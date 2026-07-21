#include "plugin_arena.hh"
#include "system/abort_rescue.hh"
#include "system/safe_log.hh"
#include "tlsf/mm_tlsf.h"
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <new>
#include <sys/lock.h>

// Defined by the linker: end of the A7 heap region [_sheap, _eheap), which
// the firmware heap (sbrk, growing up from _sheap) and the plugin arena
// (slabs claimed downward from _eheap) share with a dynamic boundary.
extern char _eheap;

// Defined in lock.cc. Recursive lock with the same IRQ-disabling scheme as
// the newlib malloc lock, so async-thread ISRs can allocate without
// deadlocking against a main loop holding the lock.
extern "C" {
extern struct __lock __lock_mm_plugin_arena;
}

// Defined in sbrk.cc: the firmware heap's current break
extern "C" uintptr_t mm_current_brk(void);

namespace MetaModule::PluginArena
{

namespace
{

uintptr_t heap_top() {
	return reinterpret_cast<uintptr_t>(&_eheap);
}

mm_tlsf_t tlsf = nullptr;
size_t used = 0;
size_t peak = 0;

// TLSF's natural alignment on 32-bit is 4 and cannot be raised,
// so in order to support over-aligned types (e.g. NEON stores)
// we need to over-align all allocations mm_tlsf_memalign.
inline constexpr size_t MallocAlign = 8;

// ---- Dynamic boundary ------------------------------------------------------
// The arena claims slabs downward from _eheap, so the arena region is always
// the contiguous range [arena_floor, _eheap) and contains() stays a two-
// comparison check. The firmware heap may grow up to arena_floor (sbrk asks
// via mm_arena_allow_brk below); slab claims must leave FwHeadroom above the
// firmware's high-water break. All boundary changes happen under the arena
// lock; contains() reads the floor lock-free (acquire pairs with the release
// store when the floor moves).

// Sentinel: arena empty. Makes contains() false with no extra branch.
constexpr uintptr_t FloorEmpty = UINTPTR_MAX;
std::atomic<uintptr_t> arena_floor{FloorEmpty};

// Firmware heap's reserved high-water break: slab claims never come closer
// than FwHeadroom to it. Only touched under the arena lock.
uintptr_t brk_ceiling = 0;

// Minimum free space guaranteed to the firmware heap above its high-water
// break. Plugin-side OOM is recoverable, so the plugin side gets no reserve.
constexpr size_t FwHeadroom = 16 * 1024 * 1024;

constexpr size_t MinSlabSize = 16 * 1024 * 1024;
constexpr size_t SlabGranularity = 1024 * 1024;

struct Slab {
	uintptr_t base;
	size_t size;
	mm_pool_t pool;
	size_t live_bytes;
};

// Stack order: slabs[0] is the first-claimed (topmost address, holds the
// TLSF control struct), the last entry is the lowest, at arena_floor.
constexpr unsigned MaxSlabs = 32;
Slab slabs[MaxSlabs];
unsigned num_slabs = 0;
size_t claimed = 0;

struct LockGuard {
	LockGuard() {
		__retarget_lock_acquire_recursive(&__lock_mm_plugin_arena);
	}
	~LockGuard() {
		__retarget_lock_release_recursive(&__lock_mm_plugin_arena);
	}
};

Slab *slab_for(void const *p) {
	auto addr = reinterpret_cast<uintptr_t>(p);
	for (unsigned i = 0; i < num_slabs; i++) {
		if (addr >= slabs[i].base && addr < slabs[i].base + slabs[i].size)
			return &slabs[i];
	}
	return nullptr;
}

// Claim a new slab below the current floor, sized for `needed` bytes of
// payload. Called under the arena lock. Returns false if the shared pool
// cannot supply it (firmware headroom would be violated, or slab table full).
bool grow(size_t needed) {
	if (num_slabs >= MaxSlabs) {
		SafeLog log;
		log.str("[arena] slab table full");
		log.flush();
		return false;
	}

	// Room for the pool's own bookkeeping plus worst-case memalign slack
	size_t overhead = mm_tlsf_pool_overhead() + 1024;
	if (!tlsf)
		overhead += mm_tlsf_size();

	size_t slab_size = needed + overhead;
	if (slab_size < MinSlabSize)
		slab_size = MinSlabSize;
	slab_size = (slab_size + SlabGranularity - 1) & ~(SlabGranularity - 1);

	uintptr_t cur_floor = num_slabs ? slabs[num_slabs - 1].base : heap_top();
	if (slab_size > cur_floor)
		return false;
	uintptr_t new_floor = cur_floor - slab_size;

	// The firmware side records its growth in brk_ceiling via
	// mm_arena_allow_brk; refresh from the live break for good measure
	if (auto brk = mm_current_brk(); brk > brk_ceiling)
		brk_ceiling = brk;

	if (new_floor < brk_ceiling + FwHeadroom)
		return false;

	if (!tlsf) {
		// First slab also holds the TLSF control struct
		tlsf = mm_tlsf_create(reinterpret_cast<void *>(new_floor));
		auto pool =
			mm_tlsf_add_pool(tlsf, reinterpret_cast<void *>(new_floor + mm_tlsf_size()), slab_size - mm_tlsf_size());
		if (!pool) {
			tlsf = nullptr;
			return false;
		}
		slabs[0] = {new_floor, slab_size, pool, 0};
		num_slabs = 1;
	} else {
		auto pool = mm_tlsf_add_pool(tlsf, reinterpret_cast<void *>(new_floor), slab_size);
		if (!pool)
			return false;
		slabs[num_slabs++] = {new_floor, slab_size, pool, 0};
	}

	claimed += slab_size;
	arena_floor.store(new_floor, std::memory_order_release);
	return true;
}

// Return drained slabs to the shared pool. Only the bottom-most slab (at the
// floor) can be returned, so the arena region stays contiguous; cascade
// upward. Called under the arena lock after frees.
void try_return_slabs() {
	while (num_slabs > 0) {
		auto &bottom = slabs[num_slabs - 1];
		if (bottom.live_bytes != 0)
			break;

		if (num_slabs == 1) {
			// The last slab holds the TLSF control: back to the virgin state
			tlsf = nullptr;
			claimed -= bottom.size;
			num_slabs = 0;
			arena_floor.store(FloorEmpty, std::memory_order_release);
			break;
		}

		mm_tlsf_remove_pool(tlsf, bottom.pool);
		claimed -= bottom.size;
		num_slabs--;
		arena_floor.store(slabs[num_slabs - 1].base, std::memory_order_release);
	}
}

void log_arena_oom(size_t size) {
	SafeLog log;
	log.str("[arena] OOM! requested=");
	log.u64(size);
	log.str(" used=");
	log.u64(used);
	log.str(" claimed=");
	log.u64(claimed);
	log.str(" peak=");
	log.u64(peak);
	log.str(" fw_brk_hw=");
	log.u64(brk_ceiling ? brk_ceiling : mm_current_brk());
	log.str(" unclaimed=");
	auto floor = num_slabs ? slabs[num_slabs - 1].base : heap_top();
	auto ceiling = brk_ceiling ? brk_ceiling : mm_current_brk();
	log.u64(floor > ceiling ? floor - ceiling : 0);
	log.flush();
}

void account_alloc(void *p) {
	auto sz = mm_tlsf_block_size(p);
	used += sz;
	if (used > peak)
		peak = used;
	if (auto *s = slab_for(p))
		s->live_bytes += sz;
}

// mm_tlsf_free's return value is the raw header size field (may include flag
// bits), so measure with mm_tlsf_block_size before freeing: the slab counter
// must net to exactly zero for slab return to work.
void do_free(void *ptr) {
	auto sz = mm_tlsf_block_size(ptr);
	auto *s = slab_for(ptr);
	mm_tlsf_free(tlsf, ptr);
	used -= sz;
	if (s)
		s->live_bytes -= sz;
}

} // namespace

bool contains(void const *ptr) {
	auto p = reinterpret_cast<uintptr_t>(ptr);
	return p >= arena_floor.load(std::memory_order_acquire) && p < heap_top();
}

void *alloc(size_t size) {
	return alloc_aligned(MallocAlign, size);
}

void *alloc_aligned(size_t align, size_t size) {
	LockGuard guard;
	if (align < MallocAlign)
		align = MallocAlign;
	auto *p = tlsf ? mm_tlsf_memalign(tlsf, align, size) : nullptr;
	if (!p) {
		// A block cannot span slabs, so the new slab is sized for the whole
		// request (plus alignment slack)
		if (grow(size + align))
			p = mm_tlsf_memalign(tlsf, align, size);
	}
	if (p)
		account_alloc(p);
	else
		log_arena_oom(size);
	return p;
}

void *realloc(void *ptr, size_t size) {
	LockGuard guard;
	if (!ptr)
		return alloc(size);
	if (size == 0) {
		do_free(ptr);
		try_return_slabs();
		return nullptr;
	}

	auto old_size = mm_tlsf_block_size(ptr);
	auto *old_slab = slab_for(ptr);
	used -= old_size;
	if (old_slab)
		old_slab->live_bytes -= old_size;

	auto *p = mm_tlsf_realloc(tlsf, ptr, size);
	if (!p) {
		if (grow(size + MallocAlign))
			p = mm_tlsf_realloc(tlsf, ptr, size);
	}
	if (p && reinterpret_cast<uintptr_t>(p) % MallocAlign) {
		// tlsf_realloc had to move the data, and its internal malloc is only
		// 4-aligned: restore the malloc alignment contract with an aligned
		// copy. (The in-place shrink/merge paths keep the pointer, which was
		// already aligned.)
		auto *aligned = mm_tlsf_memalign(tlsf, MallocAlign, size);
		if (!aligned && grow(size + MallocAlign))
			aligned = mm_tlsf_memalign(tlsf, MallocAlign, size);
		if (aligned) {
			memcpy(aligned, p, size);
			mm_tlsf_free(tlsf, p); // never accounted: raw free
			p = aligned;
		}
		// else: keep the misaligned block rather than lose the data -- only
		// reachable if the arena is so full that re-allocating what we just
		// freed fails
	}
	if (p) {
		account_alloc(p);
	} else {
		// failed realloc leaves ptr valid
		used += old_size;
		if (old_slab)
			old_slab->live_bytes += old_size;
		log_arena_oom(size);
	}
	try_return_slabs();
	return p;
}

void free(void *ptr) {
	if (!ptr)
		return;
	LockGuard guard;
	do_free(ptr);
	try_return_slabs();
}

size_t used_bytes() {
	return used;
}

size_t peak_bytes() {
	return peak;
}

size_t claimed_bytes() {
	return claimed;
}

// ---- Boundary negotiation with sbrk ----------------------------------------

extern "C" {

// Called by _sbrk for positive increments: authoritative check that firmware
// heap growth stays below the arena, and records the firmware's high-water
// break so slab claims keep FwHeadroom clear of it.
int mm_arena_allow_brk(uintptr_t new_brk) {
	LockGuard guard;
	auto floor = arena_floor.load(std::memory_order_relaxed);
	uintptr_t limit = (floor == FloorEmpty) ? heap_top() : floor;
	if (new_brk > limit)
		return 0;
	if (new_brk > brk_ceiling)
		brk_ceiling = new_brk;
	return 1;
}

// The firmware heap's current upper limit, for sbrk's bounds check/logging
uintptr_t mm_arena_floor(void) {
	auto floor = arena_floor.load(std::memory_order_acquire);
	return (floor == FloorEmpty) ? heap_top() : floor;
}

} // extern "C"

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

// A plugin that hits an unrecoverable error calls its imported abort() --
// most commonly via its own std::terminate after an uncaught bad_alloc (its
// verbose-terminate message has already been printed by the time we get
// here). Plugin exceptions cannot unwind into firmware frames, so this hook
// is the only chance to regain control: longjmp back to the rescue scope
// armed around the call into plugin code (module creation, plugin init).
// With no scope armed (e.g. death in the audio context), fall through to a
// real abort and halt.
void mm_plugin_abort(void) {
	{
		SafeLog log;
		log.str("[abort] plugin called abort(); arena used=");
		log.u64(PluginArena::used_bytes());
		log.str(" of ");
		log.u64(PluginArena::claimed_bytes());
		log.flush();
	}
	MetaModule::abort_rescue_try("plugin abort");
	::abort();
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

	// Plugin death (uncaught exception -> terminate -> abort) routes to the
	// rescue hook instead of halting
	if (name == "abort")           return reinterpret_cast<void *>(mm_plugin_abort);

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
