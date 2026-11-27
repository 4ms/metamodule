#pragma once
#include "console/pr_dbg.hh"
#include "gui/elements/svg_file.hh"
#include "lvgl.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <list>
#include <string>
#include <string_view>
#include <vector>

// Component images (knobs, jacks, sliders, switches...) drawn from SVG files, at the size they
// appear on screen.
//
// The component PNGs are made for a module drawn 240px high (ModuleArtHeightPx), and MP1 has
// LVGL zoom them when it draws them. On a screen where modules are drawn much bigger than that
// (MP2), that's blurry, and LVGL's zoom leaves the object the size of the un-zoomed image,
// so things laid out from the object's size (slider handles, map rings) are off.
//
// So on those platforms, an lv_img is given a source like
//     A:ram:/4ms/comp/knob_x.svg@540
// which is the image as it is in a module drawn 540px high, already at the right size
// (make_src() makes these). An LVGL image decoder (registered here) provides the pixels,
// by rasterizing the .svg file with the same path as the component's .png (see svg_file.hh)
// at that size. The SVG's size is as in VCV Rack: 380 SVG pixels are the height of a module.
// The PNG is not used: a component without an SVG is not drawn.
// LVGL decodes an image every time it draws it, so the pixels are kept in a cache.
//
// Only in builds where ThorVG has its SVG loader (lib/thorvg/CMakeLists.txt). ThorVG is built
// without fonts or image loaders, so the SVGs must not rely on <text> or <image>.

#if defined(THORVG_SVG_LOADER_SUPPORT)

#include "thorvg.h"

namespace MetaModule::ScaledImage
{

// Height of a module in SVG pixels (as in VCV Rack)
inline constexpr float SvgModuleHeightPx = 380.f;

namespace Impl
{

struct Raster {
	std::string src;
	std::vector<uint8_t> pixels; // LV_IMG_CF_TRUE_COLOR_ALPHA
	lv_coord_t w = 0;
	lv_coord_t h = 0;
	unsigned users = 0; // open LVGL decoder descriptors using the pixels
};

// Rasters that are not being drawn are dropped, oldest first, when the cache is over this size
inline constexpr size_t MaxCacheBytes = 8 * 1024 * 1024;

struct Cache {
	std::list<Raster> rasters; // most recently used first
	size_t bytes = 0;
};

inline Cache &cache() {
	static Cache c;
	return c;
}

struct ParsedSrc {
	std::string_view path;
	uint32_t module_height = 0;
};

// "A:ram:/dir/knob.svg@540" -> {"A:ram:/dir/knob.svg", 540}
inline ParsedSrc parse(std::string_view src) {
	auto at = src.rfind('@');
	if (at == std::string_view::npos || at + 1 >= src.size())
		return {};

	uint32_t height = 0;
	for (auto c : src.substr(at + 1)) {
		if (c < '0' || c > '9')
			return {};
		height = height * 10 + (c - '0');
	}

	auto path = src.substr(0, at);
	if (height == 0 || !path.ends_with(".svg"))
		return {};

	return {path, height};
}

inline constexpr unsigned PxSize = LV_IMG_PX_SIZE_ALPHA_BYTE;

inline void write_px(uint8_t *px, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	auto color = lv_color_make(r, g, b);
	std::memcpy(px, &color, PxSize - 1);
	px[PxSize - 1] = a;
}

inline bool rasterize_svg(std::string const &path, uint32_t module_height, Raster &raster) {
	auto data = SvgFile::read(path);
	if (data.empty()) {
		pr_warn("Could not read SVG %s\n", path.c_str());
		return false;
	}

	auto picture = SvgFile::parse(data);
	if (!picture) {
		pr_warn("Could not parse SVG %s\n", path.c_str());
		return false;
	}

	float svg_w = 0, svg_h = 0;
	picture->size(&svg_w, &svg_h);
	float scale = (float)module_height / SvgModuleHeightPx;
	uint32_t w = std::max<long>(1, std::lround(svg_w * scale));
	uint32_t h = std::max<long>(1, std::lround(svg_h * scale));
	picture->size(w, h);

	// ThorVG only draws to 32-bit buffers
	std::vector<uint32_t> argb(w * h, 0);

	auto canvas = tvg::SwCanvas::gen();
	// "S": not premultiplied by alpha, like LVGL's images
	bool ok = canvas->target(argb.data(), w, w, h, tvg::ColorSpace::ARGB8888S) == tvg::Result::Success;
	ok = ok && canvas->push(picture) == tvg::Result::Success;
	ok = ok && canvas->draw(false) == tvg::Result::Success;
	ok = ok && canvas->sync() == tvg::Result::Success;
	delete canvas;

	if (!ok) {
		pr_warn("Could not draw SVG %s\n", path.c_str());
		return false;
	}

	raster.w = w;
	raster.h = h;
	raster.pixels.resize(w * h * PxSize);
	for (auto i = 0u; i < w * h; i++) {
		auto px = argb[i];
		write_px(&raster.pixels[i * PxSize], (px >> 16) & 0xFF, (px >> 8) & 0xFF, px & 0xFF, px >> 24);
	}
	return true;
}

inline void trim(Cache &c) {
	for (auto it = c.rasters.end(); c.bytes > MaxCacheBytes && it != c.rasters.begin();) {
		--it;
		// Not the newest one: it's about to be used
		if (it->users == 0 && it != c.rasters.begin()) {
			c.bytes -= it->pixels.size();
			it = c.rasters.erase(it);
		}
	}
}

// Returns the pixels for a source made by make_src(), drawing them if they aren't in the cache
inline Raster *get_raster(std::string_view src) {
	auto parsed = parse(src);
	if (parsed.module_height == 0)
		return nullptr;

	auto &c = cache();

	for (auto it = c.rasters.begin(); it != c.rasters.end(); ++it) {
		if (it->src == src) {
			c.rasters.splice(c.rasters.begin(), c.rasters, it);
			return &c.rasters.front();
		}
	}

	Raster raster;
	raster.src = src;
	if (!rasterize_svg(std::string{parsed.path}, parsed.module_height, raster))
		return nullptr;

	c.bytes += raster.pixels.size();
	c.rasters.push_front(std::move(raster));
	trim(c);
	return &c.rasters.front();
}

inline bool is_file_src(const void *src) {
	return src && lv_img_src_get_type(src) == LV_IMG_SRC_FILE;
}

inline lv_res_t decoder_info(lv_img_decoder_t *, const void *src, lv_img_header_t *header) {
	if (!is_file_src(src))
		return LV_RES_INV;

	auto raster = get_raster(static_cast<const char *>(src));
	if (!raster)
		return LV_RES_INV;

	header->always_zero = 0;
	header->cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
	header->w = raster->w;
	header->h = raster->h;
	return LV_RES_OK;
}

inline lv_res_t decoder_open(lv_img_decoder_t *, lv_img_decoder_dsc_t *dsc) {
	if (!is_file_src(dsc->src))
		return LV_RES_INV;

	auto raster = get_raster(static_cast<const char *>(dsc->src));
	if (!raster)
		return LV_RES_INV;

	raster->users++;
	dsc->img_data = raster->pixels.data();
	dsc->user_data = raster;
	return LV_RES_OK;
}

inline void decoder_close(lv_img_decoder_t *, lv_img_decoder_dsc_t *dsc) {
	auto &c = cache();
	for (auto &raster : c.rasters) {
		if (&raster == dsc->user_data && raster.users > 0)
			raster.users--;
	}
	dsc->user_data = nullptr;
	trim(c);
}

inline void register_decoder() {
	static bool registered = false;
	if (registered)
		return;

	if (auto decoder = lv_img_decoder_create()) {
		lv_img_decoder_set_info_cb(decoder, decoder_info);
		lv_img_decoder_set_open_cb(decoder, decoder_open);
		lv_img_decoder_set_close_cb(decoder, decoder_close);
		registered = true;
	}
}

} // namespace Impl

// Returns the source to give an lv_img, to draw the component image named `image_path` as it is
// in a module drawn `module_height` pixels high
inline std::string make_src(std::string_view image_path, uint32_t module_height) {
	Impl::register_decoder();

	return SvgFile::path_for(image_path) + "@" + std::to_string(module_height);
}

// Returns the module height that a source was made for, or 0 if it's not from make_src()
inline uint32_t module_height_of(std::string_view src) {
	return Impl::parse(src).module_height;
}

// Forgets everything that was read from files (to be called when the files could have changed)
inline void clear_cache() {
	SvgFile::forget_sizes();

	auto &c = Impl::cache();
	for (auto it = c.rasters.begin(); it != c.rasters.end();) {
		if (it->users == 0) {
			c.bytes -= it->pixels.size();
			it = c.rasters.erase(it);
		} else
			++it;
	}
}

} // namespace MetaModule::ScaledImage

#endif
