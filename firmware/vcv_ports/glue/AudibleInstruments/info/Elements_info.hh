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
		Davies1900hBlackKnob{{to_mm<72>(47.58), to_mm<72>(60.35), Center, "Contour x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(114.99), to_mm<72>(60.35), Center, "Bow x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(182.51), to_mm<72>(60.35), Center, "Blow x23 RedMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(250.03), to_mm<72>(60.35), Center, "Strike x23 RedMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(317.55), to_mm<72>(60.35), Center, "Coarse x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(385.07), to_mm<72>(60.35), Center, "Fine x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(452.59), to_mm<72>(60.35), Center, "FM x23 WhiteMediumKnob", ""}, 0.5f},
		OrangeButton{{to_mm<72>(47.58), to_mm<72>(124.27), Center, "Play", ""}},
		DaviesLargeKnob{{to_mm<72>(135.71), to_mm<72>(137.31), Center, "Flow x23 RedLargeKnob", ""}, 0.5f},
		DaviesLargeKnob{{to_mm<72>(229.31), to_mm<72>(137.31), Center, "Mallet x23 BlueLargeKnob", ""}, 0.5f},
		DaviesLargeKnob{{to_mm<72>(338.27), to_mm<72>(137.31), Center, "Geometry x23 WhiteLargeKnob", ""}, 0.5f},
		DaviesLargeKnob{{to_mm<72>(431.87), to_mm<72>(137.31), Center, "Brightness x23 WhiteLargeKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(114.99), to_mm<72>(214.27), Center, "Bow Timbre x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(182.51), to_mm<72>(214.27), Center, "Blow Timbre x23 RedMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(250.03), to_mm<72>(214.27), Center, "Strike Timbre x23 BlueMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(317.55), to_mm<72>(214.27), Center, "Damping x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(385.07), to_mm<72>(214.27), Center, "Position x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(452.59), to_mm<72>(214.27), Center, "Space x23 WhiteMediumKnob", ""}, 0.5f},
		Knob9mm{{to_mm<72>(108.81), to_mm<72>(270.97), Center, "Bow Timbre Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(145.66), to_mm<72>(270.97), Center, "Flow Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(182.51), to_mm<72>(270.97), Center, "Blow Timbre Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(219.36), to_mm<72>(270.97), Center, "Mallet Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(256.21), to_mm<72>(270.97), Center, "Strike Timbre Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(311.37), to_mm<72>(270.97), Center, "Damping Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(348.22), to_mm<72>(270.97), Center, "Geometry Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(385.07), to_mm<72>(270.97), Center, "Position Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(421.92), to_mm<72>(270.97), Center, "Brightness Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(458.77), to_mm<72>(270.97), Center, "Space Atten x23 WhiteSmallKnob", ""}, 0.0f},
		AnalogJackInput4ms{{to_mm<72>(30.49), to_mm<72>(182.75), Center, "V x2F Oct", ""}},
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
		RedGreenBlueLight{{to_mm<72>(182.51), to_mm<72>(163.87), Center, "ControlExciter LED x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(385.07), to_mm<72>(163.87), Center, "Resonator LED x23 RedLight", ""}},
}};

    enum class Elem {
        Contour_X23_WhitemediumknobKnob,
        Bow_X23_WhitemediumknobKnob,
        Blow_X23_RedmediumknobKnob,
        Strike_X23_RedmediumknobKnob,
        Coarse_X23_WhitemediumknobKnob,
        Fine_X23_WhitemediumknobKnob,
        Fm_X23_WhitemediumknobKnob,
        PlayButton,
        Flow_X23_RedlargeknobKnob,
        Mallet_X23_BluelargeknobKnob,
        Geometry_X23_WhitelargeknobKnob,
        Brightness_X23_WhitelargeknobKnob,
        Bow_Timbre_X23_WhitemediumknobKnob,
        Blow_Timbre_X23_RedmediumknobKnob,
        Strike_Timbre_X23_BluemediumknobKnob,
        Damping_X23_WhitemediumknobKnob,
        Position_X23_WhitemediumknobKnob,
        Space_X23_WhitemediumknobKnob,
        Bow_Timbre_Atten_X23_WhitesmallknobKnob,
        Flow_Atten_X23_WhitesmallknobKnob,
        Blow_Timbre_Atten_X23_WhitesmallknobKnob,
        Mallet_Atten_X23_WhitesmallknobKnob,
        Strike_Timbre_Atten_X23_WhitesmallknobKnob,
        Damping_Atten_X23_WhitesmallknobKnob,
        Geometry_Atten_X23_WhitesmallknobKnob,
        Position_Atten_X23_WhitesmallknobKnob,
        Brightness_Atten_X23_WhitesmallknobKnob,
        Space_Atten_X23_WhitesmallknobKnob,
        V_X2F_OctIn,
        FmIn,
        GateIn,
        StrengthIn,
        Ext_In_BlowIn,
        Ext_In_StrikeIn,
        Out_LOut,
        Out_ROut,
        Bow_Timbre_CvIn,
        Flow_CvIn,
        Blow_Timbre_CvIn,
        Mallet_CvIn,
        Strike_Timbre_CvIn,
        Damping_CvIn,
        Geometry_CvIn,
        Position_CvIn,
        Brightness_CvIn,
        Space_CvIn,
        Controlexciter_Led_X23_GreenlightLight,
        Resonator_Led_X23_RedlightLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobContour_X23_Whitemediumknob, 
        KnobBow_X23_Whitemediumknob, 
        KnobBlow_X23_Redmediumknob, 
        KnobStrike_X23_Redmediumknob, 
        KnobCoarse_X23_Whitemediumknob, 
        KnobFine_X23_Whitemediumknob, 
        KnobFm_X23_Whitemediumknob, 
        KnobFlow_X23_Redlargeknob, 
        KnobMallet_X23_Bluelargeknob, 
        KnobGeometry_X23_Whitelargeknob, 
        KnobBrightness_X23_Whitelargeknob, 
        KnobBow_Timbre_X23_Whitemediumknob, 
        KnobBlow_Timbre_X23_Redmediumknob, 
        KnobStrike_Timbre_X23_Bluemediumknob, 
        KnobDamping_X23_Whitemediumknob, 
        KnobPosition_X23_Whitemediumknob, 
        KnobSpace_X23_Whitemediumknob, 
        KnobBow_Timbre_Atten_X23_Whitesmallknob, 
        KnobFlow_Atten_X23_Whitesmallknob, 
        KnobBlow_Timbre_Atten_X23_Whitesmallknob, 
        KnobMallet_Atten_X23_Whitesmallknob, 
        KnobStrike_Timbre_Atten_X23_Whitesmallknob, 
        KnobDamping_Atten_X23_Whitesmallknob, 
        KnobGeometry_Atten_X23_Whitesmallknob, 
        KnobPosition_Atten_X23_Whitesmallknob, 
        KnobBrightness_Atten_X23_Whitesmallknob, 
        KnobSpace_Atten_X23_Whitesmallknob, 
        NumKnobs,
    };
    
    enum {
        SwitchPlay, 
        NumSwitches,
    };
    
    enum {
        InputV_X2F_Oct, 
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
        LedControlexciter_Led_X23_Greenlight, 
        LedResonator_Led_X23_Redlight, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
