#include "plugin_arena.hh"
#include "system/safe_log.hh"
#include "tlsf/mm_tlsf.h"
#include <atomic>
#include <cstring>
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
// comparison check.
// The firmware heap may grow up to arena_floor (sbrk asks via mm_arena_allow_brk).
// slab claims must leave FwHeadroom above the firmware's high-water break.
// All boundary changes happen under the arena lock.
// contains() reads the floor lock-free (acquire pairs with the release
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

	// TLSF's good-fit search rounds a request up by one second-level granule
	// (needed/32 at these sizes) and only searches buckets that guarantee a
	// fit: the slab's free block must be that much larger than the request or
	// the retry after grow() cannot find it. Happens at requests >= ~32 MB,
	// where the granule exceeds the 1 MB slab rounding.
	size_t slab_size = needed + needed / 32 + overhead;
	if (slab_size < MinSlabSize)
		slab_size = MinSlabSize;
	slab_size = (slab_size + SlabGranularity - 1) & ~(SlabGranularity - 1);

	uintptr_t cur_floor = num_slabs ? slabs[num_slabs - 1].base : heap_top();
	if (slab_size > cur_floor)
		return false;
	uintptr_t new_floor = cur_floor - slab_size;

	// The firmware side records its growth in brk_ceiling via
	// mm_arena_allow_brk. Refresh from the live break
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
	if (p) {
		account_alloc(p);
	} else {
		// A slab speculatively claimed by grow() sits empty if the retry
		// still failed: give it back before reporting
		try_return_slabs();
		log_arena_oom(size);
	}
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

int check() {
	LockGuard guard;
	if (!tlsf)
		return 0;

	int errors = 0;

	// Internal free-list/bitmap consistency
	if (auto status = mm_tlsf_check(tlsf); status != 0) {
		errors += (status < 0) ? -status : status;
		SafeLog log;
		log.str("[arena] integrity FAIL in allocator control maps: ");
		log.u64(errors);
		log.str(" checks failed");
		log.flush();
	}

	// Physical block walk of every slab
	for (unsigned i = 0; i < num_slabs; i++) {
		if (auto status = mm_tlsf_check_pool(slabs[i].pool); status != 0) {
			auto n = (status < 0) ? -status : status;
			errors += n;
			SafeLog log;
			log.str("[arena] integrity FAIL in slab ");
			log.u64(i);
			log.str(" base=");
			log.hex(slabs[i].base);
			log.str(" size=");
			log.u64(slabs[i].size);
			log.str(": ");
			log.u64(n);
			log.str(" checks failed");
			log.flush();
		}
	}

	return errors;
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
