#include "alloc_rescue.hh"
#include "alloc_diag.hh"
#include "safe_log.hh"
#include <cstdlib>
#include <malloc.h>

#ifdef CORE_CA7
#include "reent_mm.hh"
#endif

// Strong definition in lock.cc (A7). The M4 has no retargeted malloc lock, so
// this default stands there.
extern "C" __attribute__((weak)) int mm_malloc_lock_held() {
	return 0;
}

namespace MetaModule
{

namespace
{

#ifdef CORE_CA7
constexpr unsigned NumSlots = NUM_PROCESSES;

unsigned slot_index() {
	auto id = get_current_proc_id();
	return (id >= 0 && id < int(NumSlots)) ? unsigned(id) : NumSlots - 1;
}
#else
constexpr unsigned NumSlots = 1;

unsigned slot_index() {
	return 0;
}
#endif

// Per-process rescue state: the armed-scope stack plus the undo log.
// Per-process (not global) so that e.g. an async thread's allocations can
// never be recorded in -- or rolled back by -- a scope armed on a main loop.
struct Slot {
	AllocRescue *top = nullptr;

	struct Entry {
		void *ptr;
		size_t size;
	};

	static constexpr unsigned MaxEntries = 4096;
	Entry log[MaxEntries];
	unsigned count = 0;
	bool overflowed = false;
	bool heap_exhausted = false;
};

Slot slots[NumSlots];

} // namespace

// Accessor for AllocRescue's private state (friend of AllocRescue)
struct RescueState {
	static AllocRescue *armed(unsigned slot_idx) {
		auto *r = slots[slot_idx].top;
		return (r && r->active) ? r : nullptr;
	}

	static bool logging(unsigned slot_idx) {
		auto *r = slots[slot_idx].top;
		return r && r->logging;
	}

	static void disarm_and_jump(AllocRescue *r, bool is_oom) {
		// Disarm first: if the rescue handler itself fails, it must fall
		// through to the outer scope (or a hard fail), never loop back here
		r->active = false;
		r->oom = is_oom;
		longjmp(r->jb, 1);
	}
};

AllocRescue::AllocRescue() {
	slot = slot_index();
	prev = slots[slot].top;
	log_start = slots[slot].count;
	slots[slot].top = this;
}

AllocRescue::~AllocRescue() {
	auto &s = slots[slot];
	// Drop this scope's log entries: on normal exit the allocations now belong
	// to whoever the operation returned them to; after a rollback the handler
	// already dealt with them.
	s.count = log_start;
	if (!prev)
		s.overflowed = false;
	s.top = prev;
}

void AllocRescue::arm() {
	slots[slot].heap_exhausted = false;
	active = true;
	logging = true;
}

bool AllocRescue::was_oom() const {
	return oom;
}

size_t AllocRescue::free_survivors() {
	auto &s = slots[slot];

	size_t freed = 0;
	for (unsigned i = log_start; i < s.count; i++) {
		if (auto *p = s.log[i].ptr) {
			freed += s.log[i].size;
			s.log[i].ptr = nullptr;
			free(p);
		}
	}
	s.count = log_start;

	if (s.overflowed) {
		SafeLog log;
		log.str("[rescue] undo log overflowed: some allocations leaked");
		log.flush();
	}

	return freed;
}

size_t AllocRescue::leaked_bytes() const {
	auto &s = slots[slot];
	size_t live = 0;
	for (unsigned i = log_start; i < s.count; i++)
		if (s.log[i].ptr)
			live += s.log[i].size;
	return live;
}

namespace AllocRescueHooks
{

void log_alloc(void *ptr, size_t size) {
	if (!ptr)
		return;
	auto idx = slot_index();
	if (!RescueState::logging(idx))
		return;
	auto &s = slots[idx];
	if (s.count >= Slot::MaxEntries) {
		s.overflowed = true; // fail closed: unlogged blocks leak on rollback, never double-free
		return;
	}
	s.log[s.count++] = {ptr, size};
}

void log_free(void *ptr) {
	if (!ptr)
		return;
	auto idx = slot_index();
	if (!RescueState::logging(idx))
		return;
	auto &s = slots[idx];
	// Most recent first: frees usually follow their allocation closely
	for (unsigned i = s.count; i-- > 0;) {
		if (s.log[i].ptr == ptr) {
			s.log[i].ptr = nullptr; // tombstone; indices stay stable for nested scopes
			return;
		}
	}
}

void try_rescue(RescueReason reason) {
	auto idx = slot_index();
	auto *r = RescueState::armed(idx);
	if (!r)
		return;

	// Jumping while the malloc lock is held would leave the heap locked (and
	// the lock's disabled IRQs off) forever. Fall through to the hard-fail.
	if (mm_malloc_lock_held())
		return;

	bool is_oom = (reason == RescueReason::OutOfMemory) || slots[idx].heap_exhausted;

	SafeLog log;
	log.str(is_oom ? "[rescue] out of memory, rolling back" : "[rescue] abort during guarded operation, rolling back");
	log.flush();

	// The jump skips the AllocContext destructors on the abandoned frames, so
	// retire the current context here (it stays visible as a breadcrumb)
	AllocDiag::abandon();

	RescueState::disarm_and_jump(r, is_oom);
}

void note_heap_exhausted() {
	slots[slot_index()].heap_exhausted = true;
}

} // namespace AllocRescueHooks

} // namespace MetaModule

// ---- Plugin allocator wrappers -------------------------------------------
// Plugins statically link their own operator new/delete, which call malloc()
// etc. imported from firmware. The dynloader rebinds those imports to these
// wrappers (via allocator_redirect) so plugin allocations show up in the undo
// log. A failed plugin allocation returns nullptr as usual -- the plugin gets
// its chance to handle it; if it aborts instead (the common case: bad_alloc ->
// terminate), the _kill/_exit hook calls try_rescue.

using namespace MetaModule::AllocRescueHooks;

extern "C" {

void *mm_plugin_malloc(size_t size) {
	auto *p = malloc(size);
	log_alloc(p, size);
	return p;
}

void mm_plugin_free(void *p) {
	log_free(p);
	free(p);
}

void *mm_plugin_calloc(size_t nmemb, size_t size) {
	auto *p = calloc(nmemb, size);
	log_alloc(p, nmemb * size);
	return p;
}

void *mm_plugin_realloc(void *old, size_t size) {
	auto *p = realloc(old, size);
	if (p) {
		log_free(old);
		log_alloc(p, size);
	}
	return p;
}

void *mm_plugin_memalign(size_t align, size_t size) {
	auto *p = memalign(align, size);
	log_alloc(p, size);
	return p;
}

void *mm_plugin_malloc_r(struct _reent *r, size_t size) {
	auto *p = _malloc_r(r, size);
	log_alloc(p, size);
	return p;
}

void mm_plugin_free_r(struct _reent *r, void *p) {
	log_free(p);
	_free_r(r, p);
}

void *mm_plugin_realloc_r(struct _reent *r, void *old, size_t size) {
	auto *p = _realloc_r(r, old, size);
	if (p) {
		log_free(old);
		log_alloc(p, size);
	}
	return p;
}

void *mm_plugin_calloc_r(struct _reent *r, size_t nmemb, size_t size) {
	auto *p = _calloc_r(r, nmemb, size);
	log_alloc(p, nmemb * size);
	return p;
}

void *mm_plugin_memalign_r(struct _reent *r, size_t align, size_t size) {
	auto *p = _memalign_r(r, align, size);
	log_alloc(p, size);
	return p;
}

// Called at the top of _kill and _exit (libc_stub.c): a plugin that hits OOM
// throws bad_alloc from its own operator new, fails to catch it, and lands in
// abort() -> _kill. If a rescue scope is armed for this process, roll back
// instead of dying.
void mm_abort_rescue() {
	try_rescue(RescueReason::Abort);
}

} // extern "C"

namespace MetaModule::AllocRescueHooks
{

void *allocator_redirect(std::string_view name) {
	// clang-format off
	if (name == "malloc")      return reinterpret_cast<void *>(mm_plugin_malloc);
	if (name == "free")        return reinterpret_cast<void *>(mm_plugin_free);
	if (name == "calloc")      return reinterpret_cast<void *>(mm_plugin_calloc);
	if (name == "realloc")     return reinterpret_cast<void *>(mm_plugin_realloc);
	if (name == "memalign")    return reinterpret_cast<void *>(mm_plugin_memalign);
	if (name == "_malloc_r")   return reinterpret_cast<void *>(mm_plugin_malloc_r);
	if (name == "_free_r")     return reinterpret_cast<void *>(mm_plugin_free_r);
	if (name == "_realloc_r")  return reinterpret_cast<void *>(mm_plugin_realloc_r);
	if (name == "_calloc_r")   return reinterpret_cast<void *>(mm_plugin_calloc_r);
	if (name == "_memalign_r") return reinterpret_cast<void *>(mm_plugin_memalign_r);
	// clang-format on
	return nullptr;
}

} // namespace MetaModule::AllocRescueHooks
