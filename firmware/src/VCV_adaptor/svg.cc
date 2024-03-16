#include "VCV_adaptor/math.hpp"
#include "gui/elements/draw_img.hh"
#include "gui/images/paths.hh"

rack::math::Vec get_svg_size(std::string const &svg_filename) {
	auto path = LV_FS_FATFS_LETTER + std::string(":2:/") + svg_filename;
	if (auto sz = MetaModule::ElementDrawer::get_image_size(path); sz) {
		pr_dbg("svg is %d %d px\n", sz->w, sz->h);
		return {sz->w / 47.44f * 25.4f, sz->h / 47.44f * 25.4f};
	} else {
		pr_err("can't get svg size\n");
		return {};
	}
}
