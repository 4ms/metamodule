#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/componentlibrary.hpp"
#include "VCV_adaptor/widget_convert/base.hh"

struct CKSSRot;
struct HCVThemedRogan;

template<typename BASE>
struct MuteLight;

namespace MetaModule
{

template<>
inline Element make_element<::CKSSRot>(BaseElement b) {
	return MetaModule::SlideSwitch{{b, "CKSS_rot_bg.png"}, 2, "CKSS_rot_fg.png"};
}

template<>
inline Element make_element<HCVThemedRogan>(BaseElement b) {
	return MetaModule::Knob{b, "Rogan1PRed.png"};
}

template<>
inline Element make_element<MuteLight<rack::componentlibrary::RedLight>>(BaseElement b) {
	return MetaModule::MonoLight{{b, "MuteLight.png"}, Colors565::Red};
}

template<>
inline Element make_element<MuteLight<rack::componentlibrary::BlueLight>>(BaseElement b) {
	return MetaModule::MonoLight{{b, "MuteLight.png"}, Colors565::Cyan};
}

} // namespace MetaModule
