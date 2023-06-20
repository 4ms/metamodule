#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pr_dbg.hh"

#include "4ms_images.hh"
#include "audible_images.hh"
#include "befaco_images.hh"

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const BaseElement &element, uint32_t scale_px) {
	pr_dbg("Element image not found\n");
	return nullptr;
}

} // namespace MetaModule::ElementImageImpl

namespace MetaModule
{

struct ElementImage {
	uint32_t scale_px;

	ElementImage(uint32_t module_height)
		: scale_px{module_height} {
	}

	template<typename T>
	const lv_img_dsc_t *get_img(T element) {
		return ElementImageImpl::get_img(element, scale_px);
	}
};

} // namespace MetaModule
