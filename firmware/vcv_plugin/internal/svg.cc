#include "gui/elements/draw_img.hh"
#include "gui/elements/svg_file.hh"
#include "gui/images/paths.hh"
#include <math.hpp>

#if defined(THORVG_SVG_LOADER_SUPPORT)

// The images are named as PNG files, and drawn from the SVG file with the same path
rack::math::Vec get_svg_size(std::string const &image_filename) {

	auto path = LV_FS_FATFS_LETTER + std::string(":2:/") + MetaModule::SvgFile::path_for(image_filename);

	if (auto sz = MetaModule::SvgFile::size_of(path)) {
		// A faceplate is as high as a module, whatever size its SVG file says it is: it's drawn
		// scaled to the height of the module (see svg_faceplate.hh)
		constexpr float ModuleHeight = MetaModule::ScaledImage::SvgModuleHeightPx;
		if (sz->h > ModuleHeight * 0.9f)
			return {sz->w * ModuleHeight / sz->h, ModuleHeight};

		return {sz->w, sz->h};
	}

	// Note, missing SVG is not an error
	return {};
}

#else

rack::math::Vec get_svg_size(std::string const &svg_filename) {

	auto path = LV_FS_FATFS_LETTER + std::string(":2:/") + svg_filename;

	if (auto sz = MetaModule::ElementDrawer::get_image_size(path); sz) {
		// pr_dbg("%s is %f x %f\n",
		// 	   svg_filename.c_str(),
		// 	   MetaModule::PNGpx_to_SVGpx(sz->w),
		// 	   MetaModule::PNGpx_to_SVGpx(sz->h));
		return {MetaModule::PNGpx_to_SVGpx(sz->w), MetaModule::PNGpx_to_SVGpx(sz->h)};
	} else {
		// Note, missing SVG is not an error:
		// pr_trace("%s: can't get svg size\n", svg_filename.c_str());
		return {};
	}
}

#endif
