#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct PanInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Pan"};
    static constexpr std::string_view description{"Panner"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Pan-artwork.svg"};

    static constexpr int NumKnobs = 1;
    
    enum {
        KnobPan = 0,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobPan,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(47.42f),
            .short_name = "Pan",
            .long_name = "Pan",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputCv = 0,
        InputIn = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputCv,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(166.45f),
            .short_name = "CV",
            .long_name = "CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(214.54f),
            .short_name = "In",
            .long_name = "In",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOut_1,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(263.64f),
            .short_name = "Out 1",
            .long_name = "Out 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_2,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(311.23f),
            .short_name = "Out 2",
            .long_name = "Out 2",
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
