#include "reent_mm.hh"
#include "drivers/stm32xx.h"
#include <array>
#include <reent.h>
#include <sys/reent.h>

// static struct _reent core0_reent;
// static struct _reent core1_reent;
// static struct _reent async0_reent;
// static struct _reent async1_reent;

// static bool init_reents = [] {
// 	core0_reent = _REENT_INIT(core0_reent);
// 	core1_reent = _REENT_INIT(core1_reent);
// 	async0_reent = _REENT_INIT(async0_reent);
// 	async1_reent = _REENT_INIT(async1_reent);
// 	return true;
// }();

// extern "C" struct _reent *__getreent(void) {
// 	auto core = __get_MPIDR() & 0b1; //0 = CA7 Core 1, 1 = CA7 Core 2
// 	auto is_async_thread0 = (core == 0) && LL_TIM_IsActiveFlag_UPDATE(TIM7);
// 	auto is_async_thread1 = (core == 1) && LL_TIM_IsActiveFlag_UPDATE(TIM6);

// 	return is_async_thread0 ? &async0_reent :
// 		   is_async_thread1 ? &async1_reent :
// 		   core == 0		? &core0_reent :
// 		   core == 1		? &core1_reent :
// 							  &core0_reent;
// }

namespace MetaModule
{

static std::array<struct _reent, NUM_PROCESSES> reents;

// Immediately invoked lambda run at static init time
static bool init_all_reents = [] {
	for (auto &r : reents) {
		r = _REENT_INIT(r);
	}
	return true;
}();

Processes get_current_proc() {
	const auto core = __get_MPIDR() & 0b1; //0 = CA7 Core 1, 1 = CA7 Core 2
	const auto is_async_thread0 = (core == 0) && (GIC_GetIRQStatus(TIM7_IRQn) & 0b10);
	const auto is_async_thread1 = (core == 1) && (GIC_GetIRQStatus(TIM6_IRQn) & 0b10);
	const auto is_in_audio0 = (core == 0) && (GIC_GetIRQStatus(DMA2_Stream1_IRQn) & 0b10);
	const auto is_in_audio1 = (core == 1) && (GIC_GetIRQStatus(SGI4_IRQn) & 0b10); // SMPCommand::PlayModuleList

	//TODO: read_patch_gui_elements? it calls get_display_text which could allocate?
	// const auto is_read_patch_gui = (core == 1) && (GIC_GetIRQStatus(SGI1_IRQn) & 0b10); // SMPCommand::ReadPatchGuiElements

	if (is_in_audio0) {
		return Processes::Core0Audio;
	} else if (is_in_audio1) {
		return Processes::Core1Audio;
	} else {
		return is_async_thread0 ? Processes::Core0AsyncThread :
			   is_async_thread1 ? Processes::Core1AsyncThread :
			   core == 0		? Processes::Core0Main :
			   core == 1		? Processes::Core1Main :
								  Processes::Unknown;
	}
}

int get_current_proc_id() {
	return static_cast<int>(get_current_proc());
}

} // namespace MetaModule

extern "C" struct _reent *__getreent(void) {
	auto proc_id = MetaModule::get_current_proc_id();
	return &MetaModule::reents[proc_id];
}
