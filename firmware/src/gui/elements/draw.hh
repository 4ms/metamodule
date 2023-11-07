#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/helpers/units_conversion.hh"
#include "gui/images/component_images.hh"
#include "gui/images/image_fs.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cmath>
#include <cstdint>

namespace MetaModule
{

namespace ElementDrawerImpl
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
	// printf_("Draw el img pos:%d, %d img:[%d x %d]\n", pos_x, pos_y, (int)width, (int)height);
}

// Create an object as a sub-object of the canvas, and draw img in it
// Returns the object
inline lv_obj_t *
draw_element(const BaseElement &el, const lv_img_dsc_t *img, lv_obj_t *canvas, uint32_t module_height) {
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

// Draw slider with its handle as a sub-object
inline lv_obj_t *draw_element(const Slider &el, const lv_img_dsc_t *, lv_obj_t *canvas, uint32_t module_height) {
	auto img = PNGFileSystem::read(el.image);
	auto obj = draw_element(BaseElement(el), img, canvas, module_height);
	if (!obj)
		return nullptr;

	lv_obj_t *handle;
	if (el.image_handle.size()) {
		handle = lv_img_create(obj);
		auto handle_img = PNGFileSystem::read(el.image_handle);
		if (handle_img)
			draw_image(0, 0, Coords::TopLeft, handle_img, handle, module_height);
		else
			pr_err("No handle image found for %.*s!\n", (int)el.image_handle.size(), el.image_handle.data());
	} else {
		lv_coord_t w = img ? img->header.w : 5;
		lv_coord_t h = img ? img->header.h : 5;
		handle = lv_obj_create(obj);
		if (w <= h) {
			// Vertical
			lv_obj_set_align(handle, LV_ALIGN_TOP_MID);
			lv_obj_set_width(handle, w);
			lv_obj_set_height(handle, module_height / 24);
			lv_obj_set_pos(handle, 0, 0);
			lv_obj_add_style(handle, &Gui::slider_handle_style, 0);
		} else {
			// Horizontal
			lv_obj_set_align(handle, LV_ALIGN_LEFT_MID);
			lv_obj_set_width(handle, module_height / 24); //10px at full scale
			lv_obj_set_height(handle, h);
			lv_obj_set_pos(handle, 0, 0);
			lv_obj_add_style(handle, &Gui::slider_handle_style, 0);
		}
	}
	return obj;
}

inline lv_obj_t *draw_element(const Knob &el, const lv_img_dsc_t *, lv_obj_t *canvas, uint32_t module_height) {
	auto img = PNGFileSystem::read(el.image);
	auto obj = draw_element(BaseElement(el), img, canvas, module_height);
	return obj;
}

inline lv_obj_t *draw_element(const Button &el, const lv_img_dsc_t *, lv_obj_t *canvas, uint32_t module_height) {
	auto img = PNGFileSystem::read(el.image);
	auto obj = draw_element(BaseElement(el), img, canvas, module_height);
	return obj;
}

inline lv_obj_t *draw_element(const FlipSwitch &el, const lv_img_dsc_t *, lv_obj_t *canvas, uint32_t module_height) {
	auto img = PNGFileSystem::read(el.frames[0]);
	auto obj = draw_element(BaseElement(el), img, canvas, module_height);
	return obj;
}

inline lv_obj_t *draw_element(const SlideSwitch &el, const lv_img_dsc_t *, lv_obj_t *canvas, uint32_t module_height) {
	auto body_img = PNGFileSystem::read(el.image_bg);
	if (body_img == nullptr)
		return nullptr;

	auto obj = draw_element(BaseElement(el), body_img, canvas, module_height);

	lv_obj_t *handle;

	if (el.image_fg.size()) {
		handle = lv_img_create(obj);
		auto handle_img = PNGFileSystem::read(el.image_fg);
		if (handle_img)
			draw_image(0, 0, Coords::TopLeft, handle_img, handle, module_height);
		else
			pr_err("No handle image found for %.*s!\n", (int)el.image_fg.size(), el.image_fg.data());

	} else {
		// If there's no fg img, draw a handle with LVGL styles:
		handle = lv_obj_create(obj);
		lv_obj_add_style(handle, &Gui::slider_handle_style, 0);
		if (body_img->header.h > body_img->header.w) //vertical
			lv_obj_set_size(handle, body_img->header.w - 2, body_img->header.h / el.num_pos);
		else
			lv_obj_set_size(handle, body_img->header.w / el.num_pos, body_img->header.h - 2);

		lv_obj_set_style_pad_all(handle, 0, LV_STATE_DEFAULT);
	}

	bool vert = body_img->header.w < body_img->header.h;
	lv_obj_set_align(handle, vert ? LV_ALIGN_TOP_MID : LV_ALIGN_LEFT_MID);
	lv_obj_set_pos(handle, 0, 0);
	return obj;
}

} // namespace ElementDrawerImpl

struct ElementDrawer {
	uint32_t module_height;
	lv_obj_t *canvas;

	template<typename T>
	lv_obj_t *draw_element(T element) {

		//TODO: once all image ptrs are moved into the types, remove this (and all the gui/images/BRAND/images.hh files)
		auto img = ElementImage::get_img(element);
		// if (img == nullptr)
		// 	return nullptr;

		return ElementDrawerImpl::draw_element(element, img, canvas, module_height);
	}
};

} // namespace MetaModule
