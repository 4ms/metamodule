#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct Prob8Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Prob8"};
    static constexpr std::string_view description{"Probability Module"};
    static constexpr uint32_t width_hp = 8;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Prob8-artwork.svg"};

    static constexpr std::array<Element, 12> Elements{{
		Davies1900hBlackKnob{to_mm<72>(32.88), to_mm<72>(47.23), "1", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(84.41), to_mm<72>(47.23), "2", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(32.88), to_mm<72>(104.31), "3", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(84.41), to_mm<72>(104.31), "4", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(32.88), to_mm<72>(163.62), "5", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(84.41), to_mm<72>(163.62), "6", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(32.88), to_mm<72>(222.39), "7", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(84.41), to_mm<72>(222.39), "8", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(31.02), to_mm<72>(272.5), "Clock", ""},
		AnalogJackInput4ms{to_mm<72>(84.69), to_mm<72>(272.5), "Reset", ""},
		AnalogJackOutput4ms{to_mm<72>(31.02), to_mm<72>(314.17), "Inv", ""},
		AnalogJackOutput4ms{to_mm<72>(84.69), to_mm<72>(314.17), "Out", ""},
}};

    enum class Elem {
        _1Knob,
        _2Knob,
        _3Knob,
        _4Knob,
        _5Knob,
        _6Knob,
        _7Knob,
        _8Knob,
        ClockIn,
        ResetIn,
        InvOut,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        Knob_1 = 0,
        Knob_2 = 1,
        Knob_3 = 2,
        Knob_4 = 3,
        Knob_5 = 4,
        Knob_6 = 5,
        Knob_7 = 6,
        Knob_8 = 7,
        NumKnobs,
    };
    
    
    enum {
        InputClock = 0,
        InputReset = 1,
        NumInJacks,
    };
    
    enum {
        OutputInv = 0,
        OutputOut = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
