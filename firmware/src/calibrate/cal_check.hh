#pragma once
#include "expanders.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "params_state.hh"
#include "util/analyzed_signal.hh"

namespace MetaModule
{

struct CalCheck {
	CalCheck(ParamsMidiState &params)
		: params{params} {
	}

	void update() {
		update_cal_ins_routine();
	}

	void start() {
		lv_hide(ui_SystemCalibrationButton);
		lv_hide(ui_SystemExpCalibrationButton);
		lv_hide(ui_SystemCalCheckButton);
		lv_hide(ui_SystemResetInternalPatchesCont);
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_show(ui_CalibrationButtonCont);
		lv_hide(ui_CalibrationNextButton);
		lv_hide(ui_SystemHardwareCheckCont);

		lv_show(ui_CalibrationProcedureCont);
		lv_show(ui_CalibrationInputStatusCont);

		auto use_expander = Expanders::get_connected().ext_audio_connected;
		lv_show(ui_CalibrationIn7Label, use_expander);
		lv_show(ui_CalibrationIn8Label, use_expander);
		lv_show(ui_CalibrationIn9Label, use_expander);
		lv_show(ui_CalibrationIn10Label, use_expander);
		lv_show(ui_CalibrationIn11Label, use_expander);
		lv_show(ui_CalibrationIn12Label, use_expander);

		num_in_jacks = PanelDef::NumAudioIn;
		if (use_expander)
			num_in_jacks += AudioExpander::NumInJacks;

		lv_show(ui_CalibrationCancelButton);

		auto indev = lv_indev_get_next(nullptr);
		if (indev && indev->group) {
			lv_group_remove_obj(ui_CalibrationInstructionLabel);
			lv_group_add_obj(indev->group, ui_CalibrationInstructionLabel);
			lv_group_focus_next(indev->group);
		}

		lv_label_set_text(ui_CalibrationInstructionLabel,
						  "Knob A sets the voltage on all output jacks, from -10V to +10V in 1.0V steps.\nInput jack "
						  "readings are shown below:");

		for (unsigned chan = 0; chan < num_in_jacks; chan++) {
			auto *label = input_status_labels[chan];
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
			lv_label_set_text_fmt(label, "In %d:\n--", chan + 1);
		}

		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_SystemCalibrationTitle, LV_ANIM_OFF);

		visible = true;
	}

	void hide() {
		lv_hide(ui_CalibrationProcedureCont);
		lv_hide(ui_CalibrationInputStatusCont);
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_show(ui_SystemCalibrationButton);
		lv_show(ui_SystemExpCalibrationButton, Expanders::get_connected().ext_audio_connected);
		lv_show(ui_SystemCalCheckButton);
		lv_show(ui_SystemResetInternalPatchesCont);
		lv_show(ui_SystemHardwareCheckCont);

		lv_hide(ui_CalibrationButtonCont);
		lv_show(ui_CalibrationNextButton);

		lv_group_remove_obj(ui_CalibrationInstructionLabel);

		lv_group_focus_obj(ui_SystemCalCheckButton);
		visible = false;
	}

	bool is_visible() {
		return visible;
	}

private:
	void display_measurement(unsigned chan, float val) {
		auto *label = input_status_labels[chan];
		lv_label_set_text_fmt(label, "In %d:\n%.3fV", chan + 1, (double)val);
	}

	void update_cal_ins_routine() {
		for (unsigned chan = 0; chan < num_in_jacks; chan++) {
			auto jacksense_chan = chan < PanelDef::NumAudioIn ? chan : chan + 2;
			if (params.is_input_plugged(jacksense_chan)) {

				set_input_plugged(chan, true);

				in_signals[chan].update(params.smoothed_ins[chan].val());

				display_measurement(chan, in_signals[chan].iir);

			} else {
				set_input_plugged(chan, false);
			}
		}
	}

	void set_input_plugged(unsigned chan, bool plugged) {
		auto *label = input_status_labels[chan];

		if (plugged && !jack_plugged[chan]) {
			jack_plugged[chan] = true;
			lv_obj_set_style_outline_opa(label, LV_OPA_100, LV_PART_MAIN);
			lv_obj_scroll_to_view_recursive(label, LV_ANIM_ON);

		} else if (!plugged && jack_plugged[chan]) {
			jack_plugged[chan] = false;
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
			lv_label_set_text_fmt(label, "In %d:\n--", chan + 1);
		}
	}

private:
	ParamsMidiState &params;

	bool visible = false;

	unsigned num_in_jacks = PanelDef::NumAudioIn;

	std::array<bool, PanelDef::NumAudioIn + AudioExpander::NumInJacks> jack_plugged{};

	static constexpr float coef = 1.f / 2.f;
	std::array<AnalyzedSig, PanelDef::NumAudioIn + AudioExpander::NumInJacks> in_signals{
		coef, coef, coef, coef, coef, coef, coef, coef, coef, coef, coef, coef};

	std::array<lv_obj_t *, PanelDef::NumAudioIn + AudioExpander::NumInJacks> input_status_labels{
		ui_CalibrationIn1Label,
		ui_CalibrationIn2Label,
		ui_CalibrationIn3Label,
		ui_CalibrationIn4Label,
		ui_CalibrationIn5Label,
		ui_CalibrationIn6Label,
		ui_CalibrationIn7Label,
		ui_CalibrationIn8Label,
		ui_CalibrationIn9Label,
		ui_CalibrationIn10Label,
		ui_CalibrationIn11Label,
		ui_CalibrationIn12Label,
	};
};

} // namespace MetaModule
