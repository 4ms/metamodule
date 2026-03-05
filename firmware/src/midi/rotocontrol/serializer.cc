#include "serializer.hh"
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "patch/patch_data.hh"
#include "pr_dbg.hh"
#include "util/overloaded.hh"
#include <memory>

namespace MetaModule
{

RotoControlSerializer::RotoControlSerializer(ConcurrentBuffer *buffer)
	: cdc_buffer{buffer} {
}

void RotoControlSerializer::update_from_patch(PatchData const &pd,
											  std::span<const std::unique_ptr<CoreProcessor>> modules) {
	unsigned next_midi_roto_knob_index_ = 0;
	unsigned next_midi_roto_switch_index_ = 0;
	const unsigned num_modules = pd.module_slugs.size();

	msg.start_config_update();
	msg.clear_midi_setup(0x00);

	for (const auto &k : pd.midi_maps.set) {
		if (k.module_id >= num_modules || !modules[k.module_id] || !(k.is_midi_cc() || k.is_midi_notegate())) {
			pr_dbg("RotoControl: Skipping MIDI map for module_id %u param_id %u\n", k.module_id, k.param_id);
			continue;
		}

		pr_dbg("RotoControl: Processing MIDI map for module_id %u param_id %u\n", k.module_id, k.param_id);

		const auto &slug = pd.module_slugs[k.module_id];

		auto &module_info = ModuleFactory::getModuleInfo(slug);

		// TODO: use std::find_if
		for (uint16_t el_idx = 0; el_idx < module_info.elements.size(); ++el_idx) {
			bool is_target_param = false;
			if (el_idx < module_info.indices.size() && module_info.indices[el_idx].param_idx == k.param_id) {
				is_target_param = true;
			}

			if (is_target_param) {
				const auto &element_variant = module_info.elements[el_idx];
				// FIXME: use std::visit properly, matching with an overload set
				// use `overloaded` class and a lambda matching on the type.

				std::visit(
					[&](auto &&arg) {
						using T = std::decay_t<decltype(arg)>;
						if constexpr (std::is_base_of_v<ParamElement, T>) {
							const ParamElement &param_el = arg;
							std::string_view control_name_sv = param_el.short_name;
							if (control_name_sv.empty())
								control_name_sv = param_el.long_name;

							std::string control_name_str;
							const char *control_name_ptr;

							pr_dbg("control_name_sv: %s\n", control_name_sv.data());

							if (control_name_sv.empty()) {
								control_name_str = "Unnamed MIDI"; // Max 12 chars + null
								// Pad with null bytes to make it exactly 13 characters
								control_name_str.resize(13, '\0');
								control_name_ptr = control_name_str.c_str();
							} else {
								if (control_name_sv.length() > 12) {
									control_name_str = std::string(control_name_sv.substr(0, 12));
								} else {
									control_name_str = std::string(control_name_sv);
								}
								// Pad with null bytes to make it exactly 13 characters
								control_name_str.resize(13, '\0');
								control_name_ptr = control_name_str.c_str();
							}

							uint16_t min_val_u16 = 0;
							uint16_t max_val_u16 = 127;
							HapticMode haptic_mode = HapticMode::KNOB_300;
							uint8_t haptic_steps = 0;
							const char *const *step_names_ptr = nullptr;
							std::vector<std::string> dummy_step_names_storage;
							std::vector<const char *> dummy_step_names_ptrs;

							if constexpr (std::is_base_of_v<Knob, T>) {
								pr_dbg("Knob: %s\n", control_name_str.c_str());
								// TODO: Move to RotoControl constants, 16 is the max number of steps RotoControl can support
								if constexpr (std::is_same_v<T, KnobSnapped>) {
									const KnobSnapped &snapped_knob = static_cast<const KnobSnapped &>(arg);
									if (snapped_knob.num_pos > 0 && snapped_knob.num_pos <= 16) {
										haptic_mode = HapticMode::KNOB_N_STEP;
										haptic_steps = snapped_knob.num_pos;
									} else {
										haptic_mode = HapticMode::KNOB_300;
									}
								} else {
									haptic_mode = HapticMode::KNOB_300;
								}
							} else if constexpr (std::is_base_of_v<Switch, T>) {
								pr_dbg("Switch: %s\n", control_name_str.c_str());
								const auto &switch_el = arg;
								if (switch_el.num_pos > 0 && switch_el.num_pos <= 16) {
									haptic_mode = HapticMode::KNOB_N_STEP;
									haptic_steps = switch_el.num_pos;
								} else {
									haptic_mode = HapticMode::KNOB_300;
								}
							} else if constexpr (std::is_base_of_v<Button, T>) {
								pr_dbg("Button: %s\n", control_name_str.c_str());
								haptic_steps = 2;

								if constexpr (std::is_same_v<T, MomentaryButton> ||
											  std::is_same_v<T, MomentaryButtonLight> ||
											  std::is_same_v<T, MomentaryButtonRGB>)
								{
									haptic_mode = HapticMode::PUSH;
								} else if constexpr (std::is_same_v<T, LatchingButton>) {
									haptic_mode = HapticMode::KNOB_N_STEP;
								} else {
									pr_warn("RotoControl: Encountered an unhandled Button-derived type for param_id %u",
											k.param_id);
								}
							}
							pr_dbg("haptic_steps: %d\n", haptic_steps);
							pr_dbg("haptic_mode: %d\n", haptic_mode);
							pr_dbg("control_name_str: %s\n", control_name_str.c_str());

							if (haptic_steps > 0) { // MODIFIED: Ensure check is > 0 explicitly
								dummy_step_names_storage.reserve(haptic_steps); // ADDED: Reserve storage

								if (haptic_steps == 2) {
									// This branch is typically for buttons or simple 2-state controls using the main control name.
									// control_name_str is already padded to 13 bytes.
									dummy_step_names_storage.push_back(control_name_str);
									dummy_step_names_storage.push_back(control_name_str);
								} else if constexpr (std::is_base_of_v<FlipSwitch, T> ||
													 std::is_base_of_v<SlideSwitch, T> ||
													 std::is_base_of_v<KnobSnapped, T>)
								{
									const auto &el = arg;
									pr_dbg("el.num_pos: %u\n", el.num_pos);
									for (uint8_t i = 0; i < el.num_pos; ++i) {
										bool is_valid_name = false;
										std::string step_name;

										if constexpr (std::is_same_v<T, KnobSnapped>) {
											// KnobSnapped uses const char* - check for nullptr
											if (el.pos_names[i] != nullptr) {
												step_name = std::string(el.pos_names[i]);
												pr_dbg("step_name knobsnapped: %s\n", step_name.c_str());
												is_valid_name = true;
											}
										} else {
											// FlipSwitch and SlideSwitch use std::string_view - check for empty
											if (!el.pos_names[i].empty()) {
												step_name = std::string(el.pos_names[i]);
												pr_dbg("step_name flipswitch: %s\n", step_name.c_str());
												is_valid_name = true;
											}
										}

										if (is_valid_name) {
											if (step_name.length() > 12) {
												step_name = step_name.substr(0, 12);
											}
											step_name.resize(13, '\0');
											dummy_step_names_storage.push_back(step_name);
											pr_dbg("dummy_step_names_storage: %s\n", step_name.c_str());
										}
									}
									// Update haptic_steps to match actual number of valid names collected
									haptic_steps = dummy_step_names_storage.size();
									pr_dbg("Updated haptic_steps to actual count: %u\n", haptic_steps);
								} else {
									pr_dbg("Creating dummy step names\n");
									for (uint8_t i = 0; i < haptic_steps; ++i) {
										std::string name = "S" + std::to_string(i);
										if (name.length() > 12) {
											name = name.substr(0, 12);
										}
										name.resize(13, '\0');
										dummy_step_names_storage.push_back(name);
									}
								}

								// MODIFIED: Populate dummy_step_names_ptrs AFTER dummy_step_names_storage is complete
								if (!dummy_step_names_storage.empty()) {
									dummy_step_names_ptrs.reserve(dummy_step_names_storage.size());
									for (const auto &s_str : dummy_step_names_storage) {
										dummy_step_names_ptrs.push_back(s_str.c_str());
									}
									step_names_ptr = dummy_step_names_ptrs.data();
								}
							}

							if (haptic_steps == 2) { // This condition was for calling set_switch_control_config
								// TODO lazy start
								msg.set_control_config(
									ControlType::SWITCH,
									0,							  // setup_index
									next_midi_roto_switch_index_, // RotoControl's own knob/control index
									ControlMode::CC_7BIT,
									k.midi_chan == 0 ? 1 : k.midi_chan,
									k.cc_num(), // RotoControl's parameter index
									0,			// nrpn_address
									0,
									127,
									control_name_ptr,
									0,			 // color_scheme
									haptic_mode, // haptic_mode for switch
									0x00,		 // led_on_color
									0x01,		 // led_off_color
									0,
									step_names_ptr);
								next_midi_roto_switch_index_++;
							} else {
								pr_dbg("Setting knob control config, setup_index: %d, control_index: %d, haptic_mode: "
									   "%d, haptic_steps: %d\n min_val_u16: %d, max_val_u16: %d, control_name: %s\n",
									   0,
									   next_midi_roto_knob_index_,
									   haptic_mode,
									   haptic_steps,
									   min_val_u16,
									   max_val_u16,
									   control_name_ptr);
								if (step_names_ptr && haptic_steps > 0) {
									pr_dbg("step_names: [");
									for (uint8_t i = 0; i < haptic_steps; ++i) {
										pr_dbg("%s'%s'",
											   (i > 0 ? ", " : ""),
											   step_names_ptr[i] ? step_names_ptr[i] : "null");
									}
									pr_dbg("]\n");
								} else {
									pr_dbg("step_names: null or empty\n");
								}
								msg.set_control_config(
									ControlType::KNOB,
									0,							// setup_index
									next_midi_roto_knob_index_, // RotoControl's own knob/control index
									ControlMode::CC_7BIT,
									k.midi_chan == 0 ? 1 : k.midi_chan,
									k.cc_num(), // RotoControl's parameter index
									0,			// nrpn_address
									min_val_u16,
									max_val_u16,
									control_name_ptr,
									0, // color_scheme
									haptic_mode,
									0xFF, // indent_pos1
									0xFF, // indent_pos2
									haptic_steps,
									step_names_ptr);
								next_midi_roto_knob_index_++;
							}
						}
					},
					element_variant);
				break;
			}
		}
	}
	msg.end_config_update();
	msg.set_setup(0x00);
	msg.send_all_commands(cdc_buffer);
}

} // namespace MetaModule
