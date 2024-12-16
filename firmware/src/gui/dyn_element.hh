#pragma once
#include "app/ModuleWidget.hpp"
#include "gui/dyn_element/base_dyn_draw.hh"
#include "gui/dyn_element/rack_dyn_draw.hh"
#include "lvgl.h"
#include "patch_play/patch_playloader.hh"
#include <algorithm>
#include <memory>

namespace MetaModule
{

class DynamicElementDraw {
public:
	DynamicElementDraw(PatchPlayLoader &patch_playloader)
		: patch_playloader{patch_playloader} {
	}

	void prepare_module(unsigned this_module_id, lv_obj_t *module_canvas) {
		drawer.reset();

		if (auto rack_module = patch_playloader.get_plugin_module<rack::engine::Module>(this_module_id)) {
			if (rack_module->module_widget) {
				drawer = std::make_unique<RackDynDraw>(rack_module->module_widget);
			}
		}

		else if (auto native_module = patch_playloader.get_plugin_module<CoreProcessor>(this_module_id))
		{
			// TODO:
			(void)native_module;
		}

		if (drawer) {
			// create canvas, same size as module
			lv_obj_refr_size(module_canvas);
			auto w = lv_obj_get_width(module_canvas);
			auto h = lv_obj_get_height(module_canvas);
			auto canvas = lv_canvas_create(module_canvas);
			lv_obj_set_pos(canvas, 0, 0);
			lv_obj_set_size(canvas, w, h);

			// setup backing buffer for canvas
			buffer.resize(LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(w, h));
			std::ranges::fill(buffer, 0);
			lv_canvas_set_buffer(canvas, buffer.data(), w, h, LV_IMG_CF_TRUE_COLOR_ALPHA);

			drawer->prepare(canvas);
		}
	}

	void draw() {
		if (drawer) {
			drawer->draw();
		}
	}

	void blur() {
		if (drawer)
			drawer->blur();
		buffer.clear();
	}

private:
	PatchPlayLoader &patch_playloader;
	std::unique_ptr<BaseDynDraw> drawer{};
	std::vector<char> buffer;
};

} // namespace MetaModule
