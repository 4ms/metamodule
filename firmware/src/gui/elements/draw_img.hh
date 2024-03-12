#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/helpers/units_conversion.hh"
#include "gui/images/paths.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cmath>
#include <cstdint>
#include <optional>
#include <string>

namespace MetaModule::ElementDrawer
{

struct ImageSize {
	uint32_t w;
	uint32_t h;
};

inline std::optional<ImageSize> get_image_size(std::string_view img_path) {
	lv_img_header_t img_header;
	if (lv_img_decoder_get_info(img_path.data(), &img_header) == LV_RES_OK)
		return ImageSize{img_header.w, img_header.h};
	else
		return {};
}

namespace Impl
{

inline void draw_image(float x,
					   float y,
					   lv_coord_t w,
					   lv_coord_t h,
					   Coords coord_ref,
					   std::string const &img_path,
					   lv_obj_t *obj,
					   uint32_t module_height) {

	lv_img_set_src(obj, img_path.c_str());

	float width = w;
	float height = h;

	float zoom = module_height / 240.f;

	x = fix_zoomed_coord(coord_ref, x, width, zoom);
	y = fix_zoomed_coord(coord_ref, y, height, zoom);

	uint16_t lv_zoom = 256.f * zoom;
	lv_img_set_zoom(obj, lv_zoom);
	lv_img_set_size_mode(obj, LV_IMG_SIZE_MODE_VIRTUAL);
	lv_img_set_antialias(obj, true);
	lv_obj_set_align(obj, LV_ALIGN_TOP_LEFT);

	int16_t pos_x = std::round(x);
	int16_t pos_y = std::round(y);
	lv_obj_set_pos(obj, pos_x, pos_y);
	lv_img_set_pivot(obj, width / 2.f, height / 2.f);
}
} // namespace Impl

// Draw the image into the given obj
inline void
draw_image(float x, float y, Coords coord_ref, std::string_view img_filename, lv_obj_t *obj, uint32_t module_height) {

	auto img_path = ComponentImages::get_comp_path(img_filename);

	if (auto sz = get_image_size(img_path)) {
		Impl::draw_image(x, y, sz->w, sz->h, coord_ref, img_path, obj, module_height);
	} else
		pr_warn("Could not read image %s\n", img_path.c_str());
}

// Create an object as a sub-object of the canvas, and draw img in it
// Returns the object
inline lv_obj_t *
draw_image(const BaseElement &el, std::string_view img_filename, lv_obj_t *canvas, uint32_t module_height) {

	auto img_path = ComponentImages::get_comp_path(img_filename);
	if (img_path.length() > 0) {
		if (auto sz = get_image_size(img_path)) {
			lv_obj_t *obj = lv_img_create(canvas);
			float x = ModuleInfoBase::mm_to_px(el.x_mm, module_height);
			float y = ModuleInfoBase::mm_to_px(el.y_mm, module_height);
			Impl::draw_image(x, y, sz->w, sz->h, el.coords, img_path, obj, module_height);
			lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
			lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
			lv_obj_set_size(obj, sz->w, sz->h);
			lv_obj_set_style_pad_all(obj, 0, LV_STATE_DEFAULT);
			lv_obj_add_flag(obj, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
			return obj;
		}
	}

	pr_warn("Could not read image %s\n", img_path.c_str());
	return nullptr;
}

} // namespace MetaModule::ElementDrawer
