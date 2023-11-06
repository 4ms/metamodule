#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct Seq8Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Seq8"};
    static constexpr std::string_view description{"8 Step Sequencer"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Seq8_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 12> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(32.88), to_mm<72>(47.23), Center, "1", ""}},
		Davies1900hBlackKnob{{to_mm<72>(84.41), to_mm<72>(47.23), Center, "2", ""}},
		Davies1900hBlackKnob{{to_mm<72>(32.88), to_mm<72>(104.31), Center, "3", ""}},
		Davies1900hBlackKnob{{to_mm<72>(84.41), to_mm<72>(104.31), Center, "4", ""}},
		Davies1900hBlackKnob{{to_mm<72>(32.88), to_mm<72>(163.62), Center, "5", ""}},
		Davies1900hBlackKnob{{to_mm<72>(84.41), to_mm<72>(163.62), Center, "6", ""}},
		Davies1900hBlackKnob{{to_mm<72>(32.88), to_mm<72>(222.39), Center, "7", ""}},
		Davies1900hBlackKnob{{to_mm<72>(84.41), to_mm<72>(222.39), Center, "8", ""}},
		AnalogJackInput4ms{{to_mm<72>(31.02), to_mm<72>(272.5), Center, "Clock", ""}},
		AnalogJackInput4ms{{to_mm<72>(84.69), to_mm<72>(272.5), Center, "Reset", ""}},
		AnalogJackOutput4ms{{to_mm<72>(31.13), to_mm<72>(314.17), Center, "Gate", ""}},
		AnalogJackOutput4ms{{to_mm<72>(84.69), to_mm<72>(314.17), Center, "Out", ""}},
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
        GateOut,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
        OutputGate = 0,
        OutputOut = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
