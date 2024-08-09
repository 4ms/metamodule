#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct CloudsInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Clouds"};
    static constexpr std::string_view description{"Granular Synthesizer"};
    static constexpr uint32_t width_hp = 18;
    static constexpr std::string_view svg_filename{"res/modules/Clouds_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Clouds.png"};

    using enum Coords;

    static constexpr std::array<Element, 29> Elements{{
		WhiteMomentary7mm{{to_mm<72>(34.3), to_mm<72>(54.99), Center, "Freeze", ""}},
		SmallButton{{to_mm<72>(246.79), to_mm<72>(247.07), Center, "CV Jack Mode", ""}},
		SmallButton{{to_mm<72>(12.84), to_mm<72>(247.07), Center, "Load", ""}},
		RedLargeKnob{{to_mm<72>(45.64), to_mm<72>(129.32), Center, "Position", ""}, 0.5f},
		BlueLargeKnob{{to_mm<72>(129.6), to_mm<72>(129.32), Center, "Size", ""}, 0.5f},
		WhiteLargeKnob{{to_mm<72>(212.77), to_mm<72>(129.32), Center, "Pitch", ""}, 0.5f},
		RedMediumKnob{{to_mm<72>(93.83), to_mm<72>(54.99), Center, "In Gain", ""}, 0.5f},
		RedMediumKnob{{to_mm<72>(158.97), to_mm<72>(54.99), Center, "Density", ""}, 0.5f},
		BlueMediumKnob{{to_mm<72>(224.11), to_mm<72>(54.99), Center, "Texture", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(34.3), to_mm<72>(202.85), Center, "DryWet", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(97.57), to_mm<72>(202.85), Center, "Spread", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(160.84), to_mm<72>(202.85), Center, "Feedback", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(224.11), to_mm<72>(202.85), Center, "Reverb", ""}, 0.5f},
		GateJackInput4ms{{to_mm<72>(26.11), to_mm<72>(273.49), Center, "Freeze Trig", ""}},
		GateJackInput4ms{{to_mm<72>(67.51), to_mm<72>(273.49), Center, "Trig", ""}},
		AnalogJackInput4ms{{to_mm<72>(108.91), to_mm<72>(273.49), Center, "Position CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(150.31), to_mm<72>(273.49), Center, "Size CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(191.71), to_mm<72>(273.49), Center, "V/Oct", ""}},
		AnalogJackInput4ms{{to_mm<72>(233.11), to_mm<72>(273.49), Center, "Blend CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(26.11), to_mm<72>(314.88), Center, "In L", ""}},
		AnalogJackInput4ms{{to_mm<72>(67.51), to_mm<72>(314.88), Center, "In R", ""}},
		AnalogJackInput4ms{{to_mm<72>(108.91), to_mm<72>(314.93), Center, "Density CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(150.31), to_mm<72>(314.93), Center, "Text CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(191.71), to_mm<72>(314.93), Center, "Out L", ""}},
		AnalogJackOutput4ms{{to_mm<72>(233.11), to_mm<72>(314.93), Center, "Out R", ""}},
		GreenRedLight{{to_mm<72>(34.3), to_mm<72>(246.61), Center, "Pan Light", ""}},
		GreenRedLight{{to_mm<72>(97.57), to_mm<72>(246.61), Center, "Mix Light", ""}},
		GreenRedLight{{to_mm<72>(160.84), to_mm<72>(246.61), Center, "Feedback Light", ""}},
		GreenRedLight{{to_mm<72>(224.11), to_mm<72>(246.61), Center, "Reverb Light", ""}},
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
        PanLight,
        MixLight,
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
        LedPan_Light, 
        LedMix_Light, 
        LedFeedback_Light, 
        LedReverb_Light, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
