#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct OctaveInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Octave"};
    static constexpr std::string_view description{"Octave Shifter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Octave_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(46.53), Center, "Octave", ""}},
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(94.22), Center, "Filter", ""}},
		AnalogJackInput4ms{{to_mm<72>(28.63), to_mm<72>(214.97), Center, "CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(28.63), to_mm<72>(264.07), Center, "Input", ""}},
		AnalogJackOutput4ms{{to_mm<72>(28.63), to_mm<72>(312.29), Center, "Out", ""}},
		OrangeButton{{to_mm<72>(28.65), to_mm<72>(166.04), Center, "Sub", ""}},
}};

    enum class Elem {
        OctaveKnob,
        FilterKnob,
        CvIn,
        InputIn,
        Out,
        SubButton,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
