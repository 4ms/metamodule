#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct CloudsInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Clouds"};
    static constexpr std::string_view description{"Granular Synthesizer"};
    static constexpr uint32_t width_hp = 19;
    static constexpr std::string_view svg_filename{"res/modules/Clouds_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Clouds.png"};

    using enum Coords;

    static constexpr std::array<Element, 29> Elements{{
		WhiteMomentary7mm{{to_mm<72>(41.9), to_mm<72>(55.35), Center, "Freeze", ""}},
		SmallButton{{to_mm<72>(254.38), to_mm<72>(246.97), Center, "CV Jack Mode", ""}},
		SmallButton{{to_mm<72>(41.9), to_mm<72>(25.63), Center, "Load", ""}},
		RedLargeKnob{{to_mm<72>(53.23), to_mm<72>(129.67), Center, "Position", ""}, 0.5f},
		BlueLargeKnob{{to_mm<72>(137.2), to_mm<72>(129.67), Center, "Size", ""}, 0.5f},
		WhiteLargeKnob{{to_mm<72>(220.37), to_mm<72>(129.67), Center, "Pitch", ""}, 0.5f},
		RedMediumKnob{{to_mm<72>(101.42), to_mm<72>(55.35), Center, "In Gain", ""}, 0.5f},
		RedMediumKnob{{to_mm<72>(166.56), to_mm<72>(55.35), Center, "Density", ""}, 0.5f},
		BlueMediumKnob{{to_mm<72>(231.7), to_mm<72>(55.35), Center, "Texture", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(41.9), to_mm<72>(203.2), Center, "DryWet", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(105.17), to_mm<72>(203.2), Center, "Spread", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(168.43), to_mm<72>(203.2), Center, "Feedback", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(231.7), to_mm<72>(203.2), Center, "Reverb", ""}, 0.5f},
		GateJackInput4ms{{to_mm<72>(33.7), to_mm<72>(273.85), Center, "Freeze Trig", ""}},
		GateJackInput4ms{{to_mm<72>(75.1), to_mm<72>(273.85), Center, "Trig", ""}},
		AnalogJackInput4ms{{to_mm<72>(116.5), to_mm<72>(273.85), Center, "Position CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(157.9), to_mm<72>(273.85), Center, "Size CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(199.31), to_mm<72>(273.85), Center, "V/Oct", ""}},
		AnalogJackInput4ms{{to_mm<72>(240.7), to_mm<72>(273.85), Center, "Blend CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(33.7), to_mm<72>(315.24), Center, "In L", ""}},
		AnalogJackInput4ms{{to_mm<72>(75.1), to_mm<72>(315.24), Center, "In R", ""}},
		AnalogJackInput4ms{{to_mm<72>(116.5), to_mm<72>(315.28), Center, "Density CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(157.9), to_mm<72>(315.28), Center, "Text CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(199.31), to_mm<72>(315.28), Center, "Out L", ""}},
		AnalogJackOutput4ms{{to_mm<72>(240.7), to_mm<72>(315.28), Center, "Out R", ""}},
		GreenRedLight{{to_mm<72>(105.17), to_mm<72>(246.97), Center, "Mix Light", ""}},
		GreenRedLight{{to_mm<72>(41.9), to_mm<72>(246.97), Center, "Pan Light", ""}},
		GreenRedLight{{to_mm<72>(168.43), to_mm<72>(246.97), Center, "Feedback Light", ""}},
		GreenRedLight{{to_mm<72>(231.7), to_mm<72>(246.97), Center, "Reverb Light", ""}},
}};

    enum class Elem {
        FreezeButton,
        CvJackModeButton,
        LoadButton,
        PositionKnob,
        SizeKnob,
        PitchKnob,
        InGainKnob,
        DensityKnob,
        TextureKnob,
        DrywetKnob,
        SpreadKnob,
        FeedbackKnob,
        ReverbKnob,
        FreezeTrigIn,
        TrigIn,
        PositionCvIn,
        SizeCvIn,
        V_OctIn,
        BlendCvIn,
        InLIn,
        InRIn,
        DensityCvIn,
        TextCvIn,
        OutLOut,
        OutROut,
        MixLight,
        PanLight,
        FeedbackLight,
        ReverbLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobPosition, 
        KnobSize, 
        KnobPitch, 
        KnobIn_Gain, 
        KnobDensity, 
        KnobTexture, 
        KnobDrywet, 
        KnobSpread, 
        KnobFeedback, 
        KnobReverb, 
        NumKnobs,
    };
    
    enum {
        SwitchFreeze, 
        SwitchCv_Jack_Mode, 
        SwitchLoad, 
        NumSwitches,
    };
    
    enum {
        InputFreeze_Trig, 
        InputTrig, 
        InputPosition_Cv, 
        InputSize_Cv, 
        InputV_Oct, 
        InputBlend_Cv, 
        InputIn_L, 
        InputIn_R, 
        InputDensity_Cv, 
        InputText_Cv, 
        NumInJacks,
    };
    
    enum {
        OutputOut_L, 
        OutputOut_R, 
        NumOutJacks,
    };
    
    enum {
        LedMix_Light, 
        LedPan_Light, 
        LedFeedback_Light, 
        LedReverb_Light, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
