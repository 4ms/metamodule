#pragma once
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cmath>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

// Module faceplates drawn from SVG files.
//
// The faceplate PNGs are made for a module drawn 240px high (ModuleArtHeightPx). On a screen
// where modules are drawn much larger than that (MP2), scaling the PNG up is blurry, so if
// there is an .svg file with the same path as the faceplate's .png, it's rasterized at the
// size the module is drawn at instead.
//
// Only in builds where ThorVG has its SVG loader (lib/thorvg/CMakeLists.txt). ThorVG is built
// without fonts or image loaders, so the SVGs must not rely on <text> or <image>
// (tools/make_svg_faceplates.py prepares them).

#if defined(THORVG_SVG_LOADER_SUPPORT)

#include "thorvg.h"

namespace MetaModule::SvgFaceplate
{

namespace Impl
{

// The file is read when the faceplate is measured, and used again right after to draw it
struct FileCache {
	std::string path;
	std::vector<char> data;
};

inline FileCache &cache() {
	static FileCache file_cache;
	return file_cache;
}

inline bool read_file(std::string const &path) {
	auto &c = cache();
	if (c.path == path && !c.data.empty())
		return true;

	c.path.clear();
	c.data.clear();

	lv_fs_file_t file;
	if (lv_fs_open(&file, path.c_str(), LV_FS_MODE_RD) != LV_FS_RES_OK)
		return false;

	uint32_t size = 0;
	lv_fs_seek(&file, 0, LV_FS_SEEK_END);
	lv_fs_tell(&file, &size);
	lv_fs_seek(&file, 0, LV_FS_SEEK_SET);

	c.data.resize(size);
	uint32_t bytes_read = 0;
	auto res = lv_fs_read(&file, c.data.data(), size, &bytes_read);
	lv_fs_close(&file);

	if (res != LV_FS_RES_OK || bytes_read != size || size == 0) {
		c.data.clear();
		return false;
	}

	c.path = path;
	return true;
}

// Frees a picture that was not given to a canvas
inline void release(tvg::Picture *picture) {
	picture->ref();
	picture->unref();
}

inline tvg::Picture *load_picture(std::string const &path) {
	if (!read_file(path))
		return nullptr;

	auto &data = cache().data;
	auto picture = tvg::Picture::gen();
	if (picture->load(data.data(), data.size(), "svg", nullptr, true) != tvg::Result::Success) {
		release(picture);
		pr_warn("Could not parse SVG %s\n", path.c_str());
		return nullptr;
	}
	return picture;
}

} // namespace Impl

// Returns the path of the SVG to use in place of the PNG faceplate at png_path, if there is one
inline std::optional<std::string> find(std::string_view png_path) {
	auto dot = png_path.rfind('.');
	if (dot == std::string_view::npos)
		return {};

	auto svg_path = std::string{png_path.substr(0, dot)} + ".svg";
	if (Impl::read_file(svg_path))
		return svg_path;

	return {};
}

inline bool is_svg(std::string_view path) {
	return path.ends_with(".svg");
}

// Returns the width in pixels of the faceplate when drawn at the given height (0 on failure)
inline lv_coord_t width_at_height(std::string const &svg_path, uint32_t height) {
	auto picture = Impl::load_picture(svg_path);
	if (!picture)
		return 0;

	float w = 0, h = 0;
	picture->size(&w, &h);
	Impl::release(picture);

	if (w <= 0 || h <= 0)
		return 0;

	return std::lround(w * (float)height / h);
}

// Draws the faceplate to fill a width x height buffer of LVGL pixels
inline bool draw(std::string const &svg_path, std::span<lv_color_t> pixels, uint32_t width, uint32_t height) {
	if (width == 0 || height == 0 || pixels.size() < width * height)
		return false;

	auto picture = Impl::load_picture(svg_path);

	// Done with the file, whether it could be parsed or not
	Impl::cache() = {};

	if (!picture)
		return false;

	picture->size(width, height);

	// ThorVG only draws to 32-bit buffers
	std::vector<uint32_t> argb(width * height, 0xFF000000);

	auto canvas = tvg::SwCanvas::gen();
	bool ok = canvas->target(argb.data(), width, width, height, tvg::ColorSpace::ARGB8888) == tvg::Result::Success;
	ok = ok && canvas->push(picture) == tvg::Result::Success;
	ok = ok && canvas->draw(false) == tvg::Result::Success;
	ok = ok && canvas->sync() == tvg::Result::Success;
	delete canvas;

	if (!ok) {
		pr_warn("Could not draw SVG %s\n", svg_path.c_str());
		return false;
	}

	for (auto i = 0u; i < width * height; i++) {
		auto px = argb[i];
		pixels[i] = lv_color_make((px >> 16) & 0xFF, (px >> 8) & 0xFF, px & 0xFF);
	}

	return true;
}

} // namespace MetaModule::SvgFaceplate

#endif
