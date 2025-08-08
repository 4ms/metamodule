#include "drivers/interrupt_control.hh"
#include "medium/debug.hh"
#include "reent_mm.hh"
#include "util/circular_buffer.hh"
#include "util/fixed_vector.hh"
#include <atomic>
#include <sys/lock.h>
#include <utility>

#define MM_DEBUG_LOCKS

#ifdef MM_DEBUG_LOCKS
#include "console/uart_log.hh"
void dbg_putc(char c) {
	MetaModule::UartLog::putchar(c);
}
void dbg_puts(const char *s) {
	MetaModule::UartLog::puts(s);
}
#else
#define dbg_putc(x)
#define dbg_puts(x)
#endif

extern "C" {

struct __lock {
	int proc_id = -1;
	std::atomic<unsigned> count = 0;
	FixedVector<IRQn_Type, 4> irqs_to_reenable;
};

struct __lock __lock___sfp_recursive_mutex;
struct __lock __lock___atexit_recursive_mutex;
struct __lock __lock___malloc_recursive_mutex;
struct __lock __lock___env_recursive_mutex;
struct __lock __lock___tz_mutex;
// Not used, but newlib wants them:
struct __lock __lock___at_quick_exit_mutex;
struct __lock __lock___dd_hash_mutex;
struct __lock __lock___arc4random_mutex;

// Debug helpers:
static char lock_name(_LOCK_T lock);
static char proc_name(int proc_id);
static void print_proclock(char c, _LOCK_T lock);
static void log_proclock(char c, _LOCK_T lock);

void __retarget_lock_init(_LOCK_T *lock) {
	__retarget_lock_init_recursive(lock);
}

void __retarget_lock_init_recursive(_LOCK_T *lock) {
	if (lock && (*lock)) {
		(*lock)->proc_id = -1;
		(*lock)->count = 0;
		(*lock)->irqs_to_reenable.clear();
		print_proclock('@', *lock);
	}
}

void __retarget_lock_close(_LOCK_T lock) {
	__retarget_lock_close_recursive(lock);
}

void __retarget_lock_close_recursive(_LOCK_T lock) {
	if (lock) {
		lock->proc_id = -1;
		lock->count = 0;
		lock->irqs_to_reenable.clear();
	}
}

static void disable_higher_priority_irqs(MetaModule::Processes cur_proc, _LOCK_T lock) {
	// To avoid deadlock, lower-priority processes must disable higher-priority interrupts before taking a lock.
	// Otherwise, the higher-priority interrupt might spin forever waiting for a lock which the lower-priority
	// interrupt is holding.
	//
	// We don't need to consider any of the Audio interrupts because they are not permitted to use locking newlib functions.
	//
	// We can get away with mutexes without a scheduler because all processes (interrupts/threads)
	// start and run fully -- thus they should always return the lock before returning back to the previous context.
	// So we only need to be concerned with an interrupt that might need a lock that a lower process has.
	//
	// We will only spin-wait if the other core is holding a lock, regardless of anything related to interrupts.

	if (cur_proc == MetaModule::Processes::Core0Main) {
		// Disable AsyncThread0
		if (mdrivlib::InterruptControl::is_enabled_irq(TIM7_IRQn)) {
			mdrivlib::InterruptControl::disable_irq(TIM7_IRQn);
			lock->irqs_to_reenable.push_back(TIM7_IRQn);
		}
	}

	if (cur_proc == MetaModule::Processes::Core1Main) {
		// Disable AsyncThread1
		if (mdrivlib::InterruptControl::is_enabled_irq(TIM6_IRQn)) {
			mdrivlib::InterruptControl::disable_irq(TIM6_IRQn);
			lock->irqs_to_reenable.push_back(TIM6_IRQn);
		}
	}

	if (cur_proc == MetaModule::Processes::Core1AsyncThread || cur_proc == MetaModule::Processes::Core1Main) {
		// Disable ReadPatchGuiElements
		if (mdrivlib::InterruptControl::is_enabled_irq(SGI1_IRQn)) {
			mdrivlib::InterruptControl::disable_irq(SGI1_IRQn);
			lock->irqs_to_reenable.push_back(SGI1_IRQn);
		}
	}
}

static void reenable_irqs(_LOCK_T lock) {
	for (auto irq : lock->irqs_to_reenable) {
		mdrivlib::InterruptControl::reenable_irq(irq);
	}
	lock->irqs_to_reenable.clear();
}

static int try_acquire_recursive(_LOCK_T lock, int proc_id) {
	if (!lock)
		return 0;

	unsigned expected = 0;

	// If count == 0 then we claim the lock, otherwise see if we already own it
	if (lock->count.compare_exchange_strong(expected, 1, std::memory_order_seq_cst)) {
		lock->proc_id = proc_id;
		log_proclock('^', lock); //^1 means recursive acquired
		return 1;
	}

	// Count is not 0, so someone owns the lock. See if it's us.
	if (proc_id == lock->proc_id) {
		// We own the lock, so increment the count
		// memory model can be relaxed since we are the only process allowed to write
		lock->count = lock->count + 1;
		log_proclock('^', lock); //^2 means 1=>2
		return 1;
	}

	return 0;
}

void __retarget_lock_acquire(_LOCK_T lock) {
	if (!lock)
		return;

	disable_higher_priority_irqs(MetaModule::get_current_proc(), lock);

	//spin until we can claim the lock
	while (__retarget_lock_try_acquire(lock) == 0) {
		Debug::Pin1::high();
		Debug::Pin1::low();
	}
}

// Only non-recursive lock seen so far is lock_tz_mutex, on Core1Main
int __retarget_lock_try_acquire(_LOCK_T lock) {
	if (!lock)
		return 0;

	unsigned expected = 0;

	// If count == 0 then we claim the lock, otherwise fail
	if (lock->count.compare_exchange_strong(expected, 1, std::memory_order_seq_cst)) {
		lock->proc_id = MetaModule::get_current_proc_id();
		log_proclock('n', lock); //n1 means acquired
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

	disable_higher_priority_irqs(cur_proc, lock);

	//spin until we can claim the lock
	while (try_acquire_recursive(lock, std::to_underlying(cur_proc)) == 0) {
		Debug::Pin2::high();
		Debug::Pin2::low();
	}
}

void __retarget_lock_release(_LOCK_T lock) {
	if (!lock)
		return;

	auto proc_id = MetaModule::get_current_proc_id();

	// If we own the lock, release it
	if (proc_id == lock->proc_id) {
		log_proclock('v', lock); //v with count==1 will be printed as v0
		lock->proc_id = -1;
		lock->count.store(0, std::memory_order_seq_cst);

		reenable_irqs(lock);
		return;
	} else {
		dbg_puts("Error: release on not our lock\n");
	}
}

void __retarget_lock_release_recursive(_LOCK_T lock) {
	if (!lock)
		return;

	if (lock->count <= 0) {
		dbg_puts("Error: recursive release on unowned lock\n");
		return;
	}

	auto proc_id = MetaModule::get_current_proc_id();

	// If we own the lock, decrement count
	if (proc_id == lock->proc_id) {
		// If count == 1 then we need to release to lock atomically
		if (lock->count == 1) {
			log_proclock('_', lock); //_ with count==1 will be printed as _0

			lock->proc_id = -1;
			lock->count.store(0, std::memory_order_seq_cst);

			reenable_irqs(lock);
		} else {
			// if count > 1, we keep the lock and decrement the count
			lock->count = lock->count - 1;
			log_proclock('-', lock); //-2 means recursive lock lowered 3=>2
		}
	} else {
		dbg_puts("Error: recursive release on not our lock\n");
	}
}

///////////// Debugging:
static char lock_name(_LOCK_T lock) {
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

static char proc_name(int proc_id) {
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

static void print_proclock(char c, _LOCK_T lock) {
	dbg_putc(proc_name(lock->proc_id));
	dbg_putc(c);
	dbg_putc('0' + lock->count);
	dbg_putc(lock_name(lock));
	dbg_putc('\n');
}

struct LockEntry {
	uint32_t tm;
	char lock_id;
	uint8_t proc_id;
	char event;
	uint8_t count;
};

CircularBuffer<LockEntry, 4 * 8192> core0_lock_log;
CircularBuffer<LockEntry, 4 * 8192> core1_lock_log;
CircularBuffer<LockEntry, 4 * 8192> gui_malloc_log;

static void log_proclock(char c, _LOCK_T lock) {
	char name = lock_name(lock);

	auto &log = (lock->proc_id == 3 && name == 'm') ? gui_malloc_log :
				(lock->proc_id < 3)					? core0_lock_log :
													  core1_lock_log;

	log.put({.tm = (uint32_t)PL1_GetCurrentPhysicalValue(),
			 .lock_id = name,
			 .proc_id = uint8_t(lock->proc_id),
			 .event = c,
			 .count = (c == '_' || c == 'v') ? uint8_t(0) : uint8_t(lock->count)});
}
//
}
