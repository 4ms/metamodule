#pragma once
#include <string>
#include <string_view>

// Module artwork (faceplates and component images) in SVG files.
//
// Artwork is named by its .png file everywhere: in the modules' info, by plugins, and by the
// Rack adaptor (which turns the .svg names that Rack code uses into .png names).
// MP1 draws those PNG files.
// MP2 draws the .svg file with the same path instead, and never reads the PNG:
// see svg_faceplate.hh (faceplates) and scaled_image.hh (component images).

namespace MetaModule::SvgFile
{

// Returns the path of the SVG file for the artwork named image_path
inline std::string path_for(std::string_view image_path) {
	auto dot = image_path.rfind('.');
	auto slash = image_path.rfind('/');
	if (dot != std::string_view::npos && (slash == std::string_view::npos || dot > slash))
		image_path = image_path.substr(0, dot);

	return std::string{image_path} + ".svg";
}

} // namespace MetaModule::SvgFile

// SVG files are read with ThorVG, in builds where it has its SVG loader
// (lib/thorvg/CMakeLists.txt). It must be running: tvg::Initializer::init()
#if defined(THORVG_SVG_LOADER_SUPPORT)

#include "lvgl.h"
#include "thorvg.h"
#include <optional>
#include <span>
#include <unordered_map>
#include <vector>

namespace MetaModule::SvgFile
{

// Returns the contents of a file (empty if it can't be read)
inline std::vector<char> read(std::string const &path) {
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

// Frees a picture that was not given to a canvas
inline void release(tvg::Picture *picture) {
	picture->ref();
	picture->unref();
}

// Returns the SVG as a ThorVG picture, or nullptr if it can't be parsed.
// The picture is to be given to a canvas, or to release()
inline tvg::Picture *parse(std::span<const char> svg) {
	auto picture = tvg::Picture::gen();
	if (picture->load(svg.data(), svg.size(), "svg", nullptr, true) != tvg::Result::Success) {
		release(picture);
		return nullptr;
	}
	return picture;
}

struct Size {
	float w = 0;
	float h = 0;
};

namespace Impl
{

inline std::unordered_map<std::string, Size> &sizes() {
	static std::unordered_map<std::string, Size> sizes_of_files;
	return sizes_of_files;
}

} // namespace Impl

// Returns the size of an SVG file in SVG pixels, or nothing if there is no such file or it's
// not an SVG.
// This is the size ThorVG gives it, which the size it's drawn at comes from: see
// scaled_image.hh. (Sizes are best given in pixels: ThorVG has 96 pixels to the inch for those
// in mm, in, pt..., where VCV Rack has 75.)
// ThorVG parses the whole file to tell its size, so the sizes are kept: see forget_sizes()
inline std::optional<Size> size_of(std::string const &path) {
	auto &sizes = Impl::sizes();
	if (auto found = sizes.find(path); found != sizes.end())
		return found->second;

	auto data = read(path);
	if (data.empty())
		return {};

	auto picture = parse(data);
	if (!picture)
		return {};

	Size size;
	picture->size(&size.w, &size.h);
	release(picture);

	if (size.w <= 0 || size.h <= 0)
		return {};

	sizes[path] = size;
	return size;
}

// To be called when the files could have changed
inline void forget_sizes() {
	Impl::sizes().clear();
}

} // namespace MetaModule::SvgFile

#endif
