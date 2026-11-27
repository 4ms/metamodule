#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "console/pr_dbg.hh"
#include "gui/elements/module_art.hh"
#include "gui/elements/scaled_image.hh"
#include "gui/helpers/units_conversion.hh"
#include "gui/images/paths.hh"
#include "gui/styles.hh"
#include "lvgl.h"
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

// What to give an lv_img to draw a component image in a module of some height
struct ImageSource {
	std::string src;
	uint32_t w;
	uint32_t h;
	float zoom;
};

inline std::optional<ImageSource> image_source(std::string const &img_path, uint32_t module_height) {
#if defined(THORVG_SVG_LOADER_SUPPORT)
	// The image at the size it's drawn at, from its SVG file: see scaled_image.hh
	auto scaled_src = ScaledImage::make_src(img_path, module_height);
	if (auto sz = get_image_size(scaled_src))
		return ImageSource{scaled_src, sz->w, sz->h, 1.f};
#else
	// The image as made for a module that's ModuleArtHeightPx high, zoomed by LVGL
	if (auto sz = get_image_size(img_path))
		return ImageSource{img_path, sz->w, sz->h, module_height / (float)ModuleArtHeightPx};
#endif

	return {};
}

inline void draw_image(float x, float y, Coords coord_ref, ImageSource const &img, lv_obj_t *obj) {

	lv_img_set_src(obj, img.src.c_str());

	float width = img.w;
	float height = img.h;

	x = fix_zoomed_coord(coord_ref, x, width, img.zoom);
	y = fix_zoomed_coord(coord_ref, y, height, img.zoom);

	uint16_t lv_zoom = 256.f * img.zoom;
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

	if (auto img = Impl::image_source(img_path, module_height)) {
		Impl::draw_image(x, y, coord_ref, *img, obj);
	} else
		pr_warn("Could not read image '%s'\n", img_path.c_str());
}

// Returns the source to give an lv_img that is showing a component image, to show another one
// in its place (a different frame of a switch, a pressed button...)
inline std::string image_src_like(lv_obj_t *img_obj, std::string_view img_filename) {
	auto img_path = ComponentImages::get_comp_path(img_filename);

#if defined(THORVG_SVG_LOADER_SUPPORT)
	// For the same module height as the image it replaces (see scaled_image.hh)
	auto cur_src = static_cast<const char *>(lv_img_get_src(img_obj));
	if (cur_src && img_path.length())
		return ScaledImage::make_src(img_path, ScaledImage::module_height_of(cur_src));
#endif

	return img_path;
}

// Create an object as a sub-object of the canvas, and draw img in it
// Returns the object
inline lv_obj_t *
draw_image(const BaseElement &el, std::string_view img_filename, lv_obj_t *canvas, uint32_t module_height) {

	auto img_path = ComponentImages::get_comp_path(img_filename);
	if (img_path.length() > 0) {
		if (auto img = Impl::image_source(img_path, module_height)) {
			lv_obj_t *obj = lv_img_create(canvas);
			float x = mm_to_px(el.x_mm, module_height);
			float y = mm_to_px(el.y_mm, module_height);
			Impl::draw_image(x, y, el.coords, *img, obj);
			lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
			lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
			lv_obj_set_size(obj, img->w, img->h);
			lv_obj_set_style_pad_all(obj, 0, LV_STATE_DEFAULT);
			lv_obj_add_flag(obj, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
			return obj;
		}
	}

	if (img_path.size())
		pr_warn("Could not read image `%s` for %s\n", img_path.c_str(), el.short_name.data());
	else
		pr_trace("No image given for %.*s\n", (int)el.short_name.size(), el.short_name.data());

	return nullptr;
}

} // namespace MetaModule::ElementDrawer
