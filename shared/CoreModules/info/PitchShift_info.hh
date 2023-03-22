#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct PitchShiftInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"PitchShift"};
    static constexpr std::string_view description{"Pitch Shifter"};
    static constexpr uint32_t width_hp = 7;
    static constexpr std::string_view svg_filename{"res/modules/PitchShift-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        KnobCoarse = 0,
        KnobFine = 1,
        KnobWindow = 2,
        KnobMix = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobCoarse,
            .x_mm = px_to_mm<72>(50.53f),
            .y_mm = px_to_mm<72>(46.91f),
            .short_name = "Coarse",
            .long_name = "Coarse",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFine,
            .x_mm = px_to_mm<72>(50.52f),
            .y_mm = px_to_mm<72>(94.87f),
            .short_name = "Fine",
            .long_name = "Fine",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobWindow,
            .x_mm = px_to_mm<72>(50.52f),
            .y_mm = px_to_mm<72>(139.62f),
            .short_name = "Window",
            .long_name = "Window",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobMix,
            .x_mm = px_to_mm<72>(50.52f),
            .y_mm = px_to_mm<72>(184.38f),
            .short_name = "Mix",
            .long_name = "Mix",
            .default_val = 0.875f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 4;
    
    enum {
        InputInput = 0,
        InputPitch_Cv = 1,
        InputWindow_Cv = 2,
        InputMix_Cv = 3,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(30.92f),
            .y_mm = px_to_mm<72>(232.48f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPitch_Cv,
            .x_mm = px_to_mm<72>(69.92f),
            .y_mm = px_to_mm<72>(232.48f),
            .short_name = "Pitch CV",
            .long_name = "Pitch CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputWindow_Cv,
            .x_mm = px_to_mm<72>(30.92f),
            .y_mm = px_to_mm<72>(281.58f),
            .short_name = "Window CV",
            .long_name = "Window CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputMix_Cv,
            .x_mm = px_to_mm<72>(69.92f),
            .y_mm = px_to_mm<72>(281.58f),
            .short_name = "Mix CV",
            .long_name = "Mix CV",
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
            .x_mm = px_to_mm<72>(69.92f),
            .y_mm = px_to_mm<72>(326.11f),
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
