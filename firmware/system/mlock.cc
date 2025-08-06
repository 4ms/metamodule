#include "async_thread_control.hh"
#include "console/uart_log.hh"
#include "drivers/interrupt_control.hh"
#include "reent_mm.hh"
#include "util/fixed_vector.hh"
#include <atomic>
#include <sys/lock.h>
#include <utility>

extern "C" {

struct __lock {
	int proc_id = -1;
	std::atomic<unsigned> count = 0;
};

struct __lock __lock___sfp_recursive_mutex;
struct __lock __lock___atexit_recursive_mutex;
// struct __lock __lock___at_quick_exit_mutex;
struct __lock __lock___malloc_recursive_mutex;
struct __lock __lock___env_recursive_mutex;
struct __lock __lock___tz_mutex;
// struct __lock __lock___dd_hash_mutex;
// struct __lock __lock___arc4random_mutex;

// __LOCK_INIT(static,malloc_handler) expands to:
// extern struct __lock __lock_malloc_handler;
// static _LOCK_T malloc_handler = &__lock_malloc_handler;

char lock_name(_LOCK_T lock) {
	if (lock == &__lock___sfp_recursive_mutex)
		return 'f';
	if (lock == &__lock___atexit_recursive_mutex)
		return 'x';
	if (lock == &__lock___malloc_recursive_mutex)
		return 'm';
	if (lock == &__lock___env_recursive_mutex)
		return 'e';
	if (lock == &__lock___tz_mutex)
		return 't';
	return '?';
}

char proc_name(int proc_id) {
	if (proc_id == 0)
		return 'M';
	if (proc_id == 1)
		return 'A'; //async0
	if (proc_id == 2)
		return 'P'; //patch player

	if (proc_id == 3)
		return 'g'; //core1main (gui)
	if (proc_id == 4)
		return 'a'; //async1
	if (proc_id == 5)
		return 't'; //patch read elements (text_displays)
	if (proc_id == 6)
		return 'p'; //core1 audio

	return '?';
}

void __retarget_lock_init(_LOCK_T *lock) {
	__retarget_lock_init_recursive(lock);
}

void __retarget_lock_init_recursive(_LOCK_T *lock) {
	if (lock && (*lock)) {
		(*lock)->proc_id = -1;
		(*lock)->count = 0;
	}
}

void __retarget_lock_close(_LOCK_T lock) {
	__retarget_lock_close_recursive(lock);
}

void __retarget_lock_close_recursive(_LOCK_T lock) {
	if (lock) {
		lock->proc_id = -1;
		lock->count = 0;
	}
}

static FixedVector<IRQn_Type, 2> disable_higher_priority_irqs(MetaModule::Processes cur_proc) {
	FixedVector<IRQn_Type, 2> should_reenable_irqs;

	// To avoid deadlock, Core0Main must pause AsyncThread0 since the latter runs on the same CPU at a higher priority.
	// Otherwise AsyncThread0 might spin forever waiting for Core0Main to release a lock.
	// Likewise for Core1Main and AsyncThread1.
	// We don't need to consider any of the Audio threads because they are not permitted to use locking newlib functions.
	// ReadPatchGuiElements runs at the same priority as AsyncThread1, so they cannot interrupt each other.
	//
	// We can get away with mutexes without a scheduler because all processes (interrupts/threads)
	// start and run fully -- thus they should always return the lock before returning back to the previous context.
	// So we only need to be concerned with an interrupt that might need a lock that a lower process has.

	// Core0Main must pause AsyncThread1 since it runs on the same CPU at a higher priority.
	// This avoids deadlock. Likewise for Core1Main and AsyncThread1
	// In general, lower-priority threads must not be interrupted by higher-priority threads
	// but since we don't want to block audio threads, we must forbid use of locks in them.
	if (cur_proc == MetaModule::Processes::Core0Main) {
		if (mdrivlib::InterruptControl::is_enabled_irq(TIM7_IRQn)) {
			mdrivlib::InterruptControl::disable_irq(TIM7_IRQn);
			should_reenable_irqs.push_back(TIM7_IRQn);
		}
	}
	if (cur_proc == MetaModule::Processes::Core1Main) {
		if (mdrivlib::InterruptControl::is_enabled_irq(TIM6_IRQn)) {
			mdrivlib::InterruptControl::disable_irq(TIM6_IRQn);
			should_reenable_irqs.push_back(TIM6_IRQn);
		}
		if (mdrivlib::InterruptControl::is_enabled_irq(SGI4_IRQn)) {
			mdrivlib::InterruptControl::disable_irq(SGI4_IRQn);
			should_reenable_irqs.push_back(SGI4_IRQn);
		}
	}

	return should_reenable_irqs;
}

static void reenable_irqs(FixedVector<IRQn_Type, 2> &should_reenable_irqs) {
	for (auto irq : should_reenable_irqs) {
		mdrivlib::InterruptControl::reenable_irq(irq);
	}
}

static int try_acquire_recursive(_LOCK_T lock, int proc_id) {
	if (!lock)
		return 0;

	unsigned expected = 0;

	// If count == 0 then we claim the lock, otherwise see if we already own it
	if (lock->count.compare_exchange_strong(expected, 1, std::memory_order_seq_cst)) {
		lock->proc_id = proc_id;
		MetaModule::UartLog::putchar(proc_name(proc_id));
		MetaModule::UartLog::putchar('^');
		MetaModule::UartLog::putchar('1');
		MetaModule::UartLog::putchar(lock_name(lock));
		MetaModule::UartLog::putchar('\n');
		return 1;
	}

	// Count is not 0, so someone owns the lock. See if it's us.
	if (proc_id == lock->proc_id) {
		// We own the lock, so increment the count
		// memory model can be relaxed since we are the only process allowed to write
		lock->count = lock->count + 1;
		MetaModule::UartLog::putchar(proc_name(proc_id));
		MetaModule::UartLog::putchar('^');
		MetaModule::UartLog::putchar('0' + lock->count.load());
		MetaModule::UartLog::putchar(lock_name(lock));
		MetaModule::UartLog::putchar('\n');
		return 1;
	}

	return 0;
}

void __retarget_lock_acquire(_LOCK_T lock) {
	if (!lock)
		return;

	auto irqs_to_reenable = disable_higher_priority_irqs(MetaModule::get_current_proc());

	//spin until we can claim the lock
	while (__retarget_lock_try_acquire(lock) == 0)
		;

	reenable_irqs(irqs_to_reenable);
}

int __retarget_lock_try_acquire(_LOCK_T lock) {
	if (!lock)
		return 0;

	unsigned expected = 0;

	// If count == 0 then we claim the lock, otherwise fail
	if (lock->count.compare_exchange_strong(expected, 1, std::memory_order_seq_cst)) {
		lock->proc_id = MetaModule::get_current_proc_id();
		MetaModule::UartLog::putchar(proc_name(lock->proc_id));
		MetaModule::UartLog::putchar('n');
		MetaModule::UartLog::putchar('0' + lock->count.load());
		MetaModule::UartLog::putchar(lock_name(lock));
		MetaModule::UartLog::putchar('\n');
		return 1;
	} else {
		return 0;
	}
}

int __retarget_lock_try_acquire_recursive(_LOCK_T lock) {
	return try_acquire_recursive(lock, MetaModule::get_current_proc_id());
}

void __retarget_lock_acquire_recursive(_LOCK_T lock) {
	if (!lock)
		return;

	auto cur_proc = MetaModule::get_current_proc();

	auto irqs_to_reenable = disable_higher_priority_irqs(cur_proc);

	//spin until we can claim the lock
	while (try_acquire_recursive(lock, std::to_underlying(cur_proc)) == 0)
		;

	reenable_irqs(irqs_to_reenable);
}

void __retarget_lock_release(_LOCK_T lock) {
	if (!lock)
		return;

	auto proc_id = MetaModule::get_current_proc_id();

	// If we own the lock, release it
	if (proc_id == lock->proc_id) {
		MetaModule::UartLog::putchar(proc_name(lock->proc_id));
		MetaModule::UartLog::putchar('v');
		MetaModule::UartLog::putchar('0' + lock->count.load());
		MetaModule::UartLog::putchar(lock_name(lock));
		MetaModule::UartLog::putchar('\n');
		lock->count = 0;
		lock->proc_id = -1;
		return;
	} else {
		MetaModule::UartLog::putchar('y');
		MetaModule::UartLog::putchar('\n');
	}
}

void __retarget_lock_release_recursive(_LOCK_T lock) {
	if (!lock)
		return;

	if (lock->count <= 0) {
		MetaModule::UartLog::putchar('X');
		MetaModule::UartLog::putchar('\n');
		return;
	}

	auto proc_id = MetaModule::get_current_proc_id();

	// If we own the lock, decrement count
	if (proc_id == lock->proc_id) {
		// If count == 1 then we need to release to lock atomically
		if (lock->count == 1) {
			MetaModule::UartLog::putchar(proc_name(lock->proc_id));
			MetaModule::UartLog::putchar('_');
			MetaModule::UartLog::putchar('0');
			MetaModule::UartLog::putchar(lock_name(lock));
			MetaModule::UartLog::putchar('\n');
			lock->proc_id = -1;
			lock->count.store(0, std::memory_order_release);
		} else {
			// count > 1, so decrement it
			lock->count = lock->count - 1;
			MetaModule::UartLog::putchar(proc_name(lock->proc_id));
			MetaModule::UartLog::putchar('_');
			MetaModule::UartLog::putchar('0' + lock->count.load());
			MetaModule::UartLog::putchar(lock_name(lock));
			MetaModule::UartLog::putchar('\n');
		}
	} else {
		MetaModule::UartLog::putchar('x');
		MetaModule::UartLog::putchar('\n');
	}
}
}
