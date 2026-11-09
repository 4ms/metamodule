#include "drivers/interrupt_control.hh"
#include "reent_mm.hh"
#include "util/circular_buffer.hh"
#include "util/fixed_vector.hh"
#include <atomic>
#include <iterator>
#include <sys/lock.h>
#include <utility>

// #define MM_DEBUG_LOCKS

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

struct __lock __lock___sfp_recursive_mutex{};
struct __lock __lock___atexit_recursive_mutex{};
struct __lock __lock___malloc_recursive_mutex{};
struct __lock __lock___env_recursive_mutex{};
// Guards the plugin arena allocator (plugin_arena.cc); gets the same
// IRQ-disabling treatment as the malloc lock so async threads can allocate
struct __lock __lock_mm_plugin_arena{};

// Used by abort_rescue: longjmp'ing while an allocator lock is held would
// leave the heap/arena locked (and the lock's disabled IRQs off) forever
int mm_malloc_lock_held() {
	return __lock___malloc_recursive_mutex.count != 0;
}
int mm_arena_lock_held() {
	return __lock_mm_plugin_arena.count != 0;
}

// Used by ReadPatchGuiElements (SGI1 on core 1)
// This ISR must never wait for a lock because Audio (core 0) waits for it to finish, so if it spun on a
// lock held by a process that audio had preempted, we get a deadlock.
// Also, SGIs can't be disabled so we can't just disable SGI1 whenever a lower-priority process takes a lock.
//
// Only these locks are allowed by CoreProcessor::get_display_text():
static _LOCK_T const alloc_and_stdio_locks[] = {
	&__lock___malloc_recursive_mutex,
	&__lock_mm_plugin_arena,
	&__lock___sfp_recursive_mutex, // for printf()
};

int mm_try_lock_alloc_and_stdio() {
	// Try to get all the locks: if not, then release them and return failure
	for (unsigned i = 0; i < std::size(alloc_and_stdio_locks); i++) {
		if (!__retarget_lock_try_acquire_recursive(alloc_and_stdio_locks[i])) {
			while (i-- > 0)
				__retarget_lock_release_recursive(alloc_and_stdio_locks[i]);
			return 0;
		}
	}
	return 1;
}

void mm_unlock_alloc_and_stdio() {
	for (unsigned i = std::size(alloc_and_stdio_locks); i-- > 0;)
		__retarget_lock_release_recursive(alloc_and_stdio_locks[i]);
}

struct __lock __lock___tz_mutex;
// Not used, but newlib wants them:
struct __lock __lock___at_quick_exit_mutex{};
struct __lock __lock___dd_hash_mutex{};
struct __lock __lock___arc4random_mutex{};

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

using IrqList = FixedVector<IRQn_Type, 4>;

// Returns the IRQs it disabled
static IrqList disable_higher_priority_irqs(MetaModule::Processes cur_proc) {
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

	IrqList disabled;

	if (cur_proc == MetaModule::Processes::Core0Main) {
		// Disable AsyncThread0
		if (mdrivlib::InterruptControl::is_enabled_irq(TIM7_IRQn)) {
			mdrivlib::InterruptControl::disable_irq(TIM7_IRQn);
			disabled.push_back(TIM7_IRQn);
		}
	}

	if (cur_proc == MetaModule::Processes::Core1Main) {
		// Disable AsyncThread1
		if (mdrivlib::InterruptControl::is_enabled_irq(TIM6_IRQn)) {
			mdrivlib::InterruptControl::disable_irq(TIM6_IRQn);
			disabled.push_back(TIM6_IRQn);
		}
	}

	// Note:
	// ReadPatchGuiElements (SGI1) can interrupt Core1Main and Core1AsyncThread, but it isn't disabled here
	// because SGIs can't be disabled on the GIC-400.
	// Instead the SGI1 handler only runs if it can take all the locks, which is functionally the same
	// as disabling it

	return disabled;
}

static void reenable_irqs(IrqList const &irqs) {
	for (auto irq : irqs) {
		mdrivlib::InterruptControl::reenable_irq(irq);
	}
}

// Only once the lock is ours: until then, its owner can be on the other core, releasing it and
// re-enabling (on its own core) the IRQs recorded in it
static void record_irqs_to_reenable(_LOCK_T lock, IrqList const &irqs) {
	for (auto irq : irqs) {
		lock->irqs_to_reenable.push_back(irq);
	}
}

// Takes the IRQs to re-enable out of the lock before releasing it: once it's released, the other core
// can take it and record its own
static void release_lock(_LOCK_T lock) {
	auto irqs = lock->irqs_to_reenable;
	lock->irqs_to_reenable.clear();

	lock->proc_id = -1;
	lock->count.store(0, std::memory_order_seq_cst);

	reenable_irqs(irqs);
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

static int try_acquire(_LOCK_T lock, int proc_id) {
	unsigned expected = 0;

	// If count == 0 then we claim the lock, otherwise fail
	if (lock->count.compare_exchange_strong(expected, 1, std::memory_order_seq_cst)) {
		lock->proc_id = proc_id;
		log_proclock('n', lock); //n1 means acquired
		return 1;
	} else {
		return 0;
	}
}

void __retarget_lock_acquire(_LOCK_T lock) {
	if (!lock)
		return;

	auto cur_proc = MetaModule::get_current_proc();

	auto irqs = disable_higher_priority_irqs(cur_proc);

	//spin until we can claim the lock
	while (try_acquire(lock, std::to_underlying(cur_proc)) == 0) {
	}

	record_irqs_to_reenable(lock, irqs);
}

// Only non-recursive lock seen so far is lock_tz_mutex, on Core1Main
int __retarget_lock_try_acquire(_LOCK_T lock) {
	if (!lock)
		return 0;

	auto cur_proc = MetaModule::get_current_proc();

	auto irqs = disable_higher_priority_irqs(cur_proc);

	if (try_acquire(lock, std::to_underlying(cur_proc)) == 0) {
		reenable_irqs(irqs);
		return 0;
	}

	record_irqs_to_reenable(lock, irqs);
	return 1;
}

int __retarget_lock_try_acquire_recursive(_LOCK_T lock) {
	if (!lock)
		return 0;

	auto cur_proc = MetaModule::get_current_proc();

	auto irqs = disable_higher_priority_irqs(cur_proc);

	if (try_acquire_recursive(lock, std::to_underlying(cur_proc)) == 0) {
		reenable_irqs(irqs);
		return 0;
	}

	record_irqs_to_reenable(lock, irqs);
	return 1;
}

void __retarget_lock_acquire_recursive(_LOCK_T lock) {
	if (!lock)
		return;

	auto cur_proc = MetaModule::get_current_proc();

	auto irqs = disable_higher_priority_irqs(cur_proc);

	//spin until we can claim the lock
	while (try_acquire_recursive(lock, std::to_underlying(cur_proc)) == 0) {
	}

	record_irqs_to_reenable(lock, irqs);
}

void __retarget_lock_release(_LOCK_T lock) {
	if (!lock)
		return;

	auto proc_id = MetaModule::get_current_proc_id();

	// If we own the lock, release it
	if (proc_id == lock->proc_id) {
		log_proclock('v', lock); //v with count==1 will be printed as v0
		release_lock(lock);
		return;
	} else {
		dbg_puts("Error: release on not our lock\n");
		log_proclock('#', lock);
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

			release_lock(lock);
		} else {
			// if count > 1, we keep the lock and decrement the count
			lock->count = lock->count - 1;
			log_proclock('-', lock); //-2 means recursive lock lowered 3=>2
		}
	} else {
		dbg_puts("Error: recursive release on not our lock: us lock lockproc\n");
		dbg_putc(proc_name(proc_id));
		dbg_putc(lock_name(lock));
		dbg_putc(proc_name(lock->proc_id));
		log_proclock('*', lock);
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

[[maybe_unused]] static char proc_name(int proc_id) {
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
