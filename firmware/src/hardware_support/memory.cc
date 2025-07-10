#include "../ld.h"
#include <cstdint>
#include <malloc.h>

namespace MetaModule
{

uint32_t total_memory() {
	return A7_HEAP_SZ;
}

uint32_t free_memory() {
	struct mallinfo mi = mallinfo();
	// uordblks: total allocated space
	return total_memory() - mi.uordblks;
}

} // namespace MetaModule
