#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct Gate8Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Gate8"};
    static constexpr std::string_view description{"8 Step Gate Sequencer"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Gate8-artwork.svg"};

    static constexpr int NumKnobs = 0;
    

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputClock = 0,
        InputReset = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputClock,
            .x_mm = px_to_mm<72>(32.07f),
            .y_mm = px_to_mm<72>(262.57f),
            .short_name = "Clock",
            .long_name = "Clock",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset,
            .x_mm = px_to_mm<72>(83.61f),
            .y_mm = px_to_mm<72>(262.57f),
            .short_name = "Reset",
            .long_name = "Reset",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        OutputEnd = 0,
        OutputOut = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputEnd,
            .x_mm = px_to_mm<72>(32.07f),
            .y_mm = px_to_mm<72>(310.16f),
            .short_name = "End",
            .long_name = "End",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut,
            .x_mm = px_to_mm<72>(83.61f),
            .y_mm = px_to_mm<72>(310.16f),
            .short_name = "Out",
            .long_name = "Out",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 8;
    
    enum {
        SwitchStep_1 = 0,
        SwitchStep_2 = 1,
        SwitchStep_3 = 2,
        SwitchStep_4 = 3,
        SwitchStep_5 = 4,
        SwitchStep_6 = 5,
        SwitchStep_7 = 6,
        SwitchStep_8 = 7,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchStep_1,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(45.78f),
            .short_name = "Step 1",
            .long_name = "Step 1",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchStep_2,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(45.78f),
            .short_name = "Step 2",
            .long_name = "Step 2",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchStep_3,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(88.3f),
            .short_name = "Step 3",
            .long_name = "Step 3",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchStep_4,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(88.3f),
            .short_name = "Step 4",
            .long_name = "Step 4",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchStep_5,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(130.82f),
            .short_name = "Step 5",
            .long_name = "Step 5",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchStep_6,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(130.82f),
            .short_name = "Step 6",
            .long_name = "Step 6",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchStep_7,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(173.25f),
            .short_name = "Step 7",
            .long_name = "Step 7",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchStep_8,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(173.34f),
            .short_name = "Step 8",
            .long_name = "Step 8",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 0;
    

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
    }};

};
