#include "alloc_diag.hh"
#include "safe_log.hh"
#include <algorithm>
#include <malloc.h>

#ifdef CORE_CA7
#include "reent_mm.hh"
#endif

// Defined by the linker / sbrk.cc
extern char _sheap;
extern char _eheap;
size_t get_heap_size();

namespace MetaModule
{

namespace
{

#ifdef CORE_CA7
constexpr unsigned NumSlots = NUM_PROCESSES;

unsigned slot_index() {
	auto id = get_current_proc_id();
	return (id >= 0 && id < int(NumSlots)) ? unsigned(id) : NumSlots - 1;
}

const char *proc_name(unsigned slot) {
	switch (slot) {
		case 0:
			return "Core0Main";
		case 1:
			return "Core0AsyncThread";
		case 2:
			return "Core0Audio";
		case 3:
			return "Core1Main";
		case 4:
			return "Core1AsyncThread";
		case 5:
			return "Core1ReadPatchElements";
		case 6:
			return "Core1Audio";
		default:
			return "Unknown";
	}
}
#else
constexpr unsigned NumSlots = 1;

unsigned slot_index() {
	return 0;
}

const char *proc_name(unsigned) {
	return "M4";
}
#endif

AllocDiag::Context slots[NumSlots];

void print_contexts(SafeLog &log, unsigned cur) {
	if (auto &slot = slots[cur]; slot.name[0]) {
		log.str(slot.active ? "[alloc] while: " : "[alloc] last completed: ");
		log.str(slot.kind);
		log.str(" '");
		log.str(slot.name);
		log.str("' in process ");
		log.str(proc_name(cur));
		log.flush();
	}

	for (unsigned i = 0; i < NumSlots; i++) {
		if (i != cur && slots[i].active) {
			log.str("[alloc] also in progress: [");
			log.str(proc_name(i));
			log.str("] ");
			log.str(slots[i].kind);
			log.str(" '");
			log.str(slots[i].name);
			log.str("'");
			log.flush();
		}
	}
}

} // namespace

namespace AllocDiag
{

Context exchange(std::string_view kind, std::string_view name) {
	auto &slot = slots[slot_index()];
	Context prev = slot;
	slot.kind.copy(kind);
	slot.name.copy(name);
	slot.active = true;
	return prev;
}

void restore(Context const &prev) {
	auto &slot = slots[slot_index()];
	if (prev.active)
		slot = prev;
	else
		slot.active = false; // keep the strings as a "last completed" breadcrumb
}

void abandon() {
	slots[slot_index()].active = false;
}

} // namespace AllocDiag

void report_alloc_contexts() {
	SafeLog log;
	print_contexts(log, slot_index());
}

[[noreturn]] void alloc_failed(std::size_t size, std::size_t align) {
	auto cur = slot_index();

	SafeLog log;
	log.str("[alloc] FAILED: ");
	log.u64(size);
	log.str(" bytes, align ");
	log.u64(align);
	log.str(", in process ");
	log.str(proc_name(cur));
	log.flush();

	print_contexts(log, cur);

	// arena free counts memory malloc holds but isn't using: a failure with
	// arena free >> requested size means fragmentation, not exhaustion
	auto mi = mallinfo();
	log.str("[alloc] heap: sbrk used ");
	log.u64(get_heap_size());
	log.str(" of ");
	log.u64(uintptr_t(&_eheap) - uintptr_t(&_sheap));
	log.str(", arena in-use ");
	log.u64(mi.uordblks);
	log.str(", arena free ");
	log.u64(mi.fordblks);
	log.flush();

	log.str("[alloc] halting this core");
	log.flush();

	while (true) {
		asm volatile("");
	}
}

} // namespace MetaModule
