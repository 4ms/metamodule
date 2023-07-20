#pragma once
#include "pages/base.hh"
#include "pages/gui-guider/custom.h"
#include "pages/gui-guider/gui_guider.h"

namespace MetaModule
{
struct KnobView3 : PageBase {
	KnobView3(PatchInfo info)
		: PageBase{info} {
	}

	void init() override {
		// setup_scr_Knob_view3(ui);
		ui->Knob_view3 = lv_obj_create(nullptr);
		init_bg(ui->Knob_view3);

		// lv_arc_set_adjustable(ui->Knob_view3_arc_1, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_2, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_3, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_4, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_5, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_6, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_7, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_8, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_9, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_10, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_11, true);
		// lv_arc_set_adjustable(ui->Knob_view3_arc_12, true);
	}

	void update() override {
		//GUI Guider knobs are laid out like this:
		//arc_2 arc_3 arc_6
		//arc_1 arc_5 arc_4
		//Param1 Param2 Param3
		//Param4 Param5 Param6
		// lv_arc_set_value(ui->Knob_view3_arc_2, params.knobs[0] * 100.f);
		// lv_arc_set_value(ui->Knob_view3_arc_3, params.knobs[1] * 100.f);
		// lv_arc_set_value(ui->Knob_view3_arc_6, params.knobs[2] * 100.f);
		// lv_arc_set_value(ui->Knob_view3_arc_1, params.knobs[3] * 100.f);
		// lv_arc_set_value(ui->Knob_view3_arc_5, params.knobs[4] * 100.f);
		// lv_arc_set_value(ui->Knob_view3_arc_4, params.knobs[5] * 100.f);

		//GUI Guider knobs are laid out like this:
		//  X     Y      Z      L     R     Q
		//arc_7 arc_12 arc_8 arc_11 arc_9 arc_10
		// lv_arc_set_value(ui->Knob_view3_arc_7, params.knobs[6] * 100.f);
		// lv_arc_set_value(ui->Knob_view3_arc_12, params.knobs[7] * 100.f);
		// lv_arc_set_value(ui->Knob_view3_arc_8, params.knobs[8] * 100.f);
		// lv_arc_set_value(ui->Knob_view3_arc_11, params.knobs[9] * 100.f);  //PotL
		// lv_arc_set_value(ui->Knob_view3_arc_9, params.knobs[10] * 100.f);  //PotR
		// lv_arc_set_value(ui->Knob_view3_arc_10, params.knobs[11] * 100.f); //PotQ
	}

	void focus(PageChangeDirection dir) override {
		PageBase::focus(dir);
		update_knob_names();
	}

	void update_knob_names() {
		// if (patch_player.is_loaded) {
		// 	lv_label_set_text(ui->Knob_view3_label_9, get_knob_list_string(0, 16).c_str());
		// 	lv_label_set_text(ui->Knob_view3_label_8, get_knob_list_string(1, 16).c_str());
		// 	lv_label_set_text(ui->Knob_view3_label_12, get_knob_list_string(2, 16).c_str());
		// 	lv_label_set_text(ui->Knob_view3_label_13, get_knob_list_string(3, 16).c_str());
		// 	lv_label_set_text(ui->Knob_view3_label_10, get_knob_list_string(4, 16).c_str());
		// 	lv_label_set_text(ui->Knob_view3_label_11, get_knob_list_string(5, 16).c_str());

		// 	lv_label_set_text(ui->Knob_view3_label_2, get_knob_list_string(6, 6).c_str());	//X
		// 	lv_label_set_text(ui->Knob_view3_label_3, get_knob_list_string(7, 6).c_str());	//Y
		// 	lv_label_set_text(ui->Knob_view3_label_4, get_knob_list_string(8, 6).c_str());	//Z
		// 	lv_label_set_text(ui->Knob_view3_label_5, get_knob_list_string(9, 6).c_str());	//L
		// 	lv_label_set_text(ui->Knob_view3_label_6, get_knob_list_string(10, 6).c_str()); //R
		// 	lv_label_set_text(ui->Knob_view3_label_7, get_knob_list_string(11, 6).c_str()); //Q
		// }
	}

	std::string get_knob_list_string(unsigned panel_knob_id, unsigned max_chars = 0) {
		const StaticString<15> &alias_name = patch_player.get_panel_knob_name(panel_knob_id);
		if (alias_name.length())
			return alias_name;

		std::vector<MappedKnob> &mapped_knobs = patch_player.knob_conns[panel_knob_id];
		//TODO: handle multi-maps
		if (mapped_knobs.size() == 0)
			return "-";

		std::string slug{patch_player.get_module_name(mapped_knobs[0].module_id)};
		auto &info = ModuleFactory::getModuleInfo(slug.c_str());
		if (info.width_hp == 0)
			return slug;

		std::string short_name{info.Knobs[mapped_knobs[0].param_id].short_name};
		int slug_len = slug.length() + 2;
		if (max_chars == 0 || (slug_len + short_name.length()) <= max_chars)
			return std::string{slug}.append(": ").append(short_name);
		else if (short_name.length() <= max_chars)
			return short_name;
		else
			return short_name.substr(0, max_chars);
	}
};
} // namespace MetaModule
