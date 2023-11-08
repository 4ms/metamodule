#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"

struct CKSSRot;
struct HCVThemedRogan;

namespace MetaModule
{

template<>
inline Element make_element<::CKSSRot>(BaseElement b) {
	return MetaModule::SlideSwitch{{b}, 2, "CKSS_rot_bg.png", "CKSS_rot_fg.png"};
}

template<>
inline Element make_element<HCVThemedRogan>(BaseElement b) {
	return MetaModule::Knob{{b}, "Rogan1PRed.png"};
}

} // namespace MetaModule
