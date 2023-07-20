#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct InfOscInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"InfOsc"};
    static constexpr std::string_view description{"Infinite Oscillator"};
    static constexpr uint32_t width_hp = 15;
    static constexpr std::string_view svg_filename{"res/modules/InfOsc-artwork.svg"};

    static constexpr int NumKnobs = 8;
    
    enum {
        KnobTrack = 0,
        KnobAbs = 1,
        KnobRange = 2,
        KnobFm = 3,
        KnobPitch = 4,
        KnobPhase = 5,
        KnobModshape = 6,
        KnobWave = 7,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobTrack,
            .x_mm = px_to_mm<72>(43.62f),
            .y_mm = px_to_mm<72>(46.55f),
            .short_name = "Track",
            .long_name = "Track",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobAbs,
            .x_mm = px_to_mm<72>(108.12f),
            .y_mm = px_to_mm<72>(46.55f),
            .short_name = "Abs",
            .long_name = "Abs",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobRange,
            .x_mm = px_to_mm<72>(172.62f),
            .y_mm = px_to_mm<72>(46.55f),
            .short_name = "Range",
            .long_name = "Range",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFm,
            .x_mm = px_to_mm<72>(43.62f),
            .y_mm = px_to_mm<72>(105.5f),
            .short_name = "FM",
            .long_name = "FM",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPitch,
            .x_mm = px_to_mm<72>(108.13f),
            .y_mm = px_to_mm<72>(117.06f),
            .short_name = "Pitch",
            .long_name = "Pitch",
            .default_val = 0.5f,
            .knob_style = KnobDef::Large,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPhase,
            .x_mm = px_to_mm<72>(172.62f),
            .y_mm = px_to_mm<72>(105.5f),
            .short_name = "Phase",
            .long_name = "Phase",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobModshape,
            .x_mm = px_to_mm<72>(43.3f),
            .y_mm = px_to_mm<72>(164.67f),
            .short_name = "Modshape",
            .long_name = "Modshape",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobWave,
            .x_mm = px_to_mm<72>(172.52f),
            .y_mm = px_to_mm<72>(164.62f),
            .short_name = "Wave",
            .long_name = "Wave",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 11;
    
    enum {
        InputPm_Cv = 0,
        InputScan_Cv = 1,
        InputAdd_Cv = 2,
        InputReset_Cv = 3,
        InputMod_Cv = 4,
        InputAbs_Cv = 5,
        InputLin_Cv = 6,
        InputPhase_Cv = 7,
        InputPitch_Cv = 8,
        InputRange_Cv = 9,
        InputFm_Cv = 10,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputPm_Cv,
            .x_mm = px_to_mm<72>(35.96f),
            .y_mm = px_to_mm<72>(214.54f),
            .short_name = "PM CV",
            .long_name = "PM CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputScan_Cv,
            .x_mm = px_to_mm<72>(83.96f),
            .y_mm = px_to_mm<72>(214.54f),
            .short_name = "Scan CV",
            .long_name = "Scan CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputAdd_Cv,
            .x_mm = px_to_mm<72>(131.96f),
            .y_mm = px_to_mm<72>(214.54f),
            .short_name = "Add CV",
            .long_name = "Add CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset_Cv,
            .x_mm = px_to_mm<72>(179.96f),
            .y_mm = px_to_mm<72>(214.54f),
            .short_name = "Reset CV",
            .long_name = "Reset CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputMod_Cv,
            .x_mm = px_to_mm<72>(35.96f),
            .y_mm = px_to_mm<72>(263.64f),
            .short_name = "Mod CV",
            .long_name = "Mod CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputAbs_Cv,
            .x_mm = px_to_mm<72>(83.96f),
            .y_mm = px_to_mm<72>(263.64f),
            .short_name = "Abs CV",
            .long_name = "Abs CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputLin_Cv,
            .x_mm = px_to_mm<72>(131.96f),
            .y_mm = px_to_mm<72>(263.64f),
            .short_name = "Lin CV",
            .long_name = "Lin CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPhase_Cv,
            .x_mm = px_to_mm<72>(179.96f),
            .y_mm = px_to_mm<72>(263.64f),
            .short_name = "Phase CV",
            .long_name = "Phase CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPitch_Cv,
            .x_mm = px_to_mm<72>(35.96f),
            .y_mm = px_to_mm<72>(311.23f),
            .short_name = "Pitch CV",
            .long_name = "Pitch CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRange_Cv,
            .x_mm = px_to_mm<72>(83.96f),
            .y_mm = px_to_mm<72>(311.23f),
            .short_name = "Range CV",
            .long_name = "Range CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFm_Cv,
            .x_mm = px_to_mm<72>(131.96f),
            .y_mm = px_to_mm<72>(311.23f),
            .short_name = "FM CV",
            .long_name = "FM CV",
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
            .x_mm = px_to_mm<72>(179.96f),
            .y_mm = px_to_mm<72>(311.23f),
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
