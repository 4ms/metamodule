// newlib's locks, for the A35's two cores (MP2). The toolchain's newlib uses retargetable locking,
// and its own versions of these do nothing; defining them here replaces them (libc's lock.o).
// MP1's are in system/lock.cc.
//
// A lock belongs to a core while it's held, and the core can take it again (recursive locks count).
// The other core spins until it's released.
//
// Interrupts: an interrupt handler that takes a lock the code it interrupted holds can't wait for
// it (that code can't run until the handler returns). So:
//  - Locks that are only ever held briefly (malloc's, and the other static ones below) mask the
//    core's interrupts while held. A handler can then never find them held by its own core.
//  - The others (FILE locks, which are held for the whole of a read or write, and the stdio list
//    lock, held while flushing every FILE) can be held too long to mask interrupts for. A handler on
//    the core that holds one goes ahead as if the lock were recursive, so it doesn't deadlock: it's
//    as unprotected against the code it interrupted as it was before there were locks. Handlers
//    shouldn't use stdio on FILEs that thread code uses.
//
// Plugins import these functions too (flashing/api-keep-list-mp2.txt), so the linker script keeps
// them all, including the ones the firmware doesn't use. The lock layout is shared with plugins (metamodule-plugin-sdk plugin-libc/glue/mp2_locks.c
// defines their static locks: plugins call these functions on them).

#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <sys/lock.h>

namespace
{
unsigned this_core() {
	uint64_t mpidr;
	asm volatile("mrs %0, mpidr_el1" : "=r"(mpidr));
	return mpidr & 0xFF;
}

// Masks IRQ and FIQ, returning the previous mask state
uint64_t mask_irqs() {
	uint64_t daif;
	asm volatile("mrs %0, daif\n\tmsr daifset, #3" : "=r"(daif) : : "memory");
	return daif;
}

void restore_irqs(uint64_t daif) {
	asm volatile("msr daif, %0" : : "r"(daif) : "memory");
}
} // namespace

extern "C" {

struct __lock {
	// 0 = free, otherwise the owning core + 1 (so a zeroed lock is free)
	std::atomic<uint32_t> owner;
	uint32_t count;
	// Mask interrupts while held (only for locks that are held briefly)
	uint32_t masks_irqs;
	uint32_t reserved;
	// The interrupt mask state to restore when released
	uint64_t saved_daif;
};
static_assert(sizeof(__lock) == 24, "Plugins (SDK plugin-libc/glue/mp2_locks.c) assume this layout");

struct __lock __lock___malloc_recursive_mutex{.masks_irqs = 1};
struct __lock __lock___atexit_recursive_mutex{.masks_irqs = 1};
struct __lock __lock___env_recursive_mutex{.masks_irqs = 1};
struct __lock __lock___tz_mutex{.masks_irqs = 1};
struct __lock __lock___at_quick_exit_mutex{.masks_irqs = 1};
struct __lock __lock___dd_hash_mutex{.masks_irqs = 1};
struct __lock __lock___arc4random_mutex{.masks_irqs = 1};
struct __lock __lock___sfp_recursive_mutex{};

static bool try_acquire(_LOCK_T lock, uint32_t me) {
	if (lock->owner.load(std::memory_order_relaxed) == me) {
		lock->count++;
		return true;
	}

	uint32_t expected = 0;
	if (lock->owner.compare_exchange_strong(expected, me, std::memory_order_acquire, std::memory_order_relaxed)) {
		lock->count = 1;
		return true;
	}

	return false;
}

static void acquire(_LOCK_T lock) {
	if (!lock)
		return;

	auto me = this_core() + 1;

	if (lock->masks_irqs) {
		auto daif = mask_irqs();
		while (!try_acquire(lock, me))
			;
		if (lock->count == 1)
			lock->saved_daif = daif;
	} else {
		while (!try_acquire(lock, me))
			;
	}
}

static int try_acquire_once(_LOCK_T lock) {
	if (!lock)
		return 0;

	auto me = this_core() + 1;

	if (lock->masks_irqs) {
		auto daif = mask_irqs();
		if (!try_acquire(lock, me)) {
			restore_irqs(daif);
			return 0;
		}
		if (lock->count == 1)
			lock->saved_daif = daif;
		return 1;
	}

	return try_acquire(lock, me) ? 1 : 0;
}

static void release(_LOCK_T lock) {
	if (!lock || lock->owner.load(std::memory_order_relaxed) != this_core() + 1)
		return;

	if (--lock->count > 0)
		return;

	auto daif = lock->saved_daif;
	lock->owner.store(0, std::memory_order_release);
	if (lock->masks_irqs)
		restore_irqs(daif);
}

// FILE locks: newlib makes one per FILE
void __retarget_lock_init_recursive(_LOCK_T *lock) {
	if (!lock)
		return;
	// If this fails, the FILE has no lock (null locks are ignored), as before there were locks
	*lock = static_cast<_LOCK_T>(calloc(1, sizeof(__lock)));
}

void __retarget_lock_init(_LOCK_T *lock) {
	__retarget_lock_init_recursive(lock);
}

void __retarget_lock_close_recursive(_LOCK_T lock) {
	free(lock);
}

void __retarget_lock_close(_LOCK_T lock) {
	__retarget_lock_close_recursive(lock);
}

void __retarget_lock_acquire_recursive(_LOCK_T lock) {
	acquire(lock);
}

void __retarget_lock_acquire(_LOCK_T lock) {
	acquire(lock);
}

int __retarget_lock_try_acquire_recursive(_LOCK_T lock) {
	return try_acquire_once(lock);
}

int __retarget_lock_try_acquire(_LOCK_T lock) {
	return try_acquire_once(lock);
}

void __retarget_lock_release_recursive(_LOCK_T lock) {
	release(lock);
}

void __retarget_lock_release(_LOCK_T lock) {
	release(lock);
}

// Used by abort rescue, as on MP1 (system/lock.cc)
int mm_malloc_lock_held() {
	return __lock___malloc_recursive_mutex.owner.load(std::memory_order_relaxed) != 0;
}
}
