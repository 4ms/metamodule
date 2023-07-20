#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct LIOInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"LIO"};
    static constexpr std::string_view description{"Listen IO"};
    static constexpr uint32_t width_hp = 6;
    static constexpr std::string_view svg_filename{"res/modules/LIO-artwork.svg"};

    static constexpr int NumKnobs = 2;
    
    enum {
        KnobGain = 0,
        KnobLevel = 1,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobGain,
            .x_mm = px_to_mm<72>(43.21f),
            .y_mm = px_to_mm<72>(61.27f),
            .short_name = "Gain",
            .long_name = "Gain",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel,
            .x_mm = px_to_mm<72>(43.21f),
            .y_mm = px_to_mm<72>(227.57f),
            .short_name = "Level",
            .long_name = "Level",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 4;
    
    enum {
        InputLine_In_L = 0,
        InputLine_In_R = 1,
        InputMod_In_L = 2,
        InputMod_In_R = 3,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputLine_In_L,
            .x_mm = px_to_mm<72>(21.57f),
            .y_mm = px_to_mm<72>(113.49f),
            .short_name = "Line In L",
            .long_name = "Line In L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputLine_In_R,
            .x_mm = px_to_mm<72>(64.95f),
            .y_mm = px_to_mm<72>(113.49f),
            .short_name = "Line In R",
            .long_name = "Line In R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputMod_In_L,
            .x_mm = px_to_mm<72>(21.57f),
            .y_mm = px_to_mm<72>(279.34f),
            .short_name = "Mod In L",
            .long_name = "Mod In L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputMod_In_R,
            .x_mm = px_to_mm<72>(64.95f),
            .y_mm = px_to_mm<72>(279.34f),
            .short_name = "Mod In R",
            .long_name = "Mod In R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 4;
    
    enum {
        OutputMod_Out_L = 0,
        OutputMod_Out_R = 1,
        OutputLine_Out_L = 2,
        OutputLine_Out_R = 3,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputMod_Out_L,
            .x_mm = px_to_mm<72>(21.57f),
            .y_mm = px_to_mm<72>(153.09f),
            .short_name = "Mod Out L",
            .long_name = "Mod Out L",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputMod_Out_R,
            .x_mm = px_to_mm<72>(64.76f),
            .y_mm = px_to_mm<72>(153.09f),
            .short_name = "Mod Out R",
            .long_name = "Mod Out R",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputLine_Out_L,
            .x_mm = px_to_mm<72>(21.57f),
            .y_mm = px_to_mm<72>(319.12f),
            .short_name = "Line Out L",
            .long_name = "Line Out L",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputLine_Out_R,
            .x_mm = px_to_mm<72>(64.76f),
            .y_mm = px_to_mm<72>(319.12f),
            .short_name = "Line Out R",
            .long_name = "Line Out R",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 0;
    

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
    }};

    static constexpr int NumDiscreteLeds = 16;
    
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
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedLed_L1_4,
            .x_mm = px_to_mm<72>(10.34f),
            .y_mm = px_to_mm<72>(41.12f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_L1_3,
            .x_mm = px_to_mm<72>(10.34f),
            .y_mm = px_to_mm<72>(54.33f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_L1_2,
            .x_mm = px_to_mm<72>(10.34f),
            .y_mm = px_to_mm<72>(67.29f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_L1_1,
            .x_mm = px_to_mm<72>(10.34f),
            .y_mm = px_to_mm<72>(80.34f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_R1_4,
            .x_mm = px_to_mm<72>(76.1f),
            .y_mm = px_to_mm<72>(41.12f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_R1_3,
            .x_mm = px_to_mm<72>(76.1f),
            .y_mm = px_to_mm<72>(54.33f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_R1_2,
            .x_mm = px_to_mm<72>(76.1f),
            .y_mm = px_to_mm<72>(67.29f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_R1_1,
            .x_mm = px_to_mm<72>(76.1f),
            .y_mm = px_to_mm<72>(80.34f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_L2_4,
            .x_mm = px_to_mm<72>(10.34f),
            .y_mm = px_to_mm<72>(207.58f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_L2_3,
            .x_mm = px_to_mm<72>(10.34f),
            .y_mm = px_to_mm<72>(220.79f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_L2_2,
            .x_mm = px_to_mm<72>(10.34f),
            .y_mm = px_to_mm<72>(233.75f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_L2_1,
            .x_mm = px_to_mm<72>(10.34f),
            .y_mm = px_to_mm<72>(246.8f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_R2_4,
            .x_mm = px_to_mm<72>(76.1f),
            .y_mm = px_to_mm<72>(207.58f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_R2_3,
            .x_mm = px_to_mm<72>(76.1f),
            .y_mm = px_to_mm<72>(220.79f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_R2_2,
            .x_mm = px_to_mm<72>(76.1f),
            .y_mm = px_to_mm<72>(233.75f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_R2_1,
            .x_mm = px_to_mm<72>(76.1f),
            .y_mm = px_to_mm<72>(246.8f),
            .led_color = LedDef::Red,
        },
    }};

};
