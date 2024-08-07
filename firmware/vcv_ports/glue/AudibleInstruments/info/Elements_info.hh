#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ElementsInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Elements"};
    static constexpr std::string_view description{"Pecussion Synthesizer"};
    static constexpr uint32_t width_hp = 34;
    static constexpr std::string_view svg_filename{"res/modules/Elements_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Elements.png"};

    using enum Coords;

    static constexpr std::array<Element, 48> Elements{{
		WhiteMediumKnob{{to_mm<72>(47.58), to_mm<72>(60.35), Center, "Contour", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(114.99), to_mm<72>(60.35), Center, "Bow", ""}, 0.5f},
		RedMediumKnob{{to_mm<72>(182.51), to_mm<72>(60.35), Center, "Blow", ""}, 0.5f},
		RedMediumKnob{{to_mm<72>(250.03), to_mm<72>(60.35), Center, "Strike", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(317.55), to_mm<72>(60.35), Center, "Coarse", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(385.07), to_mm<72>(60.35), Center, "Fine", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(452.59), to_mm<72>(60.35), Center, "FM", ""}, 0.5f},
		OrangeButton{{to_mm<72>(47.58), to_mm<72>(124.27), Center, "Play", ""}},
		RedLargeKnob{{to_mm<72>(135.71), to_mm<72>(137.31), Center, "Flow", ""}, 0.5f},
		BlueLargeKnob{{to_mm<72>(229.31), to_mm<72>(137.31), Center, "Mallet", ""}, 0.5f},
		WhiteLargeKnob{{to_mm<72>(338.27), to_mm<72>(137.31), Center, "Geometry", ""}, 0.5f},
		WhiteLargeKnob{{to_mm<72>(431.87), to_mm<72>(137.31), Center, "Brightness", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(114.99), to_mm<72>(214.27), Center, "Bow Timbre", ""}, 0.5f},
		RedMediumKnob{{to_mm<72>(182.51), to_mm<72>(214.27), Center, "Blow Timbre", ""}, 0.5f},
		BlueMediumKnob{{to_mm<72>(250.03), to_mm<72>(214.27), Center, "Strike Timbre", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(317.55), to_mm<72>(214.27), Center, "Damping", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(385.07), to_mm<72>(214.27), Center, "Position", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(452.59), to_mm<72>(214.27), Center, "Space", ""}, 0.5f},
		WhiteSmallKnob{{to_mm<72>(108.81), to_mm<72>(270.97), Center, "Bow Timbre Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(145.66), to_mm<72>(270.97), Center, "Flow Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(182.51), to_mm<72>(270.97), Center, "Blow Timbre Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(219.36), to_mm<72>(270.97), Center, "Mallet Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(256.21), to_mm<72>(270.97), Center, "Strike Timbre Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(311.37), to_mm<72>(270.97), Center, "Damping Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(348.22), to_mm<72>(270.97), Center, "Geometry Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(385.07), to_mm<72>(270.97), Center, "Position Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(421.92), to_mm<72>(270.97), Center, "Brightness Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(458.77), to_mm<72>(270.97), Center, "Space Atten", ""}, 0.0f},
		AnalogJackInput4ms{{to_mm<72>(30.49), to_mm<72>(182.75), Center, "V/Oct", ""}},
		AnalogJackInput4ms{{to_mm<72>(64.67), to_mm<72>(182.75), Center, "FM", ""}},
		GateJackInput4ms{{to_mm<72>(30.49), to_mm<72>(226.86), Center, "Gate", ""}},
		AnalogJackInput4ms{{to_mm<72>(64.67), to_mm<72>(226.86), Center, "Strength", ""}},
		AnalogJackInput4ms{{to_mm<72>(30.49), to_mm<72>(270.97), Center, "Ext IN Blow", ""}},
		AnalogJackInput4ms{{to_mm<72>(64.67), to_mm<72>(270.97), Center, "Ext IN Strike", ""}},
		AnalogJackOutput4ms{{to_mm<72>(30.49), to_mm<72>(315.07), Center, "Out L", ""}},
		AnalogJackOutput4ms{{to_mm<72>(64.67), to_mm<72>(315.07), Center, "Out R", ""}},
		AnalogJackInput4ms{{to_mm<72>(108.81), to_mm<72>(315.07), Center, "Bow Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(145.66), to_mm<72>(315.07), Center, "Flow CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(182.51), to_mm<72>(315.07), Center, "Blow Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(219.36), to_mm<72>(315.07), Center, "Mallet CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(256.21), to_mm<72>(315.07), Center, "Strike Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(311.37), to_mm<72>(315.07), Center, "Damping CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(348.22), to_mm<72>(315.07), Center, "Geometry CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(385.07), to_mm<72>(315.07), Center, "Position CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(421.92), to_mm<72>(315.07), Center, "Brightness CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(458.77), to_mm<72>(315.07), Center, "Space CV", ""}},
		GreenLight{{to_mm<72>(182.51), to_mm<72>(163.87), Center, "ControlExciter LED", ""}},
		RedLight{{to_mm<72>(385.07), to_mm<72>(163.87), Center, "Resonator LED", ""}},
}};

    enum class Elem {
        ContourKnob,
        BowKnob,
        BlowKnob,
        StrikeKnob,
        CoarseKnob,
        FineKnob,
        FmKnob,
        PlayButton,
        FlowKnob,
        MalletKnob,
        GeometryKnob,
        BrightnessKnob,
        BowTimbreKnob,
        BlowTimbreKnob,
        StrikeTimbreKnob,
        DampingKnob,
        PositionKnob,
        SpaceKnob,
        BowTimbreAttenKnob,
        FlowAttenKnob,
        BlowTimbreAttenKnob,
        MalletAttenKnob,
        StrikeTimbreAttenKnob,
        DampingAttenKnob,
        GeometryAttenKnob,
        PositionAttenKnob,
        BrightnessAttenKnob,
        SpaceAttenKnob,
        V_OctIn,
        FmIn,
        GateIn,
        StrengthIn,
        ExtInBlowIn,
        ExtInStrikeIn,
        OutLOut,
        OutROut,
        BowTimbreCvIn,
        FlowCvIn,
        BlowTimbreCvIn,
        MalletCvIn,
        StrikeTimbreCvIn,
        DampingCvIn,
        GeometryCvIn,
        PositionCvIn,
        BrightnessCvIn,
        SpaceCvIn,
        ControlexciterLedLight,
        ResonatorLedLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobContour, 
        KnobBow, 
        KnobBlow, 
        KnobStrike, 
        KnobCoarse, 
        KnobFine, 
        KnobFm, 
        KnobFlow, 
        KnobMallet, 
        KnobGeometry, 
        KnobBrightness, 
        KnobBow_Timbre, 
        KnobBlow_Timbre, 
        KnobStrike_Timbre, 
        KnobDamping, 
        KnobPosition, 
        KnobSpace, 
        KnobBow_Timbre_Atten, 
        KnobFlow_Atten, 
        KnobBlow_Timbre_Atten, 
        KnobMallet_Atten, 
        KnobStrike_Timbre_Atten, 
        KnobDamping_Atten, 
        KnobGeometry_Atten, 
        KnobPosition_Atten, 
        KnobBrightness_Atten, 
        KnobSpace_Atten, 
        NumKnobs,
    };
    
    enum {
        SwitchPlay, 
        NumSwitches,
    };
    
    enum {
        InputV_Oct, 
        InputFm, 
        InputGate, 
        InputStrength, 
        InputExt_In_Blow, 
        InputExt_In_Strike, 
        InputBow_Timbre_Cv, 
        InputFlow_Cv, 
        InputBlow_Timbre_Cv, 
        InputMallet_Cv, 
        InputStrike_Timbre_Cv, 
        InputDamping_Cv, 
        InputGeometry_Cv, 
        InputPosition_Cv, 
        InputBrightness_Cv, 
        InputSpace_Cv, 
        NumInJacks,
    };
    
    enum {
        OutputOut_L, 
        OutputOut_R, 
        NumOutJacks,
    };
    
    enum {
        LedControlexciter_Led, 
        LedResonator_Led, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
