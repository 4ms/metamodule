#pragma once
#include "CoreModules/elements/element_info.hh" //just for mm_to_px
#include "CoreModules/elements/elements.hh"
#include "pages/styles.hh"
#include "pr_dbg.hh"
#include <cmath>

namespace MetaModule::ElementDrawerImpl
{

constexpr std::pair<uint32_t, uint32_t> mm_to_px(uint32_t x_mm, uint32_t y_mm, uint32_t module_height) {
	uint32_t x = std::round(ModuleInfoBase::mm_to_px(x_mm, module_height));
	uint32_t y = std::round(ModuleInfoBase::mm_to_px(y_mm, module_height));
	return {x, y};
}

inline std::pair<uint32_t, uint32_t>
mm_to_center_px(uint32_t x_mm, uint32_t y_mm, const lv_img_dsc_t *img, uint32_t module_height) {
	uint32_t width = img ? img->header.w : 0;
	uint32_t height = img ? img->header.h : 0;
	uint32_t left = std::round(ModuleInfoBase::mm_to_px(x_mm, module_height) - width / 2.f);
	uint32_t top = std::round(ModuleInfoBase::mm_to_px(y_mm, module_height) - height / 2.f);
	return {left, top};
}

constexpr std::pair<uint32_t, uint32_t>
mm_to_center_px(uint32_t x_mm, uint32_t y_mm, uint32_t width, uint32_t height, uint32_t module_height) {
	uint32_t left = std::round(ModuleInfoBase::mm_to_px(x_mm, module_height) - width / 2.f);
	uint32_t top = std::round(ModuleInfoBase::mm_to_px(y_mm, module_height) - height / 2.f);
	return {left, top};
}

} // namespace MetaModule::ElementDrawerImpl
