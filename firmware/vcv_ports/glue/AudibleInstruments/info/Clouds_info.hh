#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
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

    static constexpr std::array<Element, 22> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(101.42), to_mm<72>(55.35), Center, "In Gain x23 RedMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(166.56), to_mm<72>(55.35), Center, "Density x23 RedMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(231.7), to_mm<72>(55.35), Center, "Texture x23 BlueMediumKnob", ""}, 0.5f},
		DaviesLargeKnob{{to_mm<72>(53.23), to_mm<72>(129.67), Center, "Position x23 RedLargeKnob", ""}, 0.5f},
		DaviesLargeKnob{{to_mm<72>(137.2), to_mm<72>(129.67), Center, "Size x23 BlueLargeKnob", ""}, 0.5f},
		DaviesLargeKnob{{to_mm<72>(220.37), to_mm<72>(129.67), Center, "Pitch x23 WhiteLargeKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(41.9), to_mm<72>(203.2), Center, "DryWet x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(105.17), to_mm<72>(203.2), Center, "Spread x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(168.43), to_mm<72>(203.2), Center, "Feedback x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(231.7), to_mm<72>(203.2), Center, "Reverb x23 WhiteMediumKnob", ""}, 0.5f},
		GateJackInput4ms{{to_mm<72>(33.7), to_mm<72>(273.85), Center, "Freeze Trig", ""}},
		GateJackInput4ms{{to_mm<72>(75.1), to_mm<72>(273.85), Center, "Trig", ""}},
		AnalogJackInput4ms{{to_mm<72>(116.5), to_mm<72>(273.85), Center, "Position CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(157.9), to_mm<72>(273.85), Center, "Size CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(199.31), to_mm<72>(273.85), Center, "V x2F Oct", ""}},
		AnalogJackInput4ms{{to_mm<72>(240.7), to_mm<72>(273.85), Center, "Blend CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(33.7), to_mm<72>(315.24), Center, "In L", ""}},
		AnalogJackInput4ms{{to_mm<72>(75.1), to_mm<72>(315.24), Center, "In R", ""}},
		AnalogJackInput4ms{{to_mm<72>(116.5), to_mm<72>(315.28), Center, "Density CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(157.9), to_mm<72>(315.28), Center, "Text CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(199.31), to_mm<72>(315.28), Center, "Out L", ""}},
		AnalogJackOutput4ms{{to_mm<72>(240.7), to_mm<72>(315.28), Center, "Out R", ""}},
}};

    enum class Elem {
        In_Gain_X23_RedmediumknobKnob,
        Density_X23_RedmediumknobKnob,
        Texture_X23_BluemediumknobKnob,
        Position_X23_RedlargeknobKnob,
        Size_X23_BluelargeknobKnob,
        Pitch_X23_WhitelargeknobKnob,
        Drywet_X23_WhitemediumknobKnob,
        Spread_X23_WhitemediumknobKnob,
        Feedback_X23_WhitemediumknobKnob,
        Reverb_X23_WhitemediumknobKnob,
        Freeze_TrigIn,
        TrigIn,
        Position_CvIn,
        Size_CvIn,
        V_X2F_OctIn,
        Blend_CvIn,
        In_LIn,
        In_RIn,
        Density_CvIn,
        Text_CvIn,
        Out_LOut,
        Out_ROut,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobIn_Gain_X23_Redmediumknob, 
        KnobDensity_X23_Redmediumknob, 
        KnobTexture_X23_Bluemediumknob, 
        KnobPosition_X23_Redlargeknob, 
        KnobSize_X23_Bluelargeknob, 
        KnobPitch_X23_Whitelargeknob, 
        KnobDrywet_X23_Whitemediumknob, 
        KnobSpread_X23_Whitemediumknob, 
        KnobFeedback_X23_Whitemediumknob, 
        KnobReverb_X23_Whitemediumknob, 
        NumKnobs,
    };
    
    
    enum {
        InputFreeze_Trig, 
        InputTrig, 
        InputPosition_Cv, 
        InputSize_Cv, 
        InputV_X2F_Oct, 
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
    
    
};
} // namespace MetaModule
