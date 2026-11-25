#pragma once
#include "console/pr_dbg.hh"
#include "gui/elements/module_art.hh"
#include "lvgl.h"
#include <cmath>
#include <cstring>
#include <list>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

// Component images (knobs, jacks, sliders, switches...) drawn at the size they appear on screen.
//
// The component PNGs are made for a module drawn 240px high (ModuleArtHeightPx), and MP1 has
// LVGL zoom them when it draws them. On a screen where modules are drawn much bigger than that
// (MP2), that's blurry, and LVGL's zoom leaves the object the size of the un-zoomed image,
// so things laid out from the object's size (slider handles, map rings) are off.
//
// So on those platforms, an lv_img is given a source like
//     A:ram:/4ms/comp/knob_x.svg@540
// which is the image as it is in a module drawn 540px high, already at the right size
// (make_src() makes these). An LVGL image decoder (registered here) provides the pixels:
//   - from an .svg file with the same path as the component's .png, if there is one, rasterized
//     at that size. Its size is as in VCV Rack: 380 SVG pixels are the height of a module.
//     (tools/make_svg_assets.py prepares the SVGs for built-in modules)
//   - otherwise from the .png, resized.
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
	std::unordered_map<std::string, bool> has_svg;
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
	if (height == 0 || !(path.ends_with(".svg") || path.ends_with(".png")))
		return {};

	return {path, height};
}

inline bool file_exists(std::string const &path) {
	lv_fs_file_t file;
	if (lv_fs_open(&file, path.c_str(), LV_FS_MODE_RD) != LV_FS_RES_OK)
		return false;
	lv_fs_close(&file);
	return true;
}

inline std::vector<char> read_file(std::string const &path) {
	std::vector<char> data;

	lv_fs_file_t file;
	if (lv_fs_open(&file, path.c_str(), LV_FS_MODE_RD) != LV_FS_RES_OK)
		return data;

	uint32_t size = 0;
	lv_fs_seek(&file, 0, LV_FS_SEEK_END);
	lv_fs_tell(&file, &size);
	lv_fs_seek(&file, 0, LV_FS_SEEK_SET);

	data.resize(size);
	uint32_t bytes_read = 0;
	auto res = lv_fs_read(&file, data.data(), size, &bytes_read);
	lv_fs_close(&file);

	if (res != LV_FS_RES_OK || bytes_read != size)
		data.clear();

	return data;
}

inline constexpr unsigned PxSize = LV_IMG_PX_SIZE_ALPHA_BYTE;

inline void write_px(uint8_t *px, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	auto color = lv_color_make(r, g, b);
	std::memcpy(px, &color, PxSize - 1);
	px[PxSize - 1] = a;
}

struct Rgba {
	float r, g, b, a;
};

// Color is returned multiplied by alpha
inline Rgba read_px_premultiplied(const uint8_t *px) {
	lv_color_t color{};
	std::memcpy(&color, px, PxSize - 1);
	lv_color32_t c32;
	c32.full = lv_color_to32(color);
	float a = px[PxSize - 1];
	return {c32.ch.red * a, c32.ch.green * a, c32.ch.blue * a, a};
}

inline bool rasterize_svg(std::string const &path, uint32_t module_height, Raster &raster) {
	auto data = read_file(path);
	if (data.empty())
		return false;

	auto picture = tvg::Picture::gen();
	if (picture->load(data.data(), data.size(), "svg", nullptr, true) != tvg::Result::Success) {
		// Free a picture that was not given to a canvas
		picture->ref();
		picture->unref();
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

inline bool resize_png(std::string const &path, uint32_t module_height, Raster &raster) {
	lv_img_decoder_dsc_t png;
	if (lv_img_decoder_open(&png, path.c_str(), lv_color_black(), 0) != LV_RES_OK)
		return false;

	bool ok = false;

	// LVGL's PNG decoder decodes the whole image to this format
	if (png.img_data && png.header.cf == LV_IMG_CF_TRUE_COLOR_ALPHA && png.header.w > 0 && png.header.h > 0) {
		int32_t src_w = png.header.w;
		int32_t src_h = png.header.h;
		float scale = (float)module_height / (float)ModuleArtHeightPx;
		int32_t w = std::max<long>(1, std::lround(src_w * scale));
		int32_t h = std::max<long>(1, std::lround(src_h * scale));

		raster.w = w;
		raster.h = h;
		raster.pixels.resize(w * h * PxSize);

		// Bilinear, on colors multiplied by alpha so transparent pixels don't bleed into the edges
		for (int32_t y = 0; y < h; y++) {
			float fy = std::clamp((y + 0.5f) * src_h / h - 0.5f, 0.f, src_h - 1.f);
			int32_t y0 = fy;
			int32_t y1 = std::min(y0 + 1, src_h - 1);
			float wy = fy - y0;

			for (int32_t x = 0; x < w; x++) {
				float fx = std::clamp((x + 0.5f) * src_w / w - 0.5f, 0.f, src_w - 1.f);
				int32_t x0 = fx;
				int32_t x1 = std::min(x0 + 1, src_w - 1);
				float wx = fx - x0;

				auto p00 = read_px_premultiplied(&png.img_data[(y0 * src_w + x0) * PxSize]);
				auto p01 = read_px_premultiplied(&png.img_data[(y0 * src_w + x1) * PxSize]);
				auto p10 = read_px_premultiplied(&png.img_data[(y1 * src_w + x0) * PxSize]);
				auto p11 = read_px_premultiplied(&png.img_data[(y1 * src_w + x1) * PxSize]);

				auto mix = [=](float v00, float v01, float v10, float v11) {
					return (v00 * (1 - wx) + v01 * wx) * (1 - wy) + (v10 * (1 - wx) + v11 * wx) * wy;
				};
				float a = mix(p00.a, p01.a, p10.a, p11.a);
				float r = mix(p00.r, p01.r, p10.r, p11.r);
				float g = mix(p00.g, p01.g, p10.g, p11.g);
				float b = mix(p00.b, p01.b, p10.b, p11.b);

				auto out = &raster.pixels[(y * w + x) * PxSize];
				if (a < 0.5f)
					write_px(out, 0, 0, 0, 0);
				else
					write_px(out, std::lround(r / a), std::lround(g / a), std::lround(b / a), std::lround(a));
			}
		}
		ok = true;
	}

	lv_img_decoder_close(&png);
	return ok;
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
	std::string path{parsed.path};

	bool ok = false;
	if (path.ends_with(".svg")) {
		ok = rasterize_svg(path, parsed.module_height, raster);
		// If the SVG can't be drawn, there's a PNG with the same name
		if (!ok)
			path.replace(path.size() - 4, 4, ".png");
	}
	ok = ok || resize_png(path, parsed.module_height, raster);
	if (!ok)
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

// Returns the source to give an lv_img, to draw the component image at `png_path` as it is
// in a module drawn `module_height` pixels high
inline std::string make_src(std::string_view png_path, uint32_t module_height) {
	Impl::register_decoder();

	std::string path{png_path};

	if (auto dot = path.rfind('.'); dot != std::string::npos) {
		auto svg_path = path.substr(0, dot) + ".svg";
		auto &has_svg = Impl::cache().has_svg;
		auto found = has_svg.find(svg_path);
		if (found == has_svg.end())
			found = has_svg.emplace(svg_path, Impl::file_exists(svg_path)).first;
		if (found->second)
			path = svg_path;
	}

	return path + "@" + std::to_string(module_height);
}

// Returns the module height that a source was made for, or 0 if it's not from make_src()
inline uint32_t module_height_of(std::string_view src) {
	return Impl::parse(src).module_height;
}

// Forgets everything that was read from files (to be called when the files could have changed)
inline void clear_cache() {
	auto &c = Impl::cache();
	c.has_svg.clear();
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
