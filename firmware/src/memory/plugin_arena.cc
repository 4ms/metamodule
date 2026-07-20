#include "plugin_arena.hh"
#include "system/safe_log.hh"
#include "tlsf/mm_tlsf.h"
#include <cstring>
#include <new>
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

// TLSF's natural alignment on 32-bit is 4 and cannot be raised,
// so in order to support over-aligned types (e.g. NEON stores)
// we need to over-align all allocations mm_tlsf_memalign.
inline constexpr size_t MallocAlign = 8;

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
	return alloc_aligned(MallocAlign, size);
}

void *alloc_aligned(size_t align, size_t size) {
	LockGuard guard;
	ensure_init();
	auto *p = mm_tlsf_memalign(tlsf, align < MallocAlign ? MallocAlign : align, size);
	if (p)
		account_alloc(p);
	else
		log_arena_oom(size);
	return p;
}

void *realloc(void *ptr, size_t size) {
	LockGuard guard;
	ensure_init();
	if (!ptr)
		return alloc(size);
	if (size == 0) {
		used -= mm_tlsf_free(tlsf, ptr);
		return nullptr;
	}
	used -= mm_tlsf_block_size(ptr);
	auto *p = mm_tlsf_realloc(tlsf, ptr, size);
	if (p && reinterpret_cast<uintptr_t>(p) % MallocAlign) {
		// tlsf_realloc had to move the data, and its internal malloc is only
		// 4-aligned: restore the malloc alignment contract with an aligned
		// copy. (The in-place shrink/merge paths keep the pointer, which was
		// already aligned.)
		if (auto *aligned = mm_tlsf_memalign(tlsf, MallocAlign, size)) {
			memcpy(aligned, p, size);
			mm_tlsf_free(tlsf, p);
			p = aligned;
		}
		// else: keep the misaligned block rather than lose the data -- only
		// reachable if the arena is so full that re-allocating what we just
		// freed fails
	}
	if (p) {
		account_alloc(p);
	} else {
		used += mm_tlsf_block_size(ptr); // failed realloc leaves ptr valid
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

using namespace MetaModule;

// ---- free/realloc dispatchers (--wrap) -------------------------------------
// Ownership legitimately crosses the firmware/plugin boundary in both
// directions (e.g. a std::string handed across), so every free/realloc must
// dispatch by the pointer's address. The firmware links with --wrap=free etc.
// (see src/CMakeLists.txt), which redirects every firmware call site --
// including newlib-internal ones -- here. Plugin imports of free/_free_r are
// redirected here as well (allocator_redirect below): --wrap only rewrites
// link-time references, so a name lookup of "free" in the ELF would find the
// real newlib function, not the wrapper.

extern "C" {

void __real_free(void *);
void __real__free_r(struct _reent *, void *);
void *__real_realloc(void *, size_t);
void *__real__realloc_r(struct _reent *, void *, size_t);

void __wrap_free(void *p) {
	if (PluginArena::contains(p))
		PluginArena::free(p);
	else
		__real_free(p);
}

void __wrap__free_r(struct _reent *r, void *p) {
	if (PluginArena::contains(p))
		PluginArena::free(p);
	else
		__real__free_r(r, p);
}

void *__wrap_realloc(void *p, size_t size) {
	if (PluginArena::contains(p))
		return PluginArena::realloc(p, size);
	return __real_realloc(p, size);
}

void *__wrap__realloc_r(struct _reent *r, void *p, size_t size) {
	if (PluginArena::contains(p))
		return PluginArena::realloc(p, size);
	return __real__realloc_r(r, p, size);
}

} // extern "C"

// ---- Plugin allocator wrappers ---------------------------------------------
// Plugins statically link their own operator new/delete/std containers, which
// call the C allocator functions imported from firmware. The dynloader
// rebinds those imports (via allocator_redirect below) to these wrappers so
// that everything plugin code allocates lands in the arena.
//
// A failed arena allocation returns nullptr, same as malloc: the plugin's own
// operator new then throws its own bad_alloc, which the plugin can catch and
// recover from; if it doesn't, its terminate handler calls the imported
// abort() -> firmware _kill/_exit (the stage-2 recovery hook).

namespace
{

void *plugin_realloc(void *old, size_t size) {
	// A firmware-heap block stays on the firmware heap (newlib owns it); a
	// null or arena pointer (re)allocates in the arena -- unlike __wrap_realloc,
	// the caller here is known to be plugin code
	if (old && !PluginArena::contains(old))
		return __real_realloc(old, size);
	return PluginArena::realloc(old, size);
}

} // namespace

extern "C" {

void *mm_plugin_malloc(size_t size) {
	return PluginArena::alloc(size);
}

void *mm_plugin_calloc(size_t nmemb, size_t size) {
	auto total = nmemb * size;
	auto *p = PluginArena::alloc(total);
	if (p)
		memset(p, 0, total);
	return p;
}

void *mm_plugin_realloc(void *old, size_t size) {
	return plugin_realloc(old, size);
}

void *mm_plugin_memalign(size_t align, size_t size) {
	return PluginArena::alloc_aligned(align, size);
}

int mm_plugin_posix_memalign(void **memptr, size_t align, size_t size) {
	auto *p = PluginArena::alloc_aligned(align, size);
	if (!p)
		return 12; // ENOMEM
	*memptr = p;
	return 0;
}

void *mm_plugin_aligned_alloc(size_t align, size_t size) {
	return PluginArena::alloc_aligned(align, size);
}

// newlib reentrant entry points: same behavior, reent unused
void *mm_plugin_malloc_r(struct _reent *, size_t size) {
	return PluginArena::alloc(size);
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
// linking libstdc++'s. The throwing news must not return nullptr; the thrown
// bad_alloc is the firmware's, and (until cross-boundary unwinding exists)
// will terminate if no handler is reached before plugin frames.
void *mm_plugin_op_new(unsigned size) {
	auto *p = PluginArena::alloc(size);
	if (!p)
		throw std::bad_alloc{};
	return p;
}

void *mm_plugin_op_new_nothrow(unsigned size, void const *) {
	return PluginArena::alloc(size);
}

void *mm_plugin_op_new_aligned(unsigned size, unsigned align) {
	auto *p = PluginArena::alloc_aligned(align, size);
	if (!p)
		throw std::bad_alloc{};
	return p;
}

void mm_plugin_op_delete(void *p) {
	__wrap_free(p);
}

void mm_plugin_op_delete_sized(void *p, unsigned) {
	__wrap_free(p);
}

void mm_plugin_op_delete_aligned(void *p, unsigned) {
	__wrap_free(p);
}

} // extern "C"

namespace MetaModule::PluginArena
{

void *allocator_redirect(std::string_view name) {
	// clang-format off
	if (name == "malloc")          return reinterpret_cast<void *>(mm_plugin_malloc);
	if (name == "calloc")          return reinterpret_cast<void *>(mm_plugin_calloc);
	if (name == "realloc")         return reinterpret_cast<void *>(mm_plugin_realloc);
	if (name == "memalign")        return reinterpret_cast<void *>(mm_plugin_memalign);
	if (name == "posix_memalign")  return reinterpret_cast<void *>(mm_plugin_posix_memalign);
	if (name == "aligned_alloc")   return reinterpret_cast<void *>(mm_plugin_aligned_alloc);
	if (name == "_malloc_r")       return reinterpret_cast<void *>(mm_plugin_malloc_r);
	if (name == "_realloc_r")      return reinterpret_cast<void *>(mm_plugin_realloc_r);
	if (name == "_calloc_r")       return reinterpret_cast<void *>(mm_plugin_calloc_r);
	if (name == "_memalign_r")     return reinterpret_cast<void *>(mm_plugin_memalign_r);

	// De-allocation goes to the address-dispatching wrappers: a name lookup
	// of "free" in the ELF finds real newlib free (--wrap doesn't rename), so
	// plugins would otherwise free arena pointers into the newlib heap
	if (name == "free")            return reinterpret_cast<void *>(__wrap_free);
	if (name == "_free_r")         return reinterpret_cast<void *>(__wrap__free_r);

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
