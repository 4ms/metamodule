#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"
#include "VCV_adaptor/widgets.hh"

namespace MetaModule
{

template<>
inline Element make_element<rack::componentlibrary::BefacoBigKnob>(BaseElement &&b) {
	return BefacoBigKnob{b};
};

template<>
inline Element make_element<rack::componentlibrary::BefacoTinyKnob>(BaseElement &&b) {
	return BefacoTinyKnobBlack{b};
};

template<>
inline Element make_element<rack::componentlibrary::BefacoSlidePot>(BaseElement &&b) {
	return BefacoSlidePot{b};
};

template<>
inline Element make_element<rack::componentlibrary::BefacoSwitch>(BaseElement &&b) {
	return BefacoSwitch{b};
};

template<>
inline Element make_element<rack::componentlibrary::BefacoPush>(BaseElement &&b) {
	return BefacoPush{b};
};

template<>
inline Element make_element<rack::componentlibrary::CKSS>(BaseElement &&b) {
	return CKSS{b};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hBlackKnob>(BaseElement &&b) {
	return Davies1900hBlackKnob{b};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hWhiteKnob>(BaseElement &&b) {
	return Davies1900hWhiteKnob{b};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hRedKnob>(BaseElement &&b) {
	return Davies1900hRedKnob{b};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hLargeWhiteKnob>(BaseElement &&b) {
	return Davies1900hLargeWhiteKnob{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PSGreen>(BaseElement &&b) {
	return Rogan1PSGreen{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PSRed>(BaseElement &&b) {
	return Rogan1PSRed{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PSWhite>(BaseElement &&b) {
	return Rogan1PSWhite{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2SGray>(BaseElement &&b) {
	return Rogan2SGray{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2PSWhite>(BaseElement &&b) {
	return Rogan2PSWhite{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PRed>(BaseElement &&b) {
	return Rogan1PRed{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan>(BaseElement &&b) {
	return Rogan1PRed{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2PSRed>(BaseElement &&b) {
	return Rogan2PSRed{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2PSGreen>(BaseElement &&b) {
	return Rogan2PSGreen{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan3PSWhite>(BaseElement &&b) {
	return Rogan3PSWhite{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan3PSRed>(BaseElement &&b) {
	return Rogan3PSRed{b};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan3PSGreen>(BaseElement &&b) {
	return Rogan3PSGreen{b};
};

template<>
inline Element make_element<rack::componentlibrary::Trimpot>(BaseElement &&b) {
	return Trimpot{b};
};

template<>
inline Element make_element<rack::componentlibrary::CKD6>(BaseElement &&b) {
	return CKD6{b};
};

template<>
inline Element make_element<rack::componentlibrary::TL1105>(BaseElement &&b) {
	return TL1105{b};
};

template<>
inline Element make_element<rack::componentlibrary::LEDBezel>(BaseElement &&b) {
	return LEDBezel{b};
};

template<>
inline Element
make_element<rack::componentlibrary::VCVLightBezel<rack::componentlibrary::RedGreenBlueLight>>(BaseElement &&b) {
	return VCVLightBezel<RedGreenBlueLight>{b};
};

template<>
inline Element make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::RedLight>>(BaseElement &&b) {
	return SmallLight<RedLight>{b};
};

template<>
inline Element make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::GreenLight>>(BaseElement &&b) {
	return SmallLight<GreenLight>{b};
};

template<>
inline Element
make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::GreenRedLight>>(BaseElement &&b) {
	return SmallLight<GreenRedLight>{b};
};

template<>
inline Element
make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::GreenRedLight>>(BaseElement &&b) {
	return MediumLight<GreenRedLight>{b};
};

template<>
inline Element make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::RedLight>>(BaseElement &&b) {
	return MediumLight<RedLight>{b};
};

template<>
inline Element make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::GreenLight>>(BaseElement &&b) {
	return MediumLight<GreenLight>{b};
};

template<>
inline Element make_element_input<rack::componentlibrary::PJ301MPort>(BaseElement b) {
	return MediumLight<PJ301MPortIn>{b};
};

template<>
inline Element make_element_output<rack::componentlibrary::PJ301MPort>(BaseElement b) {
	return MediumLight<PJ301MPortOut>{b};
};

template<>
inline Element make_element_input<rack::componentlibrary::ThemedPJ301MPort>(BaseElement b) {
	return MediumLight<PJ301MPortIn>{b};
};

template<>
inline Element make_element_output<rack::componentlibrary::ThemedPJ301MPort>(BaseElement b) {
	return MediumLight<PJ301MPortOut>{b};
};

} // namespace MetaModule
