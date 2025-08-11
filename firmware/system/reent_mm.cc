#include "reent_mm.hh"
#include "drivers/stm32xx.h"
#include <array>
#include <reent.h>
#include <sys/reent.h>

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
	if (core == 1) {
		if (GIC_GetIRQStatus(TIM6_IRQn) & 0b10) {
			return Processes::Core1AsyncThread;
		}
		if (GIC_GetIRQStatus(SGI1_IRQn) & 0b10) { // SMPCommand::ReadPatchGuiElements
			return Processes::Core1ReadPatchElements;
		}
		if (GIC_GetIRQStatus(SGI4_IRQn) & 0b10) { // SMPCommand::PlayModuleList
			return Processes::Core1Audio;
		}
		return Processes::Core1Main;

	} else {
		if (GIC_GetIRQStatus(TIM7_IRQn) & 0b10) {
			return Processes::Core0AsyncThread;
		}
		if (GIC_GetIRQStatus(DMA2_Stream1_IRQn) & 0b10) { // Audio SAI TX DMA
			return Processes::Core0Audio;
		}
		return Processes::Core0Main;
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
