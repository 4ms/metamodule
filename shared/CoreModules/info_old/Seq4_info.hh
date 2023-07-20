#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct Seq4Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Seq4"};
    static constexpr std::string_view description{"4 Step Sequencer"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Seq4-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        Knob_1 = 0,
        Knob_2 = 1,
        Knob_3 = 2,
        Knob_4 = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = Knob_1,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(46.53f),
            .short_name = "1",
            .long_name = "1",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_2,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(94.22f),
            .short_name = "2",
            .long_name = "2",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_3,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(142.91f),
            .short_name = "3",
            .long_name = "3",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_4,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(191.1f),
            .short_name = "4",
            .long_name = "4",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 1;
    
    enum {
        InputClock = 0,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputClock,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(263.82f),
            .short_name = "Clock",
            .long_name = "Clock",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 1;
    
    enum {
        OutputOut = 0,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOut,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(312.04f),
            .short_name = "Out",
            .long_name = "Out",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 0;
    

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
    }};

    static constexpr int NumDiscreteLeds = 0;
    

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
    }};

};
