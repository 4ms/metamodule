#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct VerbInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Verb"};
    static constexpr std::string_view description{"Reverb Effect"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/Verb-artwork.svg"};

    static constexpr int NumKnobs = 6;
    
    enum {
        KnobSize = 0,
        KnobTime = 1,
        KnobDamp = 2,
        KnobAp_Ratio = 3,
        KnobComb = 4,
        KnobMix = 5,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobSize,
            .x_mm = px_to_mm<72>(37.85f),
            .y_mm = px_to_mm<72>(46.42f),
            .short_name = "Size",
            .long_name = "Size",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobTime,
            .x_mm = px_to_mm<72>(106.4f),
            .y_mm = px_to_mm<72>(46.42f),
            .short_name = "Time",
            .long_name = "Time",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDamp,
            .x_mm = px_to_mm<72>(37.85f),
            .y_mm = px_to_mm<72>(103.51f),
            .short_name = "Damp",
            .long_name = "Damp",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobAp_Ratio,
            .x_mm = px_to_mm<72>(106.4f),
            .y_mm = px_to_mm<72>(103.51f),
            .short_name = "AP Ratio",
            .long_name = "AP Ratio",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobComb,
            .x_mm = px_to_mm<72>(37.85f),
            .y_mm = px_to_mm<72>(162.82f),
            .short_name = "Comb",
            .long_name = "Comb",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobMix,
            .x_mm = px_to_mm<72>(106.4f),
            .y_mm = px_to_mm<72>(162.82f),
            .short_name = "Mix",
            .long_name = "Mix",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 6;
    
    enum {
        InputSize_Cv = 0,
        InputTime_Cv = 1,
        InputDamp_Cv = 2,
        InputRatio_Cv = 3,
        InputComb_Cv = 4,
        InputMix_Cv = 5,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputSize_Cv,
            .x_mm = px_to_mm<72>(29.94f),
            .y_mm = px_to_mm<72>(232.1f),
            .short_name = "Size CV",
            .long_name = "Size CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTime_Cv,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(232.1f),
            .short_name = "Time CV",
            .long_name = "Time CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDamp_Cv,
            .x_mm = px_to_mm<72>(115.17f),
            .y_mm = px_to_mm<72>(232.1f),
            .short_name = "Damp CV",
            .long_name = "Damp CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRatio_Cv,
            .x_mm = px_to_mm<72>(29.94f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "Ratio CV",
            .long_name = "Ratio CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputComb_Cv,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "Comb CV",
            .long_name = "Comb CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputMix_Cv,
            .x_mm = px_to_mm<72>(115.17f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "Mix CV",
            .long_name = "Mix CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 3;
    
    enum {
        OutputThru = 0,
        OutputPreverb = 1,
        OutputOut = 2,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputThru,
            .x_mm = px_to_mm<72>(29.94f),
            .y_mm = px_to_mm<72>(313.84f),
            .short_name = "Thru",
            .long_name = "Thru",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputPreverb,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(313.84f),
            .short_name = "Preverb",
            .long_name = "Preverb",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut,
            .x_mm = px_to_mm<72>(115.17f),
            .y_mm = px_to_mm<72>(313.84f),
            .short_name = "Out",
            .long_name = "Out",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 1;
    
    enum {
        SwitchHold = 0,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchHold,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(199.9f),
            .short_name = "Hold",
            .long_name = "Hold",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 0;
    

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
    }};

};
