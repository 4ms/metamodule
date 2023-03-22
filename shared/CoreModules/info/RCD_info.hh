#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct RCDInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"RCD"};
    static constexpr std::string_view description{"Rotating Clock Divider"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/RCD-artwork.svg"};

    static constexpr int NumKnobs = 0;
    

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
    }};

    static constexpr int NumInJacks = 3;
    
    enum {
        InputClk_In = 0,
        InputRotate = 1,
        InputReset = 2,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputClk_In,
            .x_mm = px_to_mm<72>(48.19f),
            .y_mm = px_to_mm<72>(56.31f),
            .short_name = "Clk In",
            .long_name = "Clk In",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRotate,
            .x_mm = px_to_mm<72>(92.61f),
            .y_mm = px_to_mm<72>(56.31f),
            .short_name = "Rotate",
            .long_name = "Rotate",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset,
            .x_mm = px_to_mm<72>(123.98f),
            .y_mm = px_to_mm<72>(56.31f),
            .short_name = "Reset",
            .long_name = "Reset",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 8;
    
    enum {
        OutputD1 = 0,
        OutputD2 = 1,
        OutputD3 = 2,
        OutputD4 = 3,
        OutputD5 = 4,
        OutputD6 = 5,
        OutputD7 = 6,
        OutputD8 = 7,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputD1,
            .x_mm = px_to_mm<72>(48.19f),
            .y_mm = px_to_mm<72>(87.93f),
            .short_name = "d1",
            .long_name = "d1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputD2,
            .x_mm = px_to_mm<72>(48.19f),
            .y_mm = px_to_mm<72>(119.54f),
            .short_name = "d2",
            .long_name = "d2",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputD3,
            .x_mm = px_to_mm<72>(48.19f),
            .y_mm = px_to_mm<72>(151.16f),
            .short_name = "d3",
            .long_name = "d3",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputD4,
            .x_mm = px_to_mm<72>(48.19f),
            .y_mm = px_to_mm<72>(182.78f),
            .short_name = "d4",
            .long_name = "d4",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputD5,
            .x_mm = px_to_mm<72>(48.19f),
            .y_mm = px_to_mm<72>(214.39f),
            .short_name = "d5",
            .long_name = "d5",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputD6,
            .x_mm = px_to_mm<72>(48.19f),
            .y_mm = px_to_mm<72>(246.01f),
            .short_name = "d6",
            .long_name = "d6",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputD7,
            .x_mm = px_to_mm<72>(48.19f),
            .y_mm = px_to_mm<72>(277.62f),
            .short_name = "d7",
            .long_name = "d7",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputD8,
            .x_mm = px_to_mm<72>(48.19f),
            .y_mm = px_to_mm<72>(309.24f),
            .short_name = "d8",
            .long_name = "d8",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 6;
    
    enum {
        SwitchCounting = 0,
        SwitchGate_Trig = 1,
        SwitchMax_Div_1 = 2,
        SwitchMax_Div_2 = 3,
        SwitchSpread = 4,
        SwitchAutoNReset = 5,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchCounting,
            .x_mm = px_to_mm<72>(108.8f),
            .y_mm = px_to_mm<72>(93.345f),
            .short_name = "Counting",
            .long_name = "Counting",
            .switch_type = SwitchDef::Toggle2pos,
            .orientation = SwitchDef::Horizontal,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchGate_Trig,
            .x_mm = px_to_mm<72>(108.8f),
            .y_mm = px_to_mm<72>(133.445f),
            .short_name = "Gate Trig",
            .long_name = "Gate Trig",
            .switch_type = SwitchDef::Toggle2pos,
            .orientation = SwitchDef::Horizontal,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchMax_Div_1,
            .x_mm = px_to_mm<72>(108.61f),
            .y_mm = px_to_mm<72>(181.245f),
            .short_name = "Max Div 1",
            .long_name = "Max Div 1",
            .switch_type = SwitchDef::Toggle2pos,
            .orientation = SwitchDef::Horizontal,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchMax_Div_2,
            .x_mm = px_to_mm<72>(108.61f),
            .y_mm = px_to_mm<72>(220.965f),
            .short_name = "Max Div 2",
            .long_name = "Max Div 2",
            .switch_type = SwitchDef::Toggle2pos,
            .orientation = SwitchDef::Horizontal,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchSpread,
            .x_mm = px_to_mm<72>(108.8f),
            .y_mm = px_to_mm<72>(266.615f),
            .short_name = "Spread",
            .long_name = "Spread",
            .switch_type = SwitchDef::Toggle2pos,
            .orientation = SwitchDef::Horizontal,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchAutoNReset,
            .x_mm = px_to_mm<72>(108.8f),
            .y_mm = px_to_mm<72>(306.335f),
            .short_name = "Auto-Reset",
            .long_name = "Auto-Reset",
            .switch_type = SwitchDef::Toggle2pos,
            .orientation = SwitchDef::Horizontal,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 9;
    
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
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedLed_In,
            .x_mm = px_to_mm<72>(19.98f),
            .y_mm = px_to_mm<72>(56.31f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_D1,
            .x_mm = px_to_mm<72>(19.98f),
            .y_mm = px_to_mm<72>(87.93f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_D2,
            .x_mm = px_to_mm<72>(19.98f),
            .y_mm = px_to_mm<72>(119.54f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_D3,
            .x_mm = px_to_mm<72>(19.98f),
            .y_mm = px_to_mm<72>(151.16f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_D4,
            .x_mm = px_to_mm<72>(19.98f),
            .y_mm = px_to_mm<72>(182.78f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_D5,
            .x_mm = px_to_mm<72>(19.98f),
            .y_mm = px_to_mm<72>(214.39f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_D6,
            .x_mm = px_to_mm<72>(19.98f),
            .y_mm = px_to_mm<72>(246.01f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_D7,
            .x_mm = px_to_mm<72>(19.98f),
            .y_mm = px_to_mm<72>(277.62f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_D8,
            .x_mm = px_to_mm<72>(19.98f),
            .y_mm = px_to_mm<72>(309.24f),
            .led_color = LedDef::Red,
        },
    }};

};
