#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/helpers/units_conversion.hh"
#include "gui/images/image_fs.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cmath>
#include <cstdint>

namespace MetaModule::ElementDrawerImpl
{

inline void
draw_image(float x, float y, Coords coord_ref, const lv_img_dsc_t *img, lv_obj_t *obj, uint32_t module_height) {
	if (!img) {
		pr_dbg("draw_image: image not found\n");
		return;
	}
	lv_img_set_src(obj, img);

	float width = img->header.w;
	float height = img->header.h;

	float zoom = module_height / 240.f;

	x = fix_zoomed_coord(coord_ref, x, width, zoom);
	y = fix_zoomed_coord(coord_ref, y, height, zoom);

	uint16_t lv_zoom = 256.f * zoom;
	lv_img_set_zoom(obj, lv_zoom);
	lv_img_set_size_mode(obj, LV_IMG_SIZE_MODE_VIRTUAL);
	lv_img_set_antialias(obj, true);
	lv_obj_set_align(obj, LV_ALIGN_TOP_LEFT);

	uint16_t pos_x = std::round(x);
	uint16_t pos_y = std::round(y);
	lv_obj_set_pos(obj, pos_x, pos_y);
	lv_img_set_pivot(obj, width / 2.f, height / 2.f);

	//DEBUG positions:
	// lv_obj_set_style_outline_color(obj, lv_palette_main(LV_PALETTE_BLUE), LV_STATE_DEFAULT);
	// lv_obj_set_style_outline_width(obj, 1, LV_STATE_DEFAULT);
	// if (img == &::BefacoSlidePotSmall) {
	// 	printf("Draw: %f, %f -> %d, %d img:[%d x %d]\n", x, y, pos_x, pos_y, (int)width, (int)height);
	// }
}

// Create an object as a sub-object of the canvas, and draw img in it
// Returns the object
inline lv_obj_t *draw_image(const BaseElement &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
	if (img == nullptr)
		return nullptr;

	lv_obj_t *obj = lv_img_create(canvas);
	float x = ModuleInfoBase::mm_to_px(el.x_mm, module_height);
	float y = ModuleInfoBase::mm_to_px(el.y_mm, module_height);
	draw_image(x, y, el.coords, img, obj, module_height);
	lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_size(obj, img->header.w, img->header.h);
	lv_obj_set_style_pad_all(obj, 0, LV_STATE_DEFAULT);
	lv_obj_add_flag(obj, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
	return obj;
}

} // namespace MetaModule::ElementDrawerImpl
