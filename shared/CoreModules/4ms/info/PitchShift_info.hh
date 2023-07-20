#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct PitchShiftInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"PitchShift"};
    static constexpr std::string_view description{"Pitch Shifter"};
    static constexpr uint32_t width_hp = 7;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/PitchShift-artwork.svg"};

    static constexpr std::array<Element, 9> Elements{{
		Davies1900hBlackKnob{to_mm<72>(50.53), to_mm<72>(46.91), "Coarse", "", 0, 0, 1, 0.25f},
		Knob9mm{to_mm<72>(50.52), to_mm<72>(94.87), "Fine", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(50.52), to_mm<72>(139.62), "Window", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(50.52), to_mm<72>(184.38), "Mix", "", 0, 0, 1, 0.875f},
		AnalogJackInput4ms{to_mm<72>(30.92), to_mm<72>(232.48), "Input", ""},
		AnalogJackInput4ms{to_mm<72>(69.92), to_mm<72>(232.48), "Pitch CV", ""},
		AnalogJackInput4ms{to_mm<72>(30.92), to_mm<72>(281.58), "Window CV", ""},
		AnalogJackInput4ms{to_mm<72>(69.92), to_mm<72>(281.58), "Mix CV", ""},
		AnalogJackOutput4ms{to_mm<72>(69.92), to_mm<72>(326.11), "Out", ""},
}};

    enum class Elem {
        CoarseKnob,
        FineKnob,
        WindowKnob,
        MixKnob,
        InputIn,
        PitchCvIn,
        WindowCvIn,
        MixCvIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobCoarse = 0,
        KnobFine = 1,
        KnobWindow = 2,
        KnobMix = 3,
        NumKnobs,
    };
    
    
    enum {
        InputInput = 0,
        InputPitch_Cv = 1,
        InputWindow_Cv = 2,
        InputMix_Cv = 3,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
