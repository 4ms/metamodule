#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/elements/draw_img.hh"
#include "gui/helpers/units_conversion.hh"
#include "gui/images/image_fs.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include <cmath>
#include <cstdint>

namespace MetaModule
{

namespace ElementDrawerImpl
{

inline lv_obj_t *draw_element(const BaseElement &, lv_obj_t *, uint32_t) {
	return nullptr;
}

//TODO: once we move image into BaseElement, all these overloads go away
inline lv_obj_t *draw_element(const JackElement &el, lv_obj_t *canvas, uint32_t module_height) {
	auto img = PNGFileSystem::read(el.image);
	auto obj = draw_image(BaseElement(el), img, canvas, module_height);
	return obj;
}

inline lv_obj_t *draw_element(const Knob &el, lv_obj_t *canvas, uint32_t module_height) {
	auto img = PNGFileSystem::read(el.image);
	auto obj = draw_image(BaseElement(el), img, canvas, module_height);
	return obj;
}

inline lv_obj_t *draw_element(const Button &el, lv_obj_t *canvas, uint32_t module_height) {
	auto img = PNGFileSystem::read(el.image);
	auto obj = draw_image(BaseElement(el), img, canvas, module_height);
	return obj;
}

inline lv_obj_t *draw_element(const FlipSwitch &el, lv_obj_t *canvas, uint32_t module_height) {
	auto img = PNGFileSystem::read(el.frames[0]);
	auto obj = draw_image(BaseElement(el), img, canvas, module_height);
	return obj;
}

// Draw slider with its handle as a sub-object
inline lv_obj_t *draw_element(const Slider &el, lv_obj_t *canvas, uint32_t module_height) {
	auto img = PNGFileSystem::read(el.image);
	auto obj = draw_image(BaseElement(el), img, canvas, module_height);
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

//Draw slide switch with handle as a sub-object
inline lv_obj_t *draw_element(const SlideSwitch &el, lv_obj_t *canvas, uint32_t module_height) {
	auto body_img = PNGFileSystem::read(el.image_bg);
	if (body_img == nullptr)
		return nullptr;

	auto obj = draw_image(BaseElement(el), body_img, canvas, module_height);

	lv_obj_t *handle;

	// Use image for handle, if image exists
	if (el.image_fg.size()) {
		handle = lv_img_create(obj);
		auto handle_img = PNGFileSystem::read(el.image_fg);
		if (handle_img)
			draw_image(0, 0, Coords::TopLeft, handle_img, handle, module_height);
		else
			pr_err("No handle image found for %.*s!\n", (int)el.image_fg.size(), el.image_fg.data());

	} else {
		// If there's no handle img, draw a handle with LVGL styles:
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
		return ElementDrawerImpl::draw_element(element, canvas, module_height);
	}
};

} // namespace MetaModule
