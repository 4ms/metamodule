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
