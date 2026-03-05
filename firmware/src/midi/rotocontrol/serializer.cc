#include "serializer.hh"
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "patch/patch_data.hh"
#include "pr_dbg.hh"
#include "util/overloaded.hh"
#include <memory>
#include <string>
#include <vector>

namespace MetaModule
{

namespace
{

static constexpr unsigned MaxRotoSteps = 16;

// Format a control name: use short_name (or long_name), truncate to 12 chars, pad to 13 with nulls.
std::string format_control_name(const ParamElement &el) {
	std::string_view sv = el.short_name;
	if (sv.empty())
		sv = el.long_name;

	std::string name;
	if (sv.empty()) {
		name = "Unnamed MIDI";
	} else {
		name = std::string(sv.substr(0, 12));
	}
	name.resize(13, '\0');
	return name;
}

// Collect step names from a pos_names array. Returns the storage vector; haptic_steps is updated.
// Works with both const char* arrays (KnobSnapped) and string_view arrays (FlipSwitch, SlideSwitch).
template<typename PosNameArray>
std::vector<std::string> collect_step_names(const PosNameArray &pos_names, unsigned num_pos, uint8_t &haptic_steps) {
	std::vector<std::string> storage;
	storage.reserve(num_pos);

	for (unsigned i = 0; i < num_pos; ++i) {
		std::string step_name;
		bool valid = false;

		if constexpr (std::is_same_v<std::decay_t<decltype(pos_names[0])>, const char *>) {
			if (pos_names[i] != nullptr) {
				step_name = std::string(pos_names[i]);
				valid = true;
			}
		} else {
			if (!pos_names[i].empty()) {
				step_name = std::string(pos_names[i]);
				valid = true;
			}
		}

		if (valid) {
			if (step_name.length() > 12)
				step_name = step_name.substr(0, 12);
			step_name.resize(13, '\0');
			storage.push_back(step_name);
		}
	}

	haptic_steps = storage.size();
	return storage;
}

// Create step names where each entry is just the control name (used for 2-state buttons).
std::vector<std::string> make_button_step_names(const std::string &control_name) {
	return {control_name, control_name};
}

// Build a c-string pointer array from a string storage vector.
std::vector<const char *> make_step_name_ptrs(const std::vector<std::string> &storage) {
	std::vector<const char *> ptrs;
	ptrs.reserve(storage.size());
	for (const auto &s : storage) {
		ptrs.push_back(s.c_str());
	}
	return ptrs;
}

struct HapticConfig {
	HapticMode mode = HapticMode::KNOB_300;
	uint8_t steps = 0;
	std::vector<std::string> step_name_storage;
};

// Determine haptic config for a Knob (continuous, no steps).
HapticConfig haptic_for_knob() {
	return {HapticMode::KNOB_300, 0, {}};
}

// Determine haptic config for a KnobSnapped.
HapticConfig haptic_for_knob_snapped(const KnobSnapped &el) {
	if (el.num_pos > 0 && el.num_pos <= MaxRotoSteps) {
		uint8_t steps = el.num_pos;
		auto storage = collect_step_names(el.pos_names, el.num_pos, steps);
		return {HapticMode::KNOB_N_STEP, steps, std::move(storage)};
	}
	return haptic_for_knob();
}

// Determine haptic config for a Switch (FlipSwitch or SlideSwitch).
template<typename SwitchT>
HapticConfig haptic_for_switch(const SwitchT &el) {
	if (el.num_pos > 0 && el.num_pos <= MaxRotoSteps) {
		uint8_t steps = el.num_pos;
		auto storage = collect_step_names(el.pos_names, el.num_pos, steps);
		return {HapticMode::KNOB_N_STEP, steps, std::move(storage)};
	}
	return {HapticMode::KNOB_300, 0, {}};
}

// Determine haptic config for a momentary button (push action, 2-state).
HapticConfig haptic_for_momentary_button(const std::string &control_name) {
	return {HapticMode::PUSH, 2, make_button_step_names(control_name)};
}

// Determine haptic config for a latching button (toggle, 2-state).
HapticConfig haptic_for_latching_button(const std::string &control_name) {
	return {HapticMode::KNOB_N_STEP, 2, make_button_step_names(control_name)};
}

// Emit a KNOB control config command.
void emit_knob(RotoControlMessage &msg,
			   uint8_t &knob_index,
			   const MappedKnob &k,
			   const char *name,
			   const HapticConfig &hc,
			   const char *const *step_names_ptr) {
	msg.set_control_config({ControlType::KNOB,
							0,
							knob_index,
							ControlMode::CC_7BIT,
							k.midi_chan == 0 ? uint8_t(1) : k.midi_chan,
							static_cast<uint8_t>(k.cc_num()),
							0,
							0,
							127,
							name,
							0,
							hc.mode,
							0xFF,
							0xFF,
							hc.steps,
							step_names_ptr});
	knob_index++;
}

// Emit a SWITCH control config command.
void emit_switch(RotoControlMessage &msg,
				 uint8_t &switch_index,
				 const MappedKnob &k,
				 const char *name,
				 const HapticConfig &hc,
				 const char *const *step_names_ptr) {
	msg.set_control_config({ControlType::SWITCH,
							0,
							switch_index,
							ControlMode::CC_7BIT,
							k.midi_chan == 0 ? uint8_t(1) : k.midi_chan,
							static_cast<uint8_t>(k.cc_num()),
							0,
							0,
							127,
							name,
							0,
							hc.mode,
							0x00,
							0x01,
							0,
							step_names_ptr});
	switch_index++;
}

// Emit either a knob or switch command based on haptic_steps.
// 2-state controls (buttons) => SWITCH, everything else => KNOB.
void emit_control(RotoControlMessage &msg,
				  uint8_t &knob_index,
				  uint8_t &switch_index,
				  const MappedKnob &k,
				  const char *name,
				  HapticConfig &hc) {
	const char *const *step_names_ptr = nullptr;
	std::vector<const char *> ptrs;

	if (!hc.step_name_storage.empty()) {
		ptrs = make_step_name_ptrs(hc.step_name_storage);
		step_names_ptr = ptrs.data();
	}

	if (hc.steps == 2) {
		emit_switch(msg, switch_index, k, name, hc, step_names_ptr);
	} else {
		emit_knob(msg, knob_index, k, name, hc, step_names_ptr);
	}
}

} // namespace

RotoControlSerializer::RotoControlSerializer(ConcurrentBuffer *buffer)
	: cdc_buffer{buffer} {
}

void RotoControlSerializer::update_from_patch(PatchData const &pd,
											  std::span<const std::unique_ptr<CoreProcessor>> modules) {
	uint8_t next_knob_index = 0;
	uint8_t next_switch_index = 0;
	const unsigned num_modules = pd.module_slugs.size();

	msg.start_config_update();
	msg.clear_midi_setup(0x00);

	for (const auto &k : pd.midi_maps.set) {
		if (k.module_id >= num_modules || !modules[k.module_id] || !(k.is_midi_cc() || k.is_midi_notegate())) {
			pr_dbg("RotoControl: Skipping MIDI map for module_id %u param_id %u\n", k.module_id, k.param_id);
			continue;
		}

		const auto &slug = pd.module_slugs[k.module_id];
		auto &module_info = ModuleFactory::getModuleInfo(slug);

		for (uint16_t el_idx = 0; el_idx < module_info.elements.size(); ++el_idx) {
			if (el_idx >= module_info.indices.size() || module_info.indices[el_idx].param_idx != k.param_id)
				continue;

			std::visit(
				overloaded{
					[&](const KnobSnapped &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_knob_snapped(el);
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const Knob &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_knob();
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const FlipSwitch &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_switch(el);
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const SlideSwitch &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_switch(el);
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const MomentaryButton &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_momentary_button(name);
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const MomentaryButtonLight &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_momentary_button(name);
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const MomentaryButtonRGB &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_momentary_button(name);
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const LatchingButton &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_latching_button(name);
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const Slider &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_knob();
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const SliderLight &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_knob();
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const Encoder &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_knob();
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const EncoderRGB &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_knob();
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[&](const ParamElement &el) {
						auto name = format_control_name(el);
						auto hc = haptic_for_knob();
						emit_control(msg, next_knob_index, next_switch_index, k, name.c_str(), hc);
					},

					[](const auto &) {
						// Non-param elements: NullElement, ImageElement, Jacks, Lights, Displays
					},
				},
				module_info.elements[el_idx]);

			break;
		}
	}

	msg.end_config_update();
	msg.set_setup(0x00);
	msg.send_all_commands(cdc_buffer);
}

} // namespace MetaModule
