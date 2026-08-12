#include "abort_rescue.hh"
#include "reent_mm.hh"
#include "safe_log.hh"

// Defined in lock.cc: rescuing while an allocator lock is held would leave
// the heap/arena locked forever (the lock owner's stack is abandoned)
extern "C" int mm_malloc_lock_held();
extern "C" int mm_arena_lock_held();

namespace MetaModule
{

namespace
{
AbortRescue *armed[NUM_PROCESSES] = {};
}

void AbortRescue::arm() {
	proc = get_current_proc_id();
	prev = armed[proc];
	armed[proc] = this;
	active = true;
}

AbortRescue::~AbortRescue() {
	if (active) {
		armed[proc] = prev;
		active = false;
	}
}

void abort_rescue_try(const char *reason) {
	auto proc = get_current_proc_id();
	auto *scope = armed[proc];

	SafeLog log;
	log.str("[rescue] ");
	log.str(reason);
	log.str(" in proc ");
	log.u64(proc);

	if (!scope) {
		log.str(": no rescue scope armed");
		log.flush();
		return;
	}
	if (mm_malloc_lock_held() || mm_arena_lock_held()) {
		log.str(": allocator lock held, cannot rescue");
		log.flush();
		return;
	}

	log.str(": rolling back");
	log.flush();

	armed[proc] = scope->prev;
	scope->active = false;
	std::longjmp(scope->jb, 1);
}

} // namespace MetaModule

extern "C" {

// Used by abort handlers in startup_ca7.s to check if our fault handler is faulting
// (stops recursive fault logging)
uint32_t mm_abort_reroute_active[4];

// Written by the abort handlers so a debugger can see the details of a fault.
volatile uint32_t mm_abort_fault_info[16];

} // extern "C"

// Re-route a data abort, prefetch abort, or undefined instruction: if there's
// a recovery point set then longjmp to it.
extern "C" void mm_abort_reroute(uint32_t fault_addr, uint32_t fault_pc, uint32_t fsr, uint32_t fault_type) {
	const char *what = fault_type == 0 ? "data abort" :
					   fault_type == 1 ? "prefetch abort" :
										 "undefined instruction";
	{
		MetaModule::SafeLog log;
		log.str("[abort] ");
		log.str(what);
		log.str(": pc ");
		log.hex(fault_pc);
		log.str(" addr ");
		log.hex(fault_addr);
		log.str(" fsr ");
		log.hex(fsr);
		log.flush();
	}

	uint32_t mpidr;
	asm volatile("mrc p15, 0, %0, c0, c0, 5" : "=r"(mpidr));
	mm_abort_reroute_active[mpidr & 3] = 0;

	MetaModule::abort_rescue_try(what);

	// Failed to rescue: halt here until a debugger can attach
	while (true)
		asm volatile("wfe");
}
