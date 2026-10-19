// The second A35 core ("core 1"; MP1's A7 core 2). It runs MP1's AuxPlayer
// (core_a7/aux_core_player.hh): when the audio stream on core 0 signals it with an SGI, it plays its
// share of the patch's modules, and reads the text displays the GUI watches.
// Unlike MP1, the GUI stays on core 0, so core 1 only does this.

#include "aux_core.hh"
#include "core_a7/aux_core_player.hh"
#include "drivers/secondary_core_control.hh"
#include <atomic>
#include <cstdio>

extern "C" void aux_core_startup(); // mdrivlib boot/aux_core_startup.s

namespace MetaModule
{

namespace
{
PatchPlayer *aux_patch_player;
Ui *aux_ui;
std::atomic<bool> aux_ready = false;

// CPUECTLR_EL1.SMPEN: the core takes part in the cluster's cache coherency
bool smp_enabled() {
	uint64_t cpuectlr;
	asm volatile("mrs %0, S3_1_C15_C2_1" : "=r"(cpuectlr));
	return cpuectlr & (1 << 6);
}
} // namespace

bool start_aux_core(PatchPlayer &patch_player, Ui &ui) {
	if (!smp_enabled())
		printf("A35 core 0: SMPEN is not set, the cores' caches are not coherent!\n");

	aux_patch_player = &patch_player;
	aux_ui = &ui;

	if (auto err = mdrivlib::SecondaryCore::start(aux_core_startup); err != 0) {
		printf("A35 core 1: failed to start (%d)\n", err);
		return false;
	}

	for (auto start = HAL_GetTick(); !aux_ready.load(std::memory_order_acquire);) {
		if (HAL_GetTick() - start > 100) {
			printf("A35 core 1: did not start!\n");
			return false;
		}
	}

	return true;
}

} // namespace MetaModule

// Called by aux_core_startup on core 1, after it enables its MMU, caches and GIC interface
extern "C" void aux_main() {
	using namespace MetaModule;

	// Registers the SGI handlers. They must be enabled from this core (the GIC banks SGIs per core)
	AuxPlayer aux_player{*aux_patch_player, *aux_ui};

	// Core 0 is waiting for aux_ready, so it's not printing
	printf("A35 core 1: started%s\n", smp_enabled() ? "" : ", but SMPEN is not set!");

	aux_ready.store(true, std::memory_order_release);

	while (true)
		__WFI();
}
