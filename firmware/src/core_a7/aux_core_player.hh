#pragma once
#include "core_a7/smp_api.hh"
#include "drivers/interrupt.hh"
#include "drivers/smp.hh"
#include "gui/ui.hh"
#include "patch_play/patch_player.hh"
#include "util/fixed_vector.hh"

namespace MetaModule
{

struct AuxPlayer {
	PatchPlayer &patch_player;
	Ui &ui;

	FixedVector<unsigned, 64> module_ids;

	AuxPlayer(PatchPlayer &patch_player, Ui &ui)
		: patch_player{patch_player}
		, ui{ui} {
		using namespace mdrivlib;

		constexpr auto NewModuleListIRQn = SMPControl::IRQn(SMPCommand::NewModuleList);
		InterruptManager::register_and_start_isr(NewModuleListIRQn, 0, 0, [this]() { assign_module_list(); });

		constexpr auto PlayModuleListIRQn = SMPControl::IRQn(SMPCommand::PlayModuleList);
		InterruptManager::register_and_start_isr(PlayModuleListIRQn, 1, 0, [this]() { play_modules(); });

		constexpr auto ProcessCablesIRQn = SMPControl::IRQn(SMPCommand::ProcessCables);
		InterruptManager::register_and_start_isr(ProcessCablesIRQn, 1, 0, [this]() { process_cables(); });
	}

	void play_modules() {
		for (auto module_i : module_ids) {
			patch_player.step_module(module_i);
		}

		patch_player.process_outputs_samecore<1>();
		mdrivlib::SMPThread::signal_done();
	}

	void process_cables() {
		patch_player.process_outputs_diffcore<1>();

		mdrivlib::SMPThread::signal_done();
	}

	void assign_module_list() {
		using namespace mdrivlib;

		module_ids.clear();

		auto num_modules = SMPControl::read<SMPRegister::NumModulesInPatch>();

		if (num_modules < module_ids.max_size()) {
			for (auto i = 0u; i < num_modules; i++) {
				auto id = SMPControl::read(i + 2);
				module_ids.push_back(id);
			}

		} else
			pr_err("Error: %u modules requested to run on core 2, max is %z\n", num_modules, module_ids.size());

		SMPThread::signal_done();
	}
};

} // namespace MetaModule
