// MP2 versions of the plugin memory arena (src/memory/plugin_arena.cc) and abort rescue
// (system/abort_rescue.cc). MP2 has neither yet: plugins allocate from the firmware's heap (their
// malloc etc. are the firmware's), and a plugin that aborts isn't rescued.
#include "drivers/risaf.hh"
#include "memory/plugin_arena.hh"
#include "pr_dbg.hh"
#include "system/abort_rescue.hh"
#include <algorithm>
#include <cstdint>

// system/sbrk_mp2.cc
void *heap_claim_top(size_t size, size_t align);
void heap_release_top(void *ptr);
size_t get_heap_size();

namespace MetaModule
{

namespace PluginArena
{

namespace
{
// RISAF4 region for the developer drive (see main.cc for the others)
constexpr unsigned DevDriveRegionIndex = 12;
// Firewall regions are whole granules: aligning to 1MB covers any granularity
constexpr size_t FirewallAlignment = 1024 * 1024;

void *dev_drive_mem = nullptr;
} // namespace

// Without an arena, the only user of these is the developer drive (fs/dev_drive.hh), one
// allocation at a time. Its memory comes from the top of the heap region, like MP1's arena slabs
// (from malloc, a 16MB block fragments the heap, and soon there's no hole big enough for it).
// The M33 serves the drive to the computer, reading and writing its memory, so the memory is
// opened to the M33 in the DDR firewall while it's allocated. (The M33 doesn't cache it: see
// core_m33/system_init.cc.)
void *alloc_aligned(size_t align, size_t size) {
	if (dev_drive_mem)
		return nullptr;

	align = std::max(align, FirewallAlignment);
	size = (size + FirewallAlignment - 1) & ~(FirewallAlignment - 1);
	auto *mem = heap_claim_top(size, align);
	if (!mem) {
		pr_err("DevDrive: the heap (%zu bytes) reaches into the top %zu bytes of its region\n", get_heap_size(), size);
		return nullptr;
	}

	using namespace mdrivlib::RISAF;
	auto start = reinterpret_cast<uintptr_t>(mem);
	if (!add_ddr_region(DevDriveRegionIndex, start, start + size - 1, CID_A35 | CID_M33, CID_A35 | CID_M33, true)) {
		pr_err("DevDrive: RISAF4 is locked, can't open the drive's memory to the M33\n");
		heap_release_top(mem);
		return nullptr;
	}

	dev_drive_mem = mem;
	return mem;
}

void free(void *ptr) {
	if (!ptr || ptr != dev_drive_mem)
		return;

	mdrivlib::RISAF::remove_ddr_region(DevDriveRegionIndex);
	heap_release_top(ptr);
	dev_drive_mem = nullptr;
}

// No arena: plugins' allocations aren't redirected
void *allocator_redirect(std::string_view) {
	return nullptr;
}

bool contains(void const *) {
	return false;
}

size_t used_bytes() {
	return 0;
}

size_t peak_bytes() {
	return 0;
}

size_t claimed_bytes() {
	return 0;
}

} // namespace PluginArena

AbortRescue::~AbortRescue() = default;

void AbortRescue::arm() {
}

void abort_rescue_try(const char *) {
}

} // namespace MetaModule
