#include "serializer.hh"
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "patch/patch_data.hh"
#include "pr_dbg.hh"
#include "util/fixed_vector.hh"
#include "util/overloaded.hh"
#include <memory>
#include <string>

namespace MetaModule
{

namespace
{

static constexpr unsigned MaxRotoSteps = 16; // Roto API goes up to 128?
using RotoString = StaticString<12>;
using RotoStringVector = FixedVector<RotoString, MaxRotoSteps>;

// Format a control name: use short_name (or long_name), truncate to 12 chars, pad to 13 with nulls.
RotoString format_control_name(const BaseElement &el) {
	RotoString s = !el.short_name.empty() ? el.short_name : !el.long_name.empty() ? el.long_name : "Unnamed";
	return s;
}

// Collect position names from a pos_names array
RotoStringVector collect_step_names(const auto &pos_names, unsigned num_pos) {
	RotoStringVector storage;

	for (unsigned i = 0; i < num_pos; ++i) {
		storage.push_back(pos_names[i]);
	}

	return storage;
}

struct HapticConfig {
	HapticMode mode = HapticMode::KNOB_300;
	uint8_t steps = 0;
	RotoStringVector step_name_storage;
};

HapticConfig haptic_for_knob() {
	return {HapticMode::KNOB_300, 0, {}};
}

HapticConfig haptic_for_knob_snapped(const KnobSnapped &el) {
	if (el.num_pos > 0 && el.num_pos <= MaxRotoSteps) {
		auto storage = collect_step_names(el.pos_names, el.num_pos);
		return {HapticMode::KNOB_N_STEP, (uint8_t)storage.size(), std::move(storage)};
	}
	return haptic_for_knob();
}

HapticConfig haptic_for_switch(const auto &el) {
	if (el.num_pos > 0 && el.num_pos <= MaxRotoSteps) {
		auto storage = collect_step_names(el.pos_names, el.num_pos);
		return {HapticMode::KNOB_N_STEP, (uint8_t)storage.size(), std::move(storage)};
	}
	return haptic_for_knob();
}

HapticConfig haptic_for_momentary_button(const BaseElement &el) {
	return {HapticMode::PUSH, 2, {el.short_name, el.short_name}};
}

HapticConfig haptic_for_latching_button(const BaseElement &el) {
	return {HapticMode::TOGGLE, 2, {el.short_name, el.short_name}};
}

// Emit a KNOB control config command.
void emit_knob(
	RotoControlMessage &msg, uint8_t &knob_index, const MappedKnob &k, BaseElement const &el, const HapticConfig &hc) {
	msg.set_control_config({ControlType::KNOB,
							0,
							knob_index,
							ControlMode::CC_7BIT,
							k.midi_chan == 0 ? uint8_t(1) : k.midi_chan,
							static_cast<uint8_t>(k.cc_num()),
							0,
							0,
							127,
							format_control_name(el),
							0,
							hc.mode,
							0xFF,
							0xFF,
							hc.steps,
							hc.step_name_storage});
	knob_index++;
}

// Emit a SWITCH control config command.
void emit_switch(RotoControlMessage &msg,
				 uint8_t &switch_index,
				 const MappedKnob &k,
				 BaseElement const &el,
				 const HapticConfig &hc) {

	uint8_t colorscheme = hc.steps + 1;
	uint8_t hc_steps = (hc.steps == 2) ? 0 : hc.steps;

	msg.set_control_config({ControlType::SWITCH,
							0,
							switch_index,
							ControlMode::CC_7BIT,
							k.midi_chan == 0 ? uint8_t(1) : k.midi_chan,
							static_cast<uint8_t>(k.cc_num()),
							0,
							0,
							127,
							format_control_name(el),
							colorscheme,
							hc.mode,
							0x00,
							0x01,
							hc_steps,
							hc.step_name_storage});
	switch_index++;
}

} // namespace

RotoControlSerializer::RotoControlSerializer(ConcurrentBuffer *buffer)
	: cdc_buffer{buffer} {
}

void RotoControlSerializer::config_max_switch_position(unsigned max_pos) {
	max_switch_pos = std::clamp(max_pos, 2u, MaxRotoSteps);
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

			std::visit(overloaded{
						   [&](const KnobSnapped &el) {
							   auto hc = haptic_for_knob_snapped(el);
							   emit_knob(msg, next_knob_index, k, el, hc);
						   },

						   [&](const Knob &el) {
							   auto hc = haptic_for_knob();
							   emit_knob(msg, next_knob_index, k, el, hc);
						   },

						   [&](const FlipSwitch &el) {
							   auto hc = haptic_for_switch(el);

							   if (el.num_pos <= max_switch_pos) {
								   emit_switch(msg, next_switch_index, k, el, hc);
							   } else {
								   emit_knob(msg, next_knob_index, k, el, hc);
							   }
						   },

						   [&](const SlideSwitch &el) {
							   auto hc = haptic_for_switch(el);

							   if (el.num_pos <= max_switch_pos) {
								   emit_switch(msg, next_switch_index, k, el, hc);
							   } else {
								   emit_knob(msg, next_knob_index, k, el, hc);
							   }
						   },

						   [&](const MomentaryButton &el) {
							   auto hc = haptic_for_momentary_button(el);
							   emit_switch(msg, next_switch_index, k, el, hc);
						   },

						   [&](const LatchingButton &el) {
							   auto hc = haptic_for_latching_button(el);
							   emit_switch(msg, next_switch_index, k, el, hc);
						   },

						   [&](const Encoder &el) {
							   // how to handle endless encoders?
							   auto hc = haptic_for_knob();
							   emit_knob(msg, next_knob_index, k, el, hc);
						   },

						   [&](const ParamElement &el) {
							   auto hc = haptic_for_knob();
							   emit_knob(msg, next_knob_index, k, el, hc);
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
