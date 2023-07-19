#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"

#include "4ms_images.hh"
#include "Rack_images.hh"
#include "audible_images.hh"
#include "befaco_images.hh"
#include "pr_dbg.hh"

namespace MetaModule::ElementImageImpl
{

inline const lv_img_dsc_t *get_img(const BaseElement &element) {
	// if (element.short_name.data() && element.short_name.size() > 0 && element.short_name.size() < 32)
	// 	pr_dbg("Element image not found: %.32s\n", element.short_name.data());
	// else
	pr_dbg("Element image not found (invalid name)\n");
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
		return ElementImageImpl::get_img(element);
	}
};

} // namespace MetaModule
