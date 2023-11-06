#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct RCDInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"RCD"};
    static constexpr std::string_view description{"Rotating Clock Divider"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/RCD_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 26> Elements{{
		GateJackInput4ms{{to_mm<72>(48.19), to_mm<72>(56.31), Center, "Clk In", ""}},
		AnalogJackInput4ms{{to_mm<72>(92.61), to_mm<72>(56.31), Center, "Rotate", ""}},
		GateJackInput4ms{{to_mm<72>(123.98), to_mm<72>(56.31), Center, "Reset", ""}},
		GateJackOutput4ms{{to_mm<72>(48.19), to_mm<72>(87.93), Center, "d1", ""}},
		GateJackOutput4ms{{to_mm<72>(48.19), to_mm<72>(119.54), Center, "d2", ""}},
		GateJackOutput4ms{{to_mm<72>(48.19), to_mm<72>(151.16), Center, "d3", ""}},
		GateJackOutput4ms{{to_mm<72>(48.19), to_mm<72>(182.78), Center, "d4", ""}},
		GateJackOutput4ms{{to_mm<72>(48.19), to_mm<72>(214.39), Center, "d5", ""}},
		GateJackOutput4ms{{to_mm<72>(48.19), to_mm<72>(246.01), Center, "d6", ""}},
		GateJackOutput4ms{{to_mm<72>(48.19), to_mm<72>(277.62), Center, "d7", ""}},
		GateJackOutput4ms{{to_mm<72>(48.19), to_mm<72>(309.24), Center, "d8", ""}},
		RedGreenBlueLight{{to_mm<72>(19.98), to_mm<72>(56.31), Center, "LED in", ""}},
		RedGreenBlueLight{{to_mm<72>(19.98), to_mm<72>(87.93), Center, "LED d1", ""}},
		RedGreenBlueLight{{to_mm<72>(19.98), to_mm<72>(119.54), Center, "LED d2", ""}},
		RedGreenBlueLight{{to_mm<72>(19.98), to_mm<72>(151.16), Center, "LED d3", ""}},
		RedGreenBlueLight{{to_mm<72>(19.98), to_mm<72>(182.78), Center, "LED d4", ""}},
		RedGreenBlueLight{{to_mm<72>(19.98), to_mm<72>(214.39), Center, "LED d5", ""}},
		RedGreenBlueLight{{to_mm<72>(19.98), to_mm<72>(246.01), Center, "LED d6", ""}},
		RedGreenBlueLight{{to_mm<72>(19.98), to_mm<72>(277.62), Center, "LED d7", ""}},
		RedGreenBlueLight{{to_mm<72>(19.98), to_mm<72>(309.24), Center, "LED d8", ""}},
		Toggle2posHoriz{{to_mm<72>(108.8), to_mm<72>(93.345), Center, "Counting", ""}},
		Toggle2posHoriz{{to_mm<72>(108.8), to_mm<72>(133.445), Center, "Gate Trig", ""}},
		Toggle2posHoriz{{to_mm<72>(108.61), to_mm<72>(181.245), Center, "Max Div 1", ""}},
		Toggle2posHoriz{{to_mm<72>(108.61), to_mm<72>(220.965), Center, "Max Div 2", ""}},
		Toggle2posHoriz{{to_mm<72>(108.8), to_mm<72>(266.615), Center, "Spread", ""}},
		Toggle2posHoriz{{to_mm<72>(108.8), to_mm<72>(306.335), Center, "Auto-Reset", ""}},
}};

    enum class Elem {
        ClkIn,
        RotateIn,
        ResetIn,
        D1Out,
        D2Out,
        D3Out,
        D4Out,
        D5Out,
        D6Out,
        D7Out,
        D8Out,
        LedInLight,
        LedD1Light,
        LedD2Light,
        LedD3Light,
        LedD4Light,
        LedD5Light,
        LedD6Light,
        LedD7Light,
        LedD8Light,
        CountingSwitch,
        GateTrigSwitch,
        MaxDiv1Switch,
        MaxDiv2Switch,
        SpreadSwitch,
        AutoNResetSwitch,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    
    enum {
        SwitchCounting = 0,
        SwitchGate_Trig = 1,
        SwitchMax_Div_1 = 2,
        SwitchMax_Div_2 = 3,
        SwitchSpread = 4,
        SwitchAutoNReset = 5,
        NumSwitches,
    };
    
    enum {
        InputClk_In = 0,
        InputRotate = 1,
        InputReset = 2,
        NumInJacks,
    };
    
    enum {
        OutputD1 = 0,
        OutputD2 = 1,
        OutputD3 = 2,
        OutputD4 = 3,
        OutputD5 = 4,
        OutputD6 = 5,
        OutputD7 = 6,
        OutputD8 = 7,
        NumOutJacks,
    };
    
    enum {
        LedLed_In = 0,
        LedLed_D1 = 1,
        LedLed_D2 = 2,
        LedLed_D3 = 3,
        LedLed_D4 = 4,
        LedLed_D5 = 5,
        LedLed_D6 = 6,
        LedLed_D7 = 7,
        LedLed_D8 = 8,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
