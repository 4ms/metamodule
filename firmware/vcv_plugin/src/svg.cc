#include "gui/elements/draw_img.hh"
#include "gui/images/paths.hh"
#include <math.hpp>

rack::math::Vec get_svg_size(std::string const &svg_filename) {

	auto path = LV_FS_FATFS_LETTER + std::string(":2:/") + svg_filename;

	if (auto sz = MetaModule::ElementDrawer::get_image_size(path); sz) {
		return {MetaModule::PNGpx_to_SVGpx(sz->w), MetaModule::PNGpx_to_SVGpx(sz->h)};
	} else {
		// pr_err("can't get svg size\n");
		return {};
	}
}
