#include <cstdint>
#include <malloc.h>

// MP2 version of src/hardware_support/memory.cc

extern char _sheap;
extern char _eheap;

namespace MetaModule::System
{

uint32_t total_memory() {
	return uint32_t(&_eheap - &_sheap);
}

uint32_t free_memory() {
	struct mallinfo mi = mallinfo();
	// uordblks: total allocated space
	return total_memory() - mi.uordblks;
}

} // namespace MetaModule::System
