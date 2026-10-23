// newlib's locks, for the A35's two cores (MP2): MP1's (system/lock.cc), ported. The toolchain's
// newlib uses retargetable locking, and its own versions of these do nothing; defining them here
// replaces them (libc's lock.o).
//
// As on MP1, a lock belongs to a process (system/reent_ca35.cc: a core's main loop, or one of its
// interrupts) while it's held, and that process can take it again (recursive locks count). Any
// other process spins until it's released.
//
// Interrupts: a process must never spin on a lock held by code it interrupted, which can't run
// until it returns. So, as on MP1, taking a lock disables the interrupts on the same core that take
// locks and can preempt the process. Audio interrupts are never disabled: audio code must not take
// locks (malloc, stdio, ...), as on MP1.
//
// Also as on MP1, FILEs have no locks (newlib ignores null locks).
//
// Plugins import these functions too (flashing/api-keep-list-mp2.txt), so the linker script keeps
// them all, including the ones the firmware doesn't use. The lock layout is shared with plugins
// (metamodule-plugin-sdk plugin-libc/glue/mp2_locks.c defines their static locks: plugins call these
// functions on them).

#include "drivers/interrupt_control.hh"
#include "reent_mm.hh"
#include <array>
#include <atomic>
#include <cstdint>
#include <sys/lock.h>

using MetaModule::Processes;

namespace
{
// The interrupts that take locks (bit n in __lock::irqs_to_reenable is LockingIRQs[n])
constexpr std::array LockingIRQs{
	SGI1_IRQn, // SMPCommand::ReadPatchGuiElements, on core 1
};

// Disables the interrupts that take locks and can preempt proc, returning the ones it disabled
uint32_t disable_higher_priority_irqs(Processes proc) {
	uint32_t disabled = 0;

	auto disable = [&](unsigned i) {
		if (mdrivlib::InterruptControl::is_enabled_irq(LockingIRQs[i])) {
			mdrivlib::InterruptControl::disable_irq(LockingIRQs[i]);
			disabled |= 1u << i;
		}
	};

	// FIXME: when MP2 runs async threads (src/core_a35/async_thread_control.cc), Core0Main and Core1Main
	// must also disable their core's async thread interrupt, as on MP1
	if (proc == Processes::Core1AsyncThread || proc == Processes::Core1Main)
		disable(0);

	if (disabled) {
		__DSB();
		__ISB();
	}

	return disabled;
}

void reenable_irqs(uint32_t irqs) {
	for (auto i = 0u; i < LockingIRQs.size(); i++) {
		if (irqs & (1u << i))
			mdrivlib::InterruptControl::reenable_irq(LockingIRQs[i]);
	}
}
} // namespace

extern "C" {

struct __lock {
	// 0 = free, otherwise the owning process + 1 (so a zeroed lock is free)
	std::atomic<uint32_t> owner;
	uint32_t count;
	// The interrupts the owner disabled when it took the lock
	uint32_t irqs_to_reenable;
	uint32_t reserved[3];
};
static_assert(sizeof(__lock) == 24, "Plugins (SDK plugin-libc/glue/mp2_locks.c) assume this layout");

struct __lock __lock___malloc_recursive_mutex{};
struct __lock __lock___atexit_recursive_mutex{};
struct __lock __lock___env_recursive_mutex{};
struct __lock __lock___tz_mutex{};
struct __lock __lock___at_quick_exit_mutex{};
struct __lock __lock___dd_hash_mutex{};
struct __lock __lock___arc4random_mutex{};
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

// Unlike MP1, the disabled interrupts are recorded in the lock only once it's ours: until then the
// owner can be on the other core, releasing it (and re-enabling the interrupts it recorded)
static void acquire(_LOCK_T lock) {
	if (!lock)
		return;

	auto proc = MetaModule::get_current_proc();
	auto me = uint32_t(proc) + 1;

	auto disabled = disable_higher_priority_irqs(proc);
	while (!try_acquire(lock, me))
		;
	lock->irqs_to_reenable |= disabled;
}

// Unlike MP1, this disables interrupts like acquire() does
static int try_acquire_once(_LOCK_T lock) {
	if (!lock)
		return 0;

	auto proc = MetaModule::get_current_proc();
	auto me = uint32_t(proc) + 1;

	auto disabled = disable_higher_priority_irqs(proc);
	if (!try_acquire(lock, me)) {
		reenable_irqs(disabled);
		return 0;
	}
	lock->irqs_to_reenable |= disabled;
	return 1;
}

static void release(_LOCK_T lock) {
	if (!lock || lock->owner.load(std::memory_order_relaxed) != uint32_t(MetaModule::get_current_proc()) + 1)
		return;

	if (--lock->count > 0)
		return;

	auto irqs = lock->irqs_to_reenable;
	lock->irqs_to_reenable = 0;
	lock->owner.store(0, std::memory_order_release);
	reenable_irqs(irqs);
}

// FILE locks: newlib asks for one per FILE. As on MP1, there are none
void __retarget_lock_init_recursive(_LOCK_T *lock) {
}

void __retarget_lock_init(_LOCK_T *lock) {
}

void __retarget_lock_close_recursive(_LOCK_T lock) {
}

void __retarget_lock_close(_LOCK_T lock) {
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
