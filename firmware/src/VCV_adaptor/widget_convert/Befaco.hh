#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"

// Forward declare widgets from Befaco/src/plugin.hpp
struct Knurlie;

struct BefacoTinyKnobWhite;
struct BefacoTinyKnobRed;
struct BefacoTinyKnobDarkGrey;
struct BefacoTinyKnobLightGrey;
struct BefacoTinyKnobBlack;
struct Davies1900hLargeGreyKnob;
struct Davies1900hLargeLightGreyKnob;
struct Davies1900hLightGreyKnob;
struct Davies1900hDarkGreyKnob;
struct Crossfader;
struct BefacoSlidePotSmall;

struct BananutRed;
struct BananutBlack;

struct CKSSNarrow;
struct CKSSHoriz2;
struct CKSSVert7;
struct CKSSHoriz4;
struct CKSSNarrow3;

// From StereoStrip.cpp:
struct ThreeStateBefacoSwitchMomentary;

// Only used in Muxslicer:
// struct BefacoSwitchHorizontal;

// Conversions from Befaco widgets to MetaModule Elements:

namespace MetaModule
{

template<>
inline Element make_element<::CKSSVert7>(BaseElement b) {
	return SlideSwitch{{b}, 7, "SwitchTallVert.png", "SwitchTallVertHandle.png"};
}

template<>
inline Element make_element<::CKSSHoriz4>(BaseElement b) {
	return SlideSwitch{{b}, 4, "SwitchWideHoriz_bg.png", "SwitchWideHoriz_fg.png"};
}

template<>
inline Element make_element<::CKSSHoriz2>(BaseElement b) {
	return SlideSwitch{{b}, 2, "SwitchNarrowHoriz_bg.png"};
}

template<>
inline Element make_element<::CKSSNarrow>(BaseElement b) {
	return SlideSwitch{{b}, 2, "SwitchNarrow.png"};
}

template<>
inline Element make_element<::CKSSNarrow3>(BaseElement b) {
	return SlideSwitch{{b}, 3, "SwitchNarrow.png"};
}

template<>
inline Element make_element<::ThreeStateBefacoSwitchMomentary>(BaseElement b) {
	return FlipSwitch{
		{b}, 3, {"BefacoSwitch_0.png", "BefacoSwitch_1.png", "BefacoSwitch_2.png"}, {"Off(m)", "On", "Off"}};
};

template<>
inline Element make_element<::Knurlie>(BaseElement b) {
	return NullElement{b};
};

template<>
inline Element make_element<::BefacoTinyKnobWhite>(BaseElement b) {
	return Knob{{b}, "BefacoTinyKnobWhite.png"};
};

template<>
inline Element make_element<::BefacoTinyKnobRed>(BaseElement b) {
	return Knob{{b}, "BefacoTinyKnobRed.png"};
};

template<>
inline Element make_element<::BefacoTinyKnobDarkGrey>(BaseElement b) {
	return Knob{{b}, "BefacoTinyKnobDarkGrey.png"};
};

template<>
inline Element make_element<::BefacoTinyKnobLightGrey>(BaseElement b) {
	return Knob{{b}, "BefacoTinyKnobLightGrey.png"};
};

template<>
inline Element make_element<::BefacoTinyKnobBlack>(BaseElement b) {
	return Knob{{b}, "BefacoTinyKnobBlack.png"};
};

template<>
inline Element make_element<::Davies1900hLargeGreyKnob>(BaseElement b) {
	return Knob{{b}, "Davies1900hLargeGrey.png"};
};

template<>
inline Element make_element<::Davies1900hLightGreyKnob>(BaseElement b) {
	return Knob{{b}, "Davies1900hLightGrey.png"};
};

template<>
inline Element make_element<::Davies1900hLargeLightGreyKnob>(BaseElement b) {
	return Knob{{b}, "Davies1900hLargeLightGrey.png"};
};

template<>
inline Element make_element<::Davies1900hDarkGreyKnob>(BaseElement b) {
	return Knob{{b}, "Davies1900hDarkGrey.png"};
};

template<>
inline Element make_element<::Crossfader>(BaseElement b) {
	return Slider{{b}, "Crossfader.png", "CrossfaderHandle.png"};
};

template<>
inline Element make_element<::BefacoSlidePotSmall>(BaseElement b) {
	return Slider{{b}, "BefacoSlidePotSmall.png", "BefacoSlidePotHandleSmall.png"};
};

template<>
inline Element make_element_output<::BananutRed>(BaseElement b) {
	return JackOutput{{{b}, "BananutRed.png"}};
};

template<>
inline Element make_element_input<::BananutBlack>(BaseElement b) {
	return JackInput{{{b}, "BananutBlack.png"}};
};

} // namespace MetaModule
