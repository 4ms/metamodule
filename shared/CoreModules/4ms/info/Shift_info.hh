#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ShiftInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Shift"};
    static constexpr std::string_view description{"Frequency Shifter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Shift-artwork.svg"};

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.53), "Coarse", "", 0, 0, 1, 0.25f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.22), "Fine", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(142.91), "Mix", "", 0, 0, 1, 0.875f},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(214.97), "Coarse CV", ""},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(264.07), "Input", ""},
		AnalogJackOutput4ms{to_mm<72>(28.63), to_mm<72>(312.29), "Out", ""},
}};

    enum class Elem {
        CoarseKnob,
        FineKnob,
        MixKnob,
        CoarseCvIn,
        InputIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobCoarse = 0,
        KnobFine = 1,
        KnobMix = 2,
        NumKnobs,
    };
    
    
    enum {
        InputCoarse_Cv = 0,
        InputInput = 1,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
