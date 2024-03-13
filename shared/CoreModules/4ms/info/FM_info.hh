#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct FMInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"FM"};
    static constexpr std::string_view description{"FM Oscillator"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/FM_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/FM.png"};

    using enum Coords;

    static constexpr std::array<Element, 14> Elements{{
		Knob9mm{{to_mm<72>(31.96), to_mm<72>(40.33), Center, "Pitch", ""}},
		Knob9mm{{to_mm<72>(83.49), to_mm<72>(40.33), Center, "Mix", ""}},
		Knob9mm{{to_mm<72>(31.96), to_mm<72>(83.47), Center, "Index", ""}},
		Knob9mm{{to_mm<72>(83.49), to_mm<72>(83.47), Center, "Index CV", ""}},
		Knob9mm{{to_mm<72>(31.96), to_mm<72>(126.62), Center, "Ratio C", ""}},
		Knob9mm{{to_mm<72>(83.49), to_mm<72>(126.62), Center, "Ratio F", ""}},
		Knob9mm{{to_mm<72>(31.96), to_mm<72>(169.76), Center, "Shape", ""}},
		Knob9mm{{to_mm<72>(83.49), to_mm<72>(169.76), Center, "Shape CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(31.96), to_mm<72>(214.56), Center, "V/Oct P", ""}},
		AnalogJackInput4ms{{to_mm<72>(83.49), to_mm<72>(214.56), Center, "V/Oct S", ""}},
		AnalogJackInput4ms{{to_mm<72>(31.96), to_mm<72>(263.28), Center, "Mix CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(83.49), to_mm<72>(263.28), Center, "Index CV In", ""}},
		AnalogJackInput4ms{{to_mm<72>(31.96), to_mm<72>(312.0), Center, "Shape CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(83.49), to_mm<72>(312.0), Center, "Out", ""}},
}};

    enum class Elem {
        PitchKnob,
        MixKnob,
        IndexKnob,
        IndexCvKnob,
        RatioCKnob,
        RatioFKnob,
        ShapeKnob,
        ShapeCvKnob,
        V_OctPIn,
        V_OctSIn,
        MixCvIn,
        IndexCvIn,
        ShapeCvIn,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobPitch = 0,
        KnobMix = 1,
        KnobIndex = 2,
        KnobIndex_Cv = 3,
        KnobRatio_C = 4,
        KnobRatio_F = 5,
        KnobShape = 6,
        KnobShape_Cv = 7,
        NumKnobs,
    };
    
    
    enum {
        InputV_Oct_P = 0,
        InputV_Oct_S = 1,
        InputMix_Cv = 2,
        InputIndex_Cv_In = 3,
        InputShape_Cv = 4,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
