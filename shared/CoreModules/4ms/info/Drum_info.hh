#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct DrumInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Drum"};
    static constexpr std::string_view description{"Drum Voice"};
    static constexpr uint32_t width_hp = 15;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Drum-artwork.svg"};

    static constexpr std::array<Element, 21> Elements{{
		Davies1900hBlackKnob{to_mm<72>(43.62), to_mm<72>(45.96), "Pitch", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(108.12), to_mm<72>(45.96), "Pitch Env", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(172.59), to_mm<72>(45.96), "Pitch Amt", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(43.62), to_mm<72>(104.51), "Ratio", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(108.12), to_mm<72>(104.51), "FM Env", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(172.59), to_mm<72>(104.51), "FM Amt", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(43.62), to_mm<72>(163.19), "Tone Env", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(108.12), to_mm<72>(163.19), "Noise Env", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(172.59), to_mm<72>(163.19), "Noise Blend", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(36.54), to_mm<72>(214.33), "Trigger", ""},
		AnalogJackInput4ms{to_mm<72>(84.82), to_mm<72>(214.33), "V/Oct", ""},
		AnalogJackInput4ms{to_mm<72>(133.11), to_mm<72>(214.33), "P Env CV", ""},
		AnalogJackInput4ms{to_mm<72>(181.39), to_mm<72>(214.33), "P Amt CV", ""},
		AnalogJackInput4ms{to_mm<72>(36.54), to_mm<72>(263.05), "Ratio CV", ""},
		AnalogJackInput4ms{to_mm<72>(84.82), to_mm<72>(263.05), "FM Env CV", ""},
		AnalogJackInput4ms{to_mm<72>(133.11), to_mm<72>(263.05), "FM Amt CV", ""},
		AnalogJackInput4ms{to_mm<72>(181.39), to_mm<72>(263.05), "T Env CV", ""},
		AnalogJackInput4ms{to_mm<72>(84.82), to_mm<72>(311.77), "N Env CV", ""},
		AnalogJackInput4ms{to_mm<72>(133.11), to_mm<72>(311.77), "N Blend CV", ""},
		AnalogJackOutput4ms{to_mm<72>(36.54), to_mm<72>(311.77), "Inv Out", ""},
		AnalogJackOutput4ms{to_mm<72>(181.39), to_mm<72>(311.77), "Out", ""},
}};

    enum class Elem {
        PitchKnob,
        PitchEnvKnob,
        PitchAmtKnob,
        RatioKnob,
        FmEnvKnob,
        FmAmtKnob,
        ToneEnvKnob,
        NoiseEnvKnob,
        NoiseBlendKnob,
        TriggerIn,
        V_OctIn,
        PEnvCvIn,
        PAmtCvIn,
        RatioCvIn,
        FmEnvCvIn,
        FmAmtCvIn,
        TEnvCvIn,
        NEnvCvIn,
        NBlendCvIn,
        InvOut,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobPitch = 0,
        KnobPitch_Env = 1,
        KnobPitch_Amt = 2,
        KnobRatio = 3,
        KnobFm_Env = 4,
        KnobFm_Amt = 5,
        KnobTone_Env = 6,
        KnobNoise_Env = 7,
        KnobNoise_Blend = 8,
        NumKnobs,
    };
    
    
    enum {
        InputTrigger = 0,
        InputV_Oct = 1,
        InputP_Env_Cv = 2,
        InputP_Amt_Cv = 3,
        InputRatio_Cv = 4,
        InputFm_Env_Cv = 5,
        InputFm_Amt_Cv = 6,
        InputT_Env_Cv = 7,
        InputN_Env_Cv = 8,
        InputN_Blend_Cv = 9,
        NumInJacks,
    };
    
    enum {
        OutputInv_Out = 0,
        OutputOut = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
