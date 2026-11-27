#pragma once
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cmath>
#include <span>
#include <string>
#include <string_view>
#include <vector>

// Module faceplates drawn from SVG files.
//
// The faceplate PNGs are made for a module drawn 240px high (ModuleArtHeightPx). On a screen
// where modules are drawn much larger than that (MP2), scaling the PNG up is blurry, so the
// .svg file with the same path as the faceplate's .png (see svg_file.hh) is rasterized at the
// size the module is drawn at instead. The PNG is not used: a module without an SVG faceplate
// is not drawn.
//
// Only in builds where ThorVG has its SVG loader (lib/thorvg/CMakeLists.txt). ThorVG is built
// without fonts or image loaders, so the SVGs must not rely on <text> or <image>.

#if defined(THORVG_SVG_LOADER_SUPPORT)

#include "gui/elements/svg_file.hh"
#include "thorvg.h"

namespace MetaModule::SvgFaceplate
{

// Returns the width in pixels of the faceplate when drawn at the given height (0 on failure)
inline lv_coord_t width_at_height(std::string const &svg_path, uint32_t height) {
	auto size = SvgFile::size_of(svg_path);
	if (!size)
		return 0;

	return std::lround(size->w * (float)height / size->h);
}

// Draws the faceplate to fill a width x height buffer of LVGL pixels
inline bool draw(std::string const &svg_path, std::span<lv_color_t> pixels, uint32_t width, uint32_t height) {
	if (width == 0 || height == 0 || pixels.size() < width * height)
		return false;

	auto data = SvgFile::read(svg_path);
	auto picture = data.empty() ? nullptr : SvgFile::parse(data);
	if (!picture) {
		pr_warn("Could not read SVG %s\n", svg_path.c_str());
		return false;
	}

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
