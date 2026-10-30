#pragma once
#include "coreproc_plugin/block_job_control.hh"
#include "core_a7/smp_api.hh"
#include "drivers/cycle_counter.hh"
#include "drivers/interrupt.hh"
#include "drivers/smp.hh"
#include "gui/ui.hh"
#include "midi/midi_sync.hh"
#include "patch_play/patch_player.hh"
#include "util/fixed_vector.hh"
#include <atomic>

namespace MetaModule
{

struct AuxPlayer {
	PatchPlayer &patch_player;
	Ui &ui;

	FixedVector<unsigned, 64> module_ids;

	mdrivlib::CycleCounter module_time;

	// Background runner for BlockJobs. It runs below the frame interrupts, so
	// they preempt it: the time spent in them is subtracted from the job times
	static constexpr IRQn_Type BlockJobsIRQn = SGI6_IRQn;
	mdrivlib::CycleCounter frame_isr_time;
	mdrivlib::CycleCounter job_time;
	std::atomic<uint32_t> frame_isr_ticks{0};

	// MIDI sync instance
	MidiSync midi_sync;

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

		constexpr auto ReadPatchLightsIRQn = SMPControl::IRQn(SMPCommand::ReadPatchGuiElements);
		InterruptManager::register_and_start_isr(ReadPatchLightsIRQn, 2, 0, [this]() { read_patch_gui_elements(); });

		// Below ReadPatchGuiElements, so Core 1 never waits for a job to read the GUI elements;
		// above the async thread timer, so a long async task can't hold up a job that's due
		InterruptManager::register_and_start_isr(BlockJobsIRQn, 3, 0, [this]() { run_block_jobs(); });

		// Either core can submit a job. A DSB makes sure Core 2 sees the job before it takes the SGI
		BlockJobControl::set_runner_notify([] {
			__DSB();
			SecondaryCore::send_sgi(BlockJobsIRQn);
		});
	}

	void play_modules() {
		frame_isr_time.start_simple_measurement();

		if (patch_player.live_load.detailed()) {
			// Chained per-module timing: one counter read marks both the end of
			// one module and the start of the next
			uint32_t total_ticks = 0;
			module_time.start_measurement();
			for (auto module_i : module_ids) {
				patch_player.step_module(module_i);

				module_time.start_measurement();
				auto ticks = module_time.get_last_period_raw();
				patch_player.live_load.tally_module(module_i, ticks);
				total_ticks += ticks;
			}
			patch_player.live_load.tally_core2_modules(total_ticks);

		} else {
			module_time.start_simple_measurement();
			for (auto module_i : module_ids) {
				patch_player.step_module(module_i);
			}
			patch_player.live_load.tally_core2_modules(module_time.stop_simple_measurement());
		}

		module_time.start_simple_measurement();
		patch_player.process_outputs_samecore<1>();
		patch_player.live_load.tally_core2_cables(module_time.stop_simple_measurement());

		frame_isr_ticks.fetch_add(frame_isr_time.stop_simple_measurement(), std::memory_order_relaxed);
		mdrivlib::SMPThread::signal_done();
	}

	void process_cables() {
		module_time.start_simple_measurement();
		patch_player.process_outputs_diffcore<1>();
		patch_player.process_summed_inputs<1>();
		auto cable_ticks = module_time.stop_simple_measurement();
		patch_player.live_load.tally_core2_cables(cable_ticks);

		frame_isr_ticks.fetch_add(cable_ticks, std::memory_order_relaxed);
		mdrivlib::SMPThread::signal_done();
	}

	void run_block_jobs() {
		while (true) {
			auto preempted0 = frame_isr_ticks.load(std::memory_order_relaxed);
			job_time.start_simple_measurement();

			auto *module = BlockJobControl::run_next_job();
			if (!module)
				break;

			auto elapsed = job_time.stop_simple_measurement();
			auto preempted = frame_isr_ticks.load(std::memory_order_relaxed) - preempted0;
			auto ticks = elapsed > preempted ? elapsed - preempted : 0;

			auto &live_load = patch_player.live_load;
			if (live_load.detailed())
				live_load.tally_module(module->id, ticks);
			live_load.tally_core2_modules(ticks);
		}
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

		midi_sync.clear_last_values();

		SMPThread::signal_done();
	}

	void read_patch_gui_elements() {

		if (SMPControl::read<SMPRegister::RefreshPatchElements>() > 0) {
			midi_sync.clear_last_values();
		}

		if (ui.new_patch_data.load() == false) {

			for (auto &d : ui.displays().watch_displays) {
				if (d.is_active()) {
					auto text = std::span<char>(d.text._data, d.text.capacity);
					auto sz = patch_player.get_display_text(d.module_id, d.light_id, text);
					if (sz)
						d.text._data[sz] = '\0';
				}
			}

			patch_player.read_param_value_string(ui.param_value_string());

			if (ui.midi_feedback_enabled()) {
				for (auto &p : patch_player.watched_params().active_watched_params()) {
					if (p.is_active()) {
						auto value = patch_player.get_param(p.module_id, p.param_id);
						auto map = MappedKnob{.panel_knob_id = p.panel_knob_id};

						if (map.is_midi_cc()) {
							midi_sync.sync_param_to_midi(value, p.midi_chan, map.cc_num());

						} else if (map.is_midi_notegate()) {
							midi_sync.sync_param_to_midi_notegate(value, p.midi_chan, map.notegate_num());

						} else if (p.panel_knob_id == MidiPitchWheelJack) {
							midi_sync.sync_param_to_midi_pitchwheel(value, p.midi_chan);
						}
					}
				}
			}

			ui.new_patch_data.store(true, std::memory_order_release);
		}

		SMPThread::signal_done();
	}
};

} // namespace MetaModule
