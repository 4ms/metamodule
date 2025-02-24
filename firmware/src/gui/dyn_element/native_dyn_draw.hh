#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "base_dyn_draw.hh"
#include "lvgl.h"
#include "util/overloaded.hh"
// #include "debug.hh"
// #include "pr_dbg.hh"
#include <memory>

namespace MetaModule
{

struct DynDraw : BaseDynDraw {

	DynDraw(CoreProcessor *module, std::string_view slug)
		: module{module} {
		auto info = ModuleFactory::getModuleInfo(slug);
		unsigned i = 0;
		for (auto const &el : info.elements) {
			std::visit(overloaded{
						   [](BaseElement const &e) {},
						   [i = i, this](DynamicGraphicDisplay const &e) { dyn_element_ids.push_back(i); },
					   },
					   el);
		}
		i++;
	}

	void prepare(lv_obj_t *widget_canvas, unsigned px_per_3U) override {
		canvas = widget_canvas;

		lv_obj_refr_size(canvas);
		width = lv_obj_get_width(canvas);
		height = lv_obj_get_height(canvas);
	}

	void draw() override {
		if (!canvas || !lv_obj_is_valid(canvas) || !lv_obj_is_visible(canvas))
			return;

		clear_canvas();
		auto lv_img_src = lv_canvas_get_img(canvas);
		auto lv_img_buf = const_cast<uint8_t *>(lv_img_src->data);
		auto pixels = reinterpret_cast<CoreProcessor::Pixel *>(lv_img_buf);
		if (module) {
			[[maybe_unused]] auto changed = module->get_canvas_pixels(0, pixels, width, height);
		}
	}

	void blur() override {
	}

	~DynDraw() override = default;

private:
	CoreProcessor *module = nullptr;
	std::vector<unsigned> dyn_element_ids;
	lv_obj_t *canvas{};
	lv_coord_t width{};
	lv_coord_t height{};

	// Takes ~50us for A 14HP-ish module
	void clear_canvas() {
		if (canvas) {
			auto buf = lv_canvas_get_img(canvas);
			if (buf) {
				memset((void *)buf->data, 0, width * height * 3);
			}
		}
	}
};

} // namespace MetaModule
