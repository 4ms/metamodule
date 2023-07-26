#pragma once
#include "lvgl.h"

struct CableDrawer {

	void draw() {
		// lv_canvas_fill_bg(page->cable_layer, lv_color_white(), LV_OPA_0);

		// Draw all cables connected to this module
		// TODO: gotta be a cleaner way to do this...
		// 		push Jack{c.out}, this_module_obj, Jack{in}, outmodule_obj
		// 		draw_cable(Jack out, Jack in, lv_obj_t *out_module, lv_obj_t *in_module);
		// const auto thismoduleinfo = ModuleFactory::getModuleInfo(this_slug);
		// if (thismoduleinfo.width_hp > 0) {
		//for (const auto &c : patch.int_cables) {
		//	// Draw cable(s) if out jack is on this module
		//	if (c.out.module_id == module_id) {
		//		auto end = DrawHelper::get_jack_xy(thismoduleinfo.OutJacks, this_module_obj, c.out, height);

		//		// Draw a cable from this out jack to all in jacks it's connected to
		//		for (const auto &in : c.ins) {
		//			// Iterate through all modules to find the one with a matching id (TODO: better way to do this?)
		//			for (auto inmodule_obj : page->modules) {
		//				uint32_t t_module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(inmodule_obj)));
		//				if (t_module_id == in.module_id) {
		//					const auto inmodule_info =
		//						ModuleFactory::getModuleInfo(patch.module_slugs[t_module_id]);
		//					auto start = DrawHelper::get_jack_xy(inmodule_info.InJacks, inmodule_obj, in, height);
		//					page->cable_drawline_dsc.color = DrawHelper::get_cable_color(in);
		//					DrawHelper::draw_cable(start, end, page->cable_layer, &page->cable_drawline_dsc);
		//					break;
		//				}
		//			}
		//		}
		//		continue; //We drew the output to all inputs, no need to check if any inputs are on this module
		//	}
		//	// Draw cable if in jack is on this module
		//	for (const auto &in : c.ins) {
		//		if (in.module_id == module_id) {
		//			auto start = DrawHelper::get_jack_xy(thismoduleinfo.InJacks, this_module_obj, in, height);
		//			//Find output jack on another module
		//			for (auto outmodule_obj : page->modules) {
		//				uint32_t t_module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(outmodule_obj)));
		//				if (t_module_id == c.out.module_id) {
		//					auto outmodule_info = ModuleFactory::getModuleInfo(patch.module_slugs[t_module_id]);
		//					auto end =
		//						DrawHelper::get_jack_xy(outmodule_info.OutJacks, outmodule_obj, c.out, height);
		//					page->cable_drawline_dsc.color = DrawHelper::get_cable_color(in);
		//					DrawHelper::draw_cable(start, end, page->cable_layer, &page->cable_drawline_dsc);
		//					break;
		//				}
		//			}
		//		}
		//	}
		// }
		// }
	}
};
