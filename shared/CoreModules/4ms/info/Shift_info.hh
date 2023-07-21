#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ShiftInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Shift"};
    static constexpr std::string_view description{"Frequency Shifter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Shift_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.53), Center, "Coarse", ""},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.22), Center, "Fine", ""},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(142.91), Center, "Mix", ""},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(214.97), Center, "Coarse CV", ""},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(264.07), Center, "Input", ""},
		AnalogJackOutput4ms{to_mm<72>(28.63), to_mm<72>(312.29), Center, "Out", ""},
}};

    enum class Elem {
        CoarseKnob,
        FineKnob,
        MixKnob,
        CoarseCvIn,
        InputIn,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
