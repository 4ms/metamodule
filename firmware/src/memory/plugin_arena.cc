#include "plugin_arena.hh"
#include "system/alloc_diag.hh"
#include "system/alloc_rescue.hh"
#include "system/safe_log.hh"
#include "tlsf/mm_tlsf.h"
#include <cstdlib>
#include <cstring>
#include <sys/lock.h>

// Defined by the linker: end of the A7 heap. The arena is the top
// PluginArena::Size bytes of [_sheap, _eheap); sbrk.cc stops firmware heap
// growth at the arena's base.
extern char _eheap;

// Defined in lock.cc. Recursive lock with the same IRQ-disabling scheme as
// the newlib malloc lock, so async-thread ISRs can allocate without
// deadlocking against a main loop holding the lock.
extern "C" {
extern struct __lock __lock_mm_plugin_arena;
}

namespace MetaModule::PluginArena
{

namespace
{

// Compute via uintptr_t: pointer arithmetic on the linker symbol (declared
// 'char') trips -Warray-bounds
uintptr_t arena_base_addr() {
	return reinterpret_cast<uintptr_t>(&_eheap) - Size;
}

char *arena_base() {
	return reinterpret_cast<char *>(arena_base_addr());
}

mm_tlsf_t tlsf = nullptr;
size_t used = 0;
size_t peak = 0;

struct LockGuard {
	LockGuard() {
		__retarget_lock_acquire_recursive(&__lock_mm_plugin_arena);
	}
	~LockGuard() {
		__retarget_lock_release_recursive(&__lock_mm_plugin_arena);
	}
};

// Lazy init under the lock: no boot-order dependency, safe from any context
void ensure_init() {
	if (!tlsf)
		tlsf = mm_tlsf_create_with_pool(arena_base(), Size);
}

void log_arena_oom(size_t size) {
	SafeLog log;
	log.str("[arena] OOM! requested=");
	log.u64(size);
	log.str(" used=");
	log.u64(used);
	log.str(" of ");
	log.u64(Size);
	log.str(" peak=");
	log.u64(peak);
	log.flush();

	// So a subsequent abort-rescue reports OOM as the cause
	AllocRescueHooks::note_heap_exhausted();
}

void account_alloc(void *p) {
	used += mm_tlsf_block_size(p);
	if (used > peak)
		peak = used;
}

} // namespace

bool contains(void const *ptr) {
	auto p = reinterpret_cast<uintptr_t>(ptr);
	return p >= arena_base_addr() && p < reinterpret_cast<uintptr_t>(&_eheap);
}

void *alloc(size_t size) {
	LockGuard guard;
	ensure_init();
	auto *p = mm_tlsf_malloc(tlsf, size);
	if (p)
		account_alloc(p);
	else
		log_arena_oom(size);
	return p;
}

void *alloc_aligned(size_t align, size_t size) {
	LockGuard guard;
	ensure_init();
	auto *p = mm_tlsf_memalign(tlsf, align, size);
	if (p)
		account_alloc(p);
	else
		log_arena_oom(size);
	return p;
}

void *realloc(void *ptr, size_t size) {
	LockGuard guard;
	ensure_init();
	if (ptr)
		used -= mm_tlsf_block_size(ptr);
	auto *p = mm_tlsf_realloc(tlsf, ptr, size);
	if (p) {
		account_alloc(p);
	} else {
		if (ptr)
			used += mm_tlsf_block_size(ptr); // failed realloc leaves ptr valid
		if (size > 0)
			log_arena_oom(size);
	}
	return p;
}

void free(void *ptr) {
	if (!ptr)
		return;
	LockGuard guard;
	used -= mm_tlsf_free(tlsf, ptr);
}

size_t used_bytes() {
	return used;
}

size_t peak_bytes() {
	return peak;
}

} // namespace MetaModule::PluginArena

// ---- Plugin allocator wrappers -------------------------------------------
// Plugins statically link their own operator new/delete/std containers, which
// call the C allocator functions imported from firmware. The dynloader
// rebinds those imports (via allocator_redirect below) to these wrappers so
// that everything plugin code allocates lands in the arena, and every free
// dispatches by address -- ownership legitimately crosses the firmware/plugin
// boundary in both directions (e.g. a std::string handed across).
//
// A failed arena allocation returns nullptr, same as malloc: the plugin gets
// its chance to handle it, and if it aborts instead (bad_alloc -> terminate),
// the _kill/_exit hook rescues via the armed scope.

using namespace MetaModule;
using namespace MetaModule::AllocRescueHooks;

namespace
{

void *plugin_alloc(size_t size) {
	auto *p = PluginArena::alloc(size);
	log_alloc(p, size);
	return p;
}

void plugin_free(void *p) {
	if (!p)
		return;
	log_free(p);
	if (PluginArena::contains(p))
		PluginArena::free(p);
	else
		::free(p); // block was allocated by firmware, handed to plugin code
}

void *plugin_realloc(void *old, size_t size) {
	// The log only compares the old pointer's value, never dereferences it;
	// capture as an integer up front to satisfy -Wuse-after-free
	auto old_addr = reinterpret_cast<uintptr_t>(old);

	void *p;
	if (old && !PluginArena::contains(old)) {
		// Growing a firmware-heap block: keep it there (newlib owns it)
		p = ::realloc(old, size);
	} else {
		p = PluginArena::realloc(old, size);
	}
	log_realloc(reinterpret_cast<void *>(old_addr), p, size);
	return p;
}

} // namespace

extern "C" {

void *mm_plugin_malloc(size_t size) {
	return plugin_alloc(size);
}

void mm_plugin_free(void *p) {
	plugin_free(p);
}

void *mm_plugin_calloc(size_t nmemb, size_t size) {
	auto total = nmemb * size;
	auto *p = plugin_alloc(total);
	if (p)
		memset(p, 0, total);
	return p;
}

void *mm_plugin_realloc(void *old, size_t size) {
	return plugin_realloc(old, size);
}

void *mm_plugin_memalign(size_t align, size_t size) {
	auto *p = PluginArena::alloc_aligned(align, size);
	log_alloc(p, size);
	return p;
}

int mm_plugin_posix_memalign(void **memptr, size_t align, size_t size) {
	auto *p = PluginArena::alloc_aligned(align, size);
	log_alloc(p, size);
	if (!p)
		return 12; // ENOMEM
	*memptr = p;
	return 0;
}

void *mm_plugin_aligned_alloc(size_t align, size_t size) {
	auto *p = PluginArena::alloc_aligned(align, size);
	log_alloc(p, size);
	return p;
}

// newlib reentrant entry points: same behavior, reent unused
void *mm_plugin_malloc_r(struct _reent *, size_t size) {
	return plugin_alloc(size);
}

void mm_plugin_free_r(struct _reent *, void *p) {
	plugin_free(p);
}

void *mm_plugin_realloc_r(struct _reent *, void *old, size_t size) {
	return plugin_realloc(old, size);
}

void *mm_plugin_calloc_r(struct _reent *, size_t nmemb, size_t size) {
	return mm_plugin_calloc(nmemb, size);
}

void *mm_plugin_memalign_r(struct _reent *, size_t align, size_t size) {
	return mm_plugin_memalign(align, size);
}

// C++ operator new/delete, for plugins that import them instead of statically
// linking libstdc++'s. Throwing news must not return nullptr: rescue if a
// scope is armed, else hard-fail with the report.
void *mm_plugin_op_new(unsigned size) {
	auto *p = plugin_alloc(size);
	if (!p) {
		try_rescue(RescueReason::OutOfMemory);
		alloc_failed(size, alignof(max_align_t));
	}
	return p;
}

void *mm_plugin_op_new_nothrow(unsigned size, void const *) {
	return plugin_alloc(size);
}

void *mm_plugin_op_new_aligned(unsigned size, unsigned align) {
	auto *p = PluginArena::alloc_aligned(align, size);
	log_alloc(p, size);
	if (!p) {
		try_rescue(RescueReason::OutOfMemory);
		alloc_failed(size, align);
	}
	return p;
}

void mm_plugin_op_delete(void *p) {
	plugin_free(p);
}

void mm_plugin_op_delete_sized(void *p, unsigned) {
	plugin_free(p);
}

void mm_plugin_op_delete_aligned(void *p, unsigned) {
	plugin_free(p);
}

} // extern "C"

namespace MetaModule::PluginArena
{

void *allocator_redirect(std::string_view name) {
	// clang-format off
	if (name == "malloc")          return reinterpret_cast<void *>(mm_plugin_malloc);
	if (name == "free")            return reinterpret_cast<void *>(mm_plugin_free);
	if (name == "calloc")          return reinterpret_cast<void *>(mm_plugin_calloc);
	if (name == "realloc")         return reinterpret_cast<void *>(mm_plugin_realloc);
	if (name == "memalign")        return reinterpret_cast<void *>(mm_plugin_memalign);
	if (name == "posix_memalign")  return reinterpret_cast<void *>(mm_plugin_posix_memalign);
	if (name == "aligned_alloc")   return reinterpret_cast<void *>(mm_plugin_aligned_alloc);
	if (name == "_malloc_r")       return reinterpret_cast<void *>(mm_plugin_malloc_r);
	if (name == "_free_r")         return reinterpret_cast<void *>(mm_plugin_free_r);
	if (name == "_realloc_r")      return reinterpret_cast<void *>(mm_plugin_realloc_r);
	if (name == "_calloc_r")       return reinterpret_cast<void *>(mm_plugin_calloc_r);
	if (name == "_memalign_r")     return reinterpret_cast<void *>(mm_plugin_memalign_r);

	// operator new(unsigned), new[], nothrow and aligned variants (arm32 mangling)
	if (name == "_Znwj")                     return reinterpret_cast<void *>(mm_plugin_op_new);
	if (name == "_Znaj")                     return reinterpret_cast<void *>(mm_plugin_op_new);
	if (name == "_ZnwjRKSt9nothrow_t")       return reinterpret_cast<void *>(mm_plugin_op_new_nothrow);
	if (name == "_ZnajRKSt9nothrow_t")       return reinterpret_cast<void *>(mm_plugin_op_new_nothrow);
	if (name == "_ZnwjSt11align_val_t")      return reinterpret_cast<void *>(mm_plugin_op_new_aligned);
	if (name == "_ZnajSt11align_val_t")      return reinterpret_cast<void *>(mm_plugin_op_new_aligned);

	// operator delete(void*), delete[], sized and aligned variants
	if (name == "_ZdlPv")                    return reinterpret_cast<void *>(mm_plugin_op_delete);
	if (name == "_ZdaPv")                    return reinterpret_cast<void *>(mm_plugin_op_delete);
	if (name == "_ZdlPvj")                   return reinterpret_cast<void *>(mm_plugin_op_delete_sized);
	if (name == "_ZdaPvj")                   return reinterpret_cast<void *>(mm_plugin_op_delete_sized);
	if (name == "_ZdlPvSt11align_val_t")     return reinterpret_cast<void *>(mm_plugin_op_delete_aligned);
	if (name == "_ZdaPvSt11align_val_t")     return reinterpret_cast<void *>(mm_plugin_op_delete_aligned);
	// clang-format on
	return nullptr;
}

} // namespace MetaModule::PluginArena
