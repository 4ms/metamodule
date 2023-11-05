#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"

struct CKSSRot;
struct HCVThemedRogan;

struct lv_img_dsc_t;
extern lv_img_dsc_t *CKSS_rot_fg;
extern lv_img_dsc_t *CKSS_rot_bg;

namespace MetaModule
{

template<>
inline Element make_element<::CKSSRot>(BaseElement &&b) {
	return MetaModule::SlideSwitchNPos{{b}, 2, (void *)&::CKSS_rot_bg, (void *)&::CKSS_rot_fg};
}

template<>
inline Element make_element<HCVThemedRogan>(BaseElement &&b) {
	return MetaModule::Rogan1PRed{b};
}

} // namespace MetaModule
