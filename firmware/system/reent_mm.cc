#include "drivers/stm32xx.h"
#include <reent.h>
#include <sys/reent.h>

static struct _reent core0_reent;
static struct _reent core1_reent;
static struct _reent async0_reent;
static struct _reent async1_reent;

static bool init_reents = [] {
	core0_reent = _REENT_INIT(core0_reent);
	core1_reent = _REENT_INIT(core1_reent);
	async0_reent = _REENT_INIT(async0_reent);
	async1_reent = _REENT_INIT(async1_reent);
	return true;
}();

extern "C" struct _reent *__getreent(void) {
	auto core = __get_MPIDR() & 0b1; //0 = CA7 Core 1, 1 = CA7 Core 2
	auto is_async_thread0 = (core == 0) && LL_TIM_IsActiveFlag_UPDATE(TIM7);
	auto is_async_thread1 = (core == 1) && LL_TIM_IsActiveFlag_UPDATE(TIM6);

	return is_async_thread0 ? &async0_reent :
		   is_async_thread1 ? &async1_reent :
		   core == 0		? &core0_reent :
		   core == 1		? &core1_reent :
							  &core0_reent;
}
