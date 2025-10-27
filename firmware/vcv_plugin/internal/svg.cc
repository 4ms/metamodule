#include "gui/images/paths.hh"
#include "lvgl.h"
#include <math.hpp>

rack::math::Vec get_svg_size(std::string const &svg_filename) {

	auto path = LV_FS_FATFS_LETTER + std::string(":2:/") + svg_filename;

	struct ImageSize {
		uint32_t w;
		uint32_t h;
	};
	auto get_image_size = [](std::string_view img_path) -> std::optional<ImageSize> {
		lv_img_header_t img_header;
		if (lv_img_decoder_get_info(img_path.data(), &img_header) == LV_RES_OK)
			return ImageSize{img_header.w, img_header.h};
		else
			return std::nullopt;
	};

	if (auto sz = get_image_size(path); sz) {
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
