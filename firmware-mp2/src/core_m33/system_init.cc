#include "drivers/stm32xx.h"

// Used by the HAL (e.g. timeouts). The M33 clock is set by TF-A.
uint32_t SystemCoreClock = 400'000'000;

// Called by startup_cm33.s before C++ static constructors.
//
// MPU: what the DCACHE may cache. Region 0 is the M33's own memory (code, data, heap, stack in
// DDR): write-back cacheable. Region 1 is the memory shared with the A35, which isn't
// cache-coherent with the M33: non-cacheable. Everything else uses the default memory map
// (PRIVDEFENA). The default map treats 0x80000000-0x9FFFFFFF as cacheable, so the shared
// region must be carved out explicitly before the DCACHE is enabled.
//
// The DCACHE itself is enabled at the start of main(), not here: startup_cm33.s writes the
// "reached main" breadcrumb after this returns, and the A35 must see it in DDR, not in our cache.

namespace
{
constexpr uint32_t AttrWriteBack = 0;
constexpr uint32_t AttrNonCacheable = 1;
} // namespace

extern "C" void system_init() {
	ARM_MPU_Disable();

	ARM_MPU_SetMemAttr(AttrWriteBack, ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(1, 1, 1, 1), ARM_MPU_ATTR_MEMORY_(1, 1, 1, 1)));
	ARM_MPU_SetMemAttr(AttrNonCacheable, ARM_MPU_ATTR(ARM_MPU_ATTR_NON_CACHEABLE, ARM_MPU_ATTR_NON_CACHEABLE));

	// RBAR(base, shareability, read-only, non-privileged access, execute-never)
	ARM_MPU_SetRegion(0,
					  ARM_MPU_RBAR(M33_LOAD_ADDR, ARM_MPU_SH_NON, 0, 1, 0),
					  ARM_MPU_RLAR(M33_LOAD_ADDR + M33_REGION_SIZE - 1, AttrWriteBack));
	ARM_MPU_SetRegion(1,
					  ARM_MPU_RBAR(SHAREDMEM_ADDR, ARM_MPU_SH_NON, 0, 1, 1),
					  ARM_MPU_RLAR(SHAREDMEM_ADDR + SHAREDMEM_SIZE - 1, AttrNonCacheable));

	ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);
}
