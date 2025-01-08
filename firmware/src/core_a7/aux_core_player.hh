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

		constexpr auto ReadPatchLightsIRQn = SMPControl::IRQn(SMPCommand::ReadPatchLights);
		InterruptManager::register_and_start_isr(ReadPatchLightsIRQn, 2, 0, [this]() { read_patch_gui_elements(); });
	}

	void play_modules() {

		for (auto module_i : module_ids) {
			patch_player.step_module(module_i);
		}

		mdrivlib::SMPThread::signal_done();
	}

	void assign_module_list() {
		using namespace mdrivlib;

		module_ids.clear();

		auto num_modules = SMPControl::read<SMPRegister::NumModulesInPatch>();
		// pr_dbg("Core 2 will play %u modules:\n", num_modules);

		if (num_modules < module_ids.max_size()) {
			for (auto i = 0u; i < num_modules; i++) {
				auto id = SMPControl::read(i + 2);
				module_ids.push_back(id);
				// pr_dbg("%u\n", id);
			}

		} else
			pr_err("Error: %u modules requested to run on core 2, max is %z\n", num_modules, module_ids.size());

		SMPThread::signal_done();
	}

	void read_patch_gui_elements() {
		if (ui.new_patch_data == false) {

			for (auto &w : ui.lights().watch_lights) {
				if (w.is_active()) {
					auto val = patch_player.get_module_light(w.module_id, w.light_id);
					w.value = val;
				}
			}

			for (auto &d : ui.displays().watch_displays) {
				if (d.is_active()) {
					auto text = std::span<char>(d.text._data, d.text.capacity);
					auto sz = patch_player.get_display_text(d.module_id, d.light_id, text);
					d.text._data[sz] = '\0';
				}
			}

			for (auto &p : ui.watched_params().active_watched_params()) {
				if (p.is_active()) {
					p.value = patch_player.get_param(p.module_id, p.param_id);
				}
			}

			ui.new_patch_data = true;
		}

		SMPThread::signal_done();
	}
};

} // namespace MetaModule
