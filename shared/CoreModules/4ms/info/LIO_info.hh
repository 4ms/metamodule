#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct LIOInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"LIO"};
    static constexpr std::string_view description{"Listen IO"};
    static constexpr uint32_t width_hp = 6;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/LIO-artwork.svg"};

    static constexpr std::array<Element, 26> Elements{{
		Davies1900hBlackKnob{to_mm<72>(43.21), to_mm<72>(61.27), "Gain", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(43.21), to_mm<72>(227.57), "Level", "", 0, 0, 1, 0.875f},
		AnalogJackInput4ms{to_mm<72>(21.57), to_mm<72>(113.49), "Line In L", ""},
		AnalogJackInput4ms{to_mm<72>(64.95), to_mm<72>(113.49), "Line In R", ""},
		AnalogJackInput4ms{to_mm<72>(21.57), to_mm<72>(279.34), "Mod In L", ""},
		AnalogJackInput4ms{to_mm<72>(64.95), to_mm<72>(279.34), "Mod In R", ""},
		AnalogJackOutput4ms{to_mm<72>(21.57), to_mm<72>(153.09), "Mod Out L", ""},
		AnalogJackOutput4ms{to_mm<72>(64.76), to_mm<72>(153.09), "Mod Out R", ""},
		AnalogJackOutput4ms{to_mm<72>(21.57), to_mm<72>(319.12), "Line Out L", ""},
		AnalogJackOutput4ms{to_mm<72>(64.76), to_mm<72>(319.12), "Line Out R", ""},
		RedGreenBlueLight{to_mm<72>(10.34), to_mm<72>(41.12), "LED L1 4", ""},
		RedGreenBlueLight{to_mm<72>(10.34), to_mm<72>(54.33), "LED L1 3", ""},
		RedGreenBlueLight{to_mm<72>(10.34), to_mm<72>(67.29), "LED L1 2", ""},
		RedGreenBlueLight{to_mm<72>(10.34), to_mm<72>(80.34), "LED L1 1", ""},
		RedGreenBlueLight{to_mm<72>(76.1), to_mm<72>(41.12), "LED R1 4", ""},
		RedGreenBlueLight{to_mm<72>(76.1), to_mm<72>(54.33), "LED R1 3", ""},
		RedGreenBlueLight{to_mm<72>(76.1), to_mm<72>(67.29), "LED R1 2", ""},
		RedGreenBlueLight{to_mm<72>(76.1), to_mm<72>(80.34), "LED R1 1", ""},
		RedGreenBlueLight{to_mm<72>(10.34), to_mm<72>(207.58), "LED L2 4", ""},
		RedGreenBlueLight{to_mm<72>(10.34), to_mm<72>(220.79), "LED L2 3", ""},
		RedGreenBlueLight{to_mm<72>(10.34), to_mm<72>(233.75), "LED L2 2", ""},
		RedGreenBlueLight{to_mm<72>(10.34), to_mm<72>(246.8), "LED L2 1", ""},
		RedGreenBlueLight{to_mm<72>(76.1), to_mm<72>(207.58), "LED R2 4", ""},
		RedGreenBlueLight{to_mm<72>(76.1), to_mm<72>(220.79), "LED R2 3", ""},
		RedGreenBlueLight{to_mm<72>(76.1), to_mm<72>(233.75), "LED R2 2", ""},
		RedGreenBlueLight{to_mm<72>(76.1), to_mm<72>(246.8), "LED R2 1", ""},
}};

    enum class Elem {
        GainKnob,
        LevelKnob,
        LineInLIn,
        LineInRIn,
        ModInLIn,
        ModInRIn,
        ModOutLOut,
        ModOutROut,
        LineOutLOut,
        LineOutROut,
        LedL14Light,
        LedL13Light,
        LedL12Light,
        LedL11Light,
        LedR14Light,
        LedR13Light,
        LedR12Light,
        LedR11Light,
        LedL24Light,
        LedL23Light,
        LedL22Light,
        LedL21Light,
        LedR24Light,
        LedR23Light,
        LedR22Light,
        LedR21Light,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobGain = 0,
        KnobLevel = 1,
        NumKnobs,
    };
    
    
    enum {
        InputLine_In_L = 0,
        InputLine_In_R = 1,
        InputMod_In_L = 2,
        InputMod_In_R = 3,
        NumInJacks,
    };
    
    enum {
        OutputMod_Out_L = 0,
        OutputMod_Out_R = 1,
        OutputLine_Out_L = 2,
        OutputLine_Out_R = 3,
        NumOutJacks,
    };
    
    enum {
        LedLed_L1_4 = 0,
        LedLed_L1_3 = 1,
        LedLed_L1_2 = 2,
        LedLed_L1_1 = 3,
        LedLed_R1_4 = 4,
        LedLed_R1_3 = 5,
        LedLed_R1_2 = 6,
        LedLed_R1_1 = 7,
        LedLed_L2_4 = 8,
        LedLed_L2_3 = 9,
        LedLed_L2_2 = 10,
        LedLed_L2_1 = 11,
        LedLed_R2_4 = 12,
        LedLed_R2_3 = 13,
        LedLed_R2_2 = 14,
        LedLed_R2_1 = 15,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
