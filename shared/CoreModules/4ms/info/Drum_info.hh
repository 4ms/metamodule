#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct DrumInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Drum"};
    static constexpr std::string_view description{"Drum Voice"};
    static constexpr uint32_t width_hp = 15;
    static constexpr std::string_view svg_filename{"res/modules/Drum_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 21> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(43.62), to_mm<72>(45.96), Center, "Pitch", ""}},
		Davies1900hBlackKnob{{to_mm<72>(108.12), to_mm<72>(45.96), Center, "Pitch Env", ""}},
		Davies1900hBlackKnob{{to_mm<72>(172.59), to_mm<72>(45.96), Center, "Pitch Amt", ""}},
		Davies1900hBlackKnob{{to_mm<72>(43.62), to_mm<72>(104.51), Center, "Ratio", ""}},
		Davies1900hBlackKnob{{to_mm<72>(108.12), to_mm<72>(104.51), Center, "FM Env", ""}},
		Davies1900hBlackKnob{{to_mm<72>(172.59), to_mm<72>(104.51), Center, "FM Amt", ""}},
		Davies1900hBlackKnob{{to_mm<72>(43.62), to_mm<72>(163.19), Center, "Tone Env", ""}},
		Davies1900hBlackKnob{{to_mm<72>(108.12), to_mm<72>(163.19), Center, "Noise Env", ""}},
		Davies1900hBlackKnob{{to_mm<72>(172.59), to_mm<72>(163.19), Center, "Noise Blend", ""}},
		AnalogJackInput4ms{{to_mm<72>(36.54), to_mm<72>(214.33), Center, "Trigger", ""}},
		AnalogJackInput4ms{{to_mm<72>(84.82), to_mm<72>(214.33), Center, "V/Oct", ""}},
		AnalogJackInput4ms{{to_mm<72>(133.11), to_mm<72>(214.33), Center, "P Env CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(181.39), to_mm<72>(214.33), Center, "P Amt CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(36.54), to_mm<72>(263.05), Center, "Ratio CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(84.82), to_mm<72>(263.05), Center, "FM Env CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(133.11), to_mm<72>(263.05), Center, "FM Amt CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(181.39), to_mm<72>(263.05), Center, "T Env CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(84.82), to_mm<72>(311.77), Center, "N Env CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(133.11), to_mm<72>(311.77), Center, "N Blend CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(36.54), to_mm<72>(311.77), Center, "Inv Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(181.39), to_mm<72>(311.77), Center, "Out", ""}},
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

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
