#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"
#include "pr_dbg.hh"

#include "4ms/images.hh"
#include "AudibleInstruments/images.hh"
#include "Befaco/images.hh"
#include "Rack/images.hh"

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

namespace ElementImage
{

template<typename T>
const lv_img_dsc_t *get_img(T element) {
	return ElementImageImpl::get_img(element);
}
}; // namespace ElementImage

} // namespace MetaModule
