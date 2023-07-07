#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct OctaveInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Octave"};
    static constexpr std::string_view description{"Octave Shifter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Octave-artwork.svg"};

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.53), "Octave", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.22), "Filter", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(214.97), "CV", ""},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(264.07), "Input", ""},
		AnalogJackOutput4ms{to_mm<72>(28.63), to_mm<72>(312.29), "Out", ""},
		LatchingButtonMonoLight{to_mm<72>(28.65), to_mm<72>(166.04), "Sub", ""},
}};

    enum class Elem {
        OctaveKnob,
        FilterKnob,
        CvIn,
        InputIn,
        Out,
        SubButton,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobOctave = 0,
        KnobFilter = 1,
        NumKnobs,
    };
    
    enum {
        SwitchSub = 0,
        NumSwitches,
    };
    
    enum {
        InputCv = 0,
        InputInput = 1,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
