#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct HardwareCheckPopup {
	HardwareCheckPopup(ParamsMidiState &params, MetaParams &metaparams)
		: params{params}
		, metaparams{metaparams}
		, group(lv_group_create()) {

		lv_group_add_obj(group, ui_Button1);
		// lv_group_add_obj(group, ui_Button2);

		lv_hide(ui_HWTestPagePanel);
	}

	void show(lv_group_t *parent_group) {
		base_group = parent_group;
		lv_obj_set_parent(ui_HWTestPagePanel, lv_layer_top());

		lv_show(ui_HWTestPagePanel);
		lv_group_activate(group);
		lv_group_focus_obj(ui_Button1);
		visible = true;
	}

	void hide() {
		lv_hide(ui_HWTestPagePanel);
		lv_group_activate(base_group);
		lv_group_set_editing(base_group, false);
		visible = false;
	}

	bool is_visible() {
		return visible;
	}

	void update() {

		for (auto [i, pot] : enumerate(params.knobs)) {
			if (pot < pot_min[i])
				pot_min[i] = pot;
			if (pot > pot_max[i])
				pot_max[i] = pot;
			pot_iir[i] = pot_iir[i] * iir_coef_inv + pot * iir_coef;
		}

		if ((last_refresh_check_tm - HAL_GetTick()) > 200) {
			last_refresh_check_tm = HAL_GetTick();

			for (auto [i, pot] : enumerate(params.knobs)) {
				auto clamped_val = std::clamp<unsigned>(pot_iir[i] * 100.f, 0u, 99u);
				if (clamped_val != last_pot_vals[i]) {
					lv_label_set_text_fmt(knob_labels[i], "%02d", clamped_val);
					last_pot_vals[i] = clamped_val;
					lv_obj_set_style_text_color(knob_labels[i], Gui::palette_main[0], LV_PART_MAIN);
				} else
					lv_obj_set_style_text_color(knob_labels[i], lv_color_white(), LV_PART_MAIN);

				// pr_dbg("Pot %zu: iir=%d min=%d max=%d range=%d\r\n",
				// 	   i,
				// 	   (int)(4096.f * pot_iir[i]),
				// 	   (int)(4096.f * pot_min[i]),
				// 	   (int)(4096.f * pot_max[i]),
				// 	   (int)(4096.f * (pot_max[i] - pot_min[i])));

				pot_iir[i] = pot;
				pot_min[i] = 4096.f;
				pot_max[i] = 0.f;
			}

			auto b = [j = params.jack_senses](uint32_t bit) -> int {
				return (j >> (jacksense_pin_order[bit])) & 1;
			};

			for (unsigned i = 8; i < 16; i++) {
				lv_label_set_text(outjack_labels[i - 8], b(i) ? "X" : "_");
				lv_obj_set_style_text_color(
					outjack_labels[i - 8], b(i) ? Gui::palette_main[2] : lv_color_white(), LV_PART_MAIN);
			}
			// pr_dbg("Outs patched: %d %d %d %d %d %d %d %d\n", b(8), b(9), b(10), b(11), b(12), b(13), b(14), b(15));

			lv_label_set_text(ui_RotaryButton1, metaparams.meta_buttons[0].is_high() ? "X" : "_");
			lv_label_set_text(ui_RotaryButton, metaparams.rotary_button.is_high() ? "X" : "_");

			lv_label_set_text(ui_GateInData1, params.gate_ins[0].is_high() ? "X" : "-");
			lv_label_set_text(ui_GateInData2, params.gate_ins[1].is_high() ? "X" : "-");

			lv_obj_set_style_text_color(ui_GateInData1, b(6) ? Gui::palette_main[2] : lv_color_white(), LV_PART_MAIN);
			lv_obj_set_style_text_color(ui_GateInData2, b(7) ? Gui::palette_main[2] : lv_color_white(), LV_PART_MAIN);

			// pr_dbg("Button: %d GateIn1: %d [%d] GateIn2: %d [%d] \r\n",
			// 	   metaparams.meta_buttons[0].is_high() ? 1 : 0,
			// 	   params.gate_ins[0].is_high() ? 1 : 0,
			// 	   b(6),
			// 	   params.gate_ins[1].is_high() ? 1 : 0,
			// 	   b(7));

			for (auto [i, ain] : enumerate(metaparams.ins)) {
				auto clamped_val = std::clamp<int>(ain * 100.f, -999, 999);
				if (clamped_val != last_injack_vals[i]) {
					lv_label_set_text_fmt(injack_labels[i], "%03d", clamped_val);
					lv_obj_set_style_text_color(injack_labels[i], Gui::palette_main[0], LV_PART_MAIN);
					last_injack_vals[i] = clamped_val;
				} else
					lv_obj_set_style_text_color(
						injack_labels[i], b(i) ? Gui::palette_main[2] : lv_color_white(), LV_PART_MAIN);

				// pr_dbg("AIN %zu: [%d] iir=%d min=%d max=%d range=%d\r\n",
				// 	   i,
				// 	   b(i),
				// 	   (int)(ain.iir * 32768.f),
				// 	   (int)(ain.min * 32768.f),
				// 	   (int)(ain.max * 32768.f),
				// 	   (int)((ain.max - ain.min) * 32768.f));
			}
		}
	}

private:
	ParamsMidiState &params;
	MetaParams &metaparams;

	lv_group_t *group;
	lv_group_t *base_group = nullptr;
	bool visible = false;

	float pot_min[12]{9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999};
	float pot_max[12]{};
	float pot_iir[12]{};

	static constexpr float iir_coef = 1.f / 1000.f;
	static constexpr float iir_coef_inv = 1.f - iir_coef;

	std::array<lv_obj_t *, 12> knob_labels{
		ui_KnobData1,
		ui_KnobData2,
		ui_KnobData3,
		ui_KnobData4,
		ui_KnobData5,
		ui_KnobData6,
		ui_KnobData7,
		ui_KnobData8,
		ui_KnobData9,
		ui_KnobData10,
		ui_KnobData11,
		ui_KnobData12,
	};
	std::array<unsigned, 12> last_pot_vals{};

	std::array<lv_obj_t *, 8> outjack_labels{
		ui_OutJackPatchedData1,
		ui_OutJackPatchedData2,
		ui_OutJackPatchedData3,
		ui_OutJackPatchedData4,
		ui_OutJackPatchedData5,
		ui_OutJackPatchedData6,
		ui_OutJackPatchedData7,
		ui_OutJackPatchedData8,
	};

	std::array<lv_obj_t *, 6> injack_labels{
		ui_InJackData1,
		ui_InJackData2,
		ui_InJackData3,
		ui_InJackData4,
		ui_InJackData5,
		ui_InJackData6,
	};
	std::array<int, 6> last_injack_vals{};

	uint32_t last_refresh_check_tm = 0;
};

} // namespace MetaModule
