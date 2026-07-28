#include "exidx_registry.hh"
#include "console/pr_dbg.hh"
#include <atomic>

// Firmware's own unwind table bounds, defined by the linker script
extern "C" char __exidx_start[];
extern "C" char __exidx_end[];

namespace
{

// Lookups happen during any throw, from any context (including IRQs), and
// must not allocate or lock. Slots publish/retire via an atomic write of
// code_start (0 = free slot); the other fields are written before publishing.
struct Range {
	std::atomic<uintptr_t> code_start{0};
	uintptr_t code_end{};
	uintptr_t exidx{};
	unsigned count{};
};

constexpr unsigned MaxRanges = 32;
Range ranges[MaxRanges];

} // namespace

namespace MetaModule::ExidxRegistry
{

void register_range(uintptr_t code_start, uintptr_t code_end, uintptr_t exidx_addr, unsigned num_entries) {
	// Replace an existing entry for the same code base (e.g. a reused buffer)
	for (auto &r : ranges) {
		if (r.code_start.load(std::memory_order_acquire) == code_start) {
			r.code_start.store(0, std::memory_order_release);
			r.code_end = code_end;
			r.exidx = exidx_addr;
			r.count = num_entries;
			r.code_start.store(code_start, std::memory_order_release);
			return;
		}
	}

	for (auto &r : ranges) {
		if (r.code_start.load(std::memory_order_acquire) == 0) {
			r.code_end = code_end;
			r.exidx = exidx_addr;
			r.count = num_entries;
			r.code_start.store(code_start, std::memory_order_release);
			return;
		}
	}

	pr_err("Exidx registry full: exceptions will not unwind through this plugin\n");
}

void unregister_range(uintptr_t code_start) {
	if (code_start == 0)
		return;
	for (auto &r : ranges) {
		if (r.code_start.load(std::memory_order_acquire) == code_start)
			r.code_start.store(0, std::memory_order_release);
	}
}

} // namespace MetaModule::ExidxRegistry

// Strong definition of libgcc's weak hook. Handles firmware's own table
// and the plugin tables that have been registered.
extern "C" uintptr_t __gnu_Unwind_Find_exidx(uintptr_t pc, int *nrec) {
	for (auto &r : ranges) {
		auto start = r.code_start.load(std::memory_order_acquire);
		if (start && pc >= start && pc < r.code_end) {
			*nrec = static_cast<int>(r.count);
			return r.exidx;
		}
	}

	*nrec = static_cast<int>((uintptr_t(__exidx_end) - uintptr_t(__exidx_start)) / 8);
	return uintptr_t(__exidx_start);
}

// "Bridge" between firmware and plugin code for exception handling
extern "C" uintptr_t mm_host_find_exidx(uintptr_t pc, int *nrec) {
	return __gnu_Unwind_Find_exidx(pc, nrec);
}
