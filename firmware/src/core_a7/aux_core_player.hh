#pragma once
#include "midi.hpp"
#include "midi/midi_queue.hh"
#include "midi/midi_router.hh"
#include "midi/midi_sync.hh"
#include "core_a7/smp_api.hh"
#include "core_a7/rotocontrol.hh"
#include "drivers/interrupt.hh"
#include "drivers/smp.hh"
#include "gui/ui.hh"
#include "patch_play/patch_player.hh"
#include "util/fixed_vector.hh"
#include <atomic>
#include <functional>

namespace MetaModule
{

struct AuxPlayer {
	PatchPlayer &patch_player;
	OpenPatchManager &open_patch_manager;
	Ui &ui;
	ConcurrentBuffer &console_cdc_buff;
	FixedVector<unsigned, 64> module_ids;
	unsigned midi_throttle_counter = 0;
	unsigned gui_element_counter = 0;  // Add counter for tracking iterations
	
	// MIDI sync instance
	MidiSync midi_sync;

	AuxPlayer(PatchPlayer &patch_player, OpenPatchManager &open_patch_manager, Ui &ui, ConcurrentBuffer &console_cdc_buff)
		: patch_player{patch_player}
		, open_patch_manager{open_patch_manager}
		, ui{ui}
		, console_cdc_buff{console_cdc_buff} {
		using namespace mdrivlib;

		constexpr auto NewModuleListIRQn = SMPControl::IRQn(SMPCommand::NewModuleList);
		InterruptManager::register_and_start_isr(NewModuleListIRQn, 0, 0, [this]() { assign_module_list(); });

		constexpr auto PlayModuleListIRQn = SMPControl::IRQn(SMPCommand::PlayModuleList);
		InterruptManager::register_and_start_isr(PlayModuleListIRQn, 1, 0, [this]() { play_modules(); });

		constexpr auto ProcessCablesIRQn = SMPControl::IRQn(SMPCommand::ProcessCables);
		InterruptManager::register_and_start_isr(ProcessCablesIRQn, 1, 0, [this]() { process_cables(); });

		constexpr auto ReadPatchLightsIRQn = SMPControl::IRQn(SMPCommand::ReadPatchGuiElements);
		InterruptManager::register_and_start_isr(ReadPatchLightsIRQn, 2, 0, [this]() { read_patch_gui_elements(); });
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

	void read_patch_gui_elements() {
		gui_element_counter++;

		if (ui.new_patch_data.load() == false) {

			for (auto &d : ui.displays().watch_displays) {
				if (d.is_active()) {
					auto text = std::span<char>(d.text._data, d.text.capacity);
					auto sz = patch_player.get_display_text(d.module_id, d.light_id, text);
					d.text._data[sz] = '\0';
				}
			}

			for (auto &p : ui.watched_params().active_watched_params()) {
				if (p.is_active()) {
					auto value = patch_player.get_param(p.module_id, p.param_id);
					PatchData *patch = open_patch_manager.get_playing_patch();
					if (patch) {
						const MappedKnob *mapped_knob = patch->find_midi_map(p.module_id, p.param_id);
						if (mapped_knob) {
							midi_sync.sync_param_to_midi(value, mapped_knob->midi_chan, static_cast<uint8_t>(mapped_knob->cc_num()));
						}
					}
				}
			}

			ui.new_patch_data.store(true, std::memory_order_release);
		}

		SMPThread::signal_done();
	}

	void set_knob_control_config(
		uint8_t setup_index,
		uint8_t control_index,
		ControlMode control_mode,
		uint8_t control_channel,
		uint8_t control_param,
		uint16_t nrpn_address,
		uint16_t min_value,
		uint16_t max_value,
		const char* control_name,
		uint8_t color_scheme,
		HapticMode haptic_mode,
		uint8_t indent_pos1 = 0xFF,
		uint8_t indent_pos2 = 0xFF,
		uint8_t haptic_steps = 2,
		const char* const* step_names = nullptr) {
		
		// Calculate command data length: 0x001D base + (HS * 0x0D) for step names
		uint16_t data_length = 0x001D;
		if (haptic_mode == HapticMode::KNOB_N_STEP && step_names != nullptr) {
			data_length += haptic_steps * 0x0D;
		}
		
		// Build command buffer - max possible size
		uint8_t command[256];
		uint16_t pos = 0;
		
		// Command header: 5A 02 07
		command[pos++] = 0x5A;
		command[pos++] = 0x02;
		command[pos++] = 0x07;
		
		// Command data length (MSB, LSB)
		command[pos++] = (data_length >> 8) & 0xFF;
		command[pos++] = data_length & 0xFF;
		
		// Parameters
		command[pos++] = setup_index;
		command[pos++] = control_index;
		command[pos++] = static_cast<uint8_t>(control_mode);
		command[pos++] = control_channel;
		command[pos++] = control_param;
		
		// NRPN address (2 bytes)
		command[pos++] = (nrpn_address >> 8) & 0xFF;
		command[pos++] = nrpn_address & 0xFF;
		
		// Min value (2 bytes)
		command[pos++] = (min_value >> 8) & 0xFF;
		command[pos++] = min_value & 0xFF;
		
		// Max value (2 bytes)
		command[pos++] = (max_value >> 8) & 0xFF;
		command[pos++] = max_value & 0xFF;
		
		// Control name (13 bytes, NULL terminated, padded with 00s)
		for (int i = 0; i < 13; ++i) {
			if (control_name != nullptr && control_name[i] != '\0') {
				command[pos++] = control_name[i];
			} else {
				command[pos++] = 0x00;
			}
		}
		
		// Color scheme
		command[pos++] = color_scheme;
		
		// Haptic mode
		command[pos++] = static_cast<uint8_t>(haptic_mode);
		
		// Indent positions
		command[pos++] = indent_pos1;
		command[pos++] = indent_pos2;
		
		// Haptic steps
		command[pos++] = haptic_steps;
		
		// Step names (only for KNOB_N_STEP)
		if (haptic_mode == HapticMode::KNOB_N_STEP && step_names != nullptr) {
			for (int step = 0; step < haptic_steps; ++step) {
				const char* step_name = step_names[step];
				for (int i = 0; i < 13; ++i) {
					if (step_name != nullptr && step_name[i] != '\0') {
						command[pos++] = step_name[i];
					} else {
						command[pos++] = 0x00;
					}
				}
			}
		}
		
		// Write to console buffer
		console_cdc_buff.write(std::span<const uint8_t>(command, pos));
	}

	void start_config_update() {
		// Command: 5A 01 04 00 00
		const uint8_t command[] = {0x5A, 0x01, 0x04, 0x00, 0x00};
		console_cdc_buff.write(std::span<const uint8_t>(command, sizeof(command)));
	}

	void end_config_update() {
		// Command: 5A 01 05 00 00
		const uint8_t command[] = {0x5A, 0x01, 0x05, 0x00, 0x00};
		console_cdc_buff.write(std::span<const uint8_t>(command, sizeof(command)));
	}

	// Helper to queue multiple commands with terminators between them
	void queue_config_commands(std::initializer_list<std::function<void()>> commands) {
		for (auto& command_func : commands) {
			// Execute the command
			command_func();
			// Add terminator after each command
			const uint8_t terminator[] = {0xFF, 0xFF};
			console_cdc_buff.write(std::span<const uint8_t>(terminator, sizeof(terminator)));
		}
	}
};

} // namespace MetaModule
