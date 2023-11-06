#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct PitchShiftInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"PitchShift"};
    static constexpr std::string_view description{"Pitch Shifter"};
    static constexpr uint32_t width_hp = 7;
    static constexpr std::string_view svg_filename{"res/modules/PitchShift_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 9> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(50.53), to_mm<72>(46.91), Center, "Coarse", ""}},
		Knob9mm{{to_mm<72>(50.52), to_mm<72>(94.87), Center, "Fine", ""}},
		Knob9mm{{to_mm<72>(50.52), to_mm<72>(139.62), Center, "Window", ""}},
		Knob9mm{{to_mm<72>(50.52), to_mm<72>(184.38), Center, "Mix", ""}},
		AnalogJackInput4ms{{to_mm<72>(30.92), to_mm<72>(232.48), Center, "Input", ""}},
		AnalogJackInput4ms{{to_mm<72>(69.92), to_mm<72>(232.48), Center, "Pitch CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(30.92), to_mm<72>(281.58), Center, "Window CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(69.92), to_mm<72>(281.58), Center, "Mix CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(69.92), to_mm<72>(326.11), Center, "Out", ""}},
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

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
