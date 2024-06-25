#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "metaparams.hh"
#include "params_state.hh"
#include "util/analyzed_signal.hh"

namespace MetaModule
{

struct CalCheck {
	CalCheck(ParamsMidiState &params, MetaParams &metaparams)
		: params{params}
		, metaparams{metaparams} {
	}

	void update() {
		update_cal_ins_routine();
	}

	void start() {
		lv_hide(ui_SystemCalibrationButton);
		lv_hide(ui_SystemCalCheckButton);
		lv_hide(ui_SystemResetInternalPatchesCont);
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_hide(ui_CalibrationButtonCont);

		lv_show(ui_CalibrationProcedureCont);
		lv_show(ui_CalibrationInputStatusCont);

		lv_label_set_text(ui_CalibrationInstructionLabel,
						  "Knob A sets the voltage on all output jacks, from -10V to +10V in 1.0V steps.\nInput jack "
						  "readings are shown below:");

		for (unsigned chan = 0; chan < PanelDef::NumAudioIn; chan++) {
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
		lv_show(ui_SystemCalCheckButton);
		lv_show(ui_SystemResetInternalPatchesCont);

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
		for (unsigned chan = 0; chan < PanelDef::NumAudioIn; chan++) {

			if (params.is_input_plugged(chan)) {

				set_input_plugged(chan, true);

				in_signals[chan].update(metaparams.ins[chan]);

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

		} else if (!plugged && jack_plugged[chan]) {
			jack_plugged[chan] = false;
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
			lv_label_set_text_fmt(label, "In %d:\n--", chan + 1);
		}
	}

private:
	ParamsMidiState &params;
	MetaParams &metaparams;

	bool visible = false;

	std::array<bool, PanelDef::NumAudioIn> jack_plugged{};

	static constexpr float coef = 1.f / 4.f;
	std::array<AnalyzedSig, PanelDef::NumAudioIn> in_signals{coef, coef, coef, coef, coef, coef};

	std::array<lv_obj_t *, PanelDef::NumAudioIn> input_status_labels{
		ui_CalibrationIn1Label,
		ui_CalibrationIn2Label,
		ui_CalibrationIn3Label,
		ui_CalibrationIn4Label,
		ui_CalibrationIn5Label,
		ui_CalibrationIn6Label,
	};
};

} // namespace MetaModule
