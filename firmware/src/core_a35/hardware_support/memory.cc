#include <cstddef>
#include <cstdint>
#include <malloc.h>

// MP2 version of src/hardware_support/memory.cc

size_t heap_region_size(); // system/sbrk_ca35.cc

namespace MetaModule::System
{

uint32_t total_memory() {
	return uint32_t(heap_region_size());
}

uint32_t free_memory() {
	struct mallinfo mi = mallinfo();
	// uordblks: total allocated space
	return total_memory() - mi.uordblks;
}

} // namespace MetaModule::System
