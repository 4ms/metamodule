#include "boot/mmu_ca7.h"
#include "irq_ctrl.h"
#include "stm32mp1xx.h"

uint32_t SystemCoreClock = HSE_VALUE;

void SystemInit(void) {
	// do not use global variables because this function is called before
	// reaching pre-main. RW section may be overwritten afterwards.

	// The self-extract boot stub draws a boot logo on the SPI screen and leaves a
	// magic in TAMP->BKP7R (see flashing/selfextract/splash.c). When present, don't
	// reset the screen's GPIO banks below because that causes the splash to go away
	uint32_t apb2_mask = 0xFFFFFFFF;
	uint32_t ahb4_mask = 0xFFFFFFFF;
	if (TAMP->BKP7R == 0x53504C31u) {				// "SPL1"
		apb2_mask &= ~RCC_APB2RSTSETR_SPI4RST;		// keep SPI4
		ahb4_mask &= ~(RCC_AHB4RSTSETR_GPIOBRST		// keep GPIOB (DC = PB7)
					   | RCC_AHB4RSTSETR_GPIOCRST	// keep GPIOC (reset = PC4)
					   | RCC_AHB4RSTSETR_GPIOERST); // keep GPIOE (SPI4 pins)
	}

	// Force reset of all peripherals (except any preserved above)
	// This facilitates resetting the system while debugging
	RCC->APB1RSTSETR = 0xFFFFFFFF;
	RCC->APB1RSTCLRR = 0xFFFFFFFF;

	RCC->APB2RSTSETR = apb2_mask;
	RCC->APB2RSTCLRR = apb2_mask;

	RCC->APB3RSTSETR = 0xFFFFFFFF;
	RCC->APB3RSTCLRR = 0xFFFFFFFF;

	RCC->APB4RSTSETR = 0xFFFFFFFF;
	RCC->APB4RSTCLRR = 0xFFFFFFFF;

	RCC->AHB2RSTSETR = 0xFFFFFFFF;
	RCC->AHB2RSTCLRR = 0xFFFFFFFF;

	RCC->AHB4RSTSETR = ahb4_mask;
	RCC->AHB4RSTCLRR = ahb4_mask;

	// Invalidate entire Unified TLB
	__set_TLBIALL(0);

	// Invalidate entire branch predictor array
	__set_BPIALL(0);
	__DSB();
	__ISB();

	//  Invalidate instruction cache and flush branch target cache
	__set_ICIALLU(0);
	__DSB();
	__ISB();

	L1C_InvalidateDCacheAll();

	__FPU_Enable();

	MMU_CreateTranslationTable();
	MMU_Enable();

	L1C_EnableCaches();
	L1C_EnableBTAC();

#if (__L2C_PRESENT == 1)
	L2C_Enable();
#endif

	IRQ_Initialize();
}

void SystemInitAuxCore(void) {
	// Invalidate entire Unified TLB
	__set_TLBIALL(0);

	// Invalidate entire branch predictor array
	__set_BPIALL(0);
	__DSB();
	__ISB();

	//  Invalidate instruction cache and flush branch target cache
	__set_ICIALLU(0);
	__DSB();
	__ISB();

	// L1C_InvalidateDCacheAll(); //causes MPU0 to crash: TODO: why?

	__FPU_Enable();

	MMU_CreateTranslationTableAuxCore();
	MMU_Enable();

	L1C_EnableCaches();
	L1C_EnableBTAC();

	IRQ_Initialize();
}
