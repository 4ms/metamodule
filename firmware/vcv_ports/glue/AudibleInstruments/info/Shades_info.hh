#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ShadesInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Shades"};
    static constexpr std::string_view description{"Mixer"};
    static constexpr uint32_t width_hp = 6;
    static constexpr std::string_view svg_filename{"res/modules/Shades_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Shades.png"};

    using enum Coords;

    static constexpr std::array<Element, 15> Elements{{
		Toggle2pos{{to_mm<72>(16.27), to_mm<72>(59.415), Center, "Ch1 Mode Switch x40 Atten x40 Attenuvert", ""}},
		Davies1900hBlackKnob{{to_mm<72>(57.66), to_mm<72>(59.44), Center, "Ch1 x23 WhiteMediumKnob", ""}, 0.5f},
		Toggle2pos{{to_mm<72>(16.27), to_mm<72>(122.455), Center, "Ch2 Mode Switch x40 Atten x40 Attenuvert", ""}},
		Davies1900hBlackKnob{{to_mm<72>(57.66), to_mm<72>(122.46), Center, "Ch2 x23 WhiteMediumKnob", ""}, 0.5f},
		Toggle2pos{{to_mm<72>(16.27), to_mm<72>(185.475), Center, "Ch3 Mode Switch x40 Atten x40 Attenuvert", ""}},
		Davies1900hBlackKnob{{to_mm<72>(57.66), to_mm<72>(185.47), Center, "Ch3 x23 WhiteMediumKnob", ""}, 0.5f},
		AnalogJackInput4ms{{to_mm<72>(20.75), to_mm<72>(246.71), Center, "Ch1 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.76), to_mm<72>(246.64), Center, "Ch1 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.75), to_mm<72>(280.86), Center, "Ch2 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.76), to_mm<72>(280.86), Center, "Ch2 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.75), to_mm<72>(315.07), Center, "Ch3 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.76), to_mm<72>(315.07), Center, "Ch3 Out", ""}},
		RedGreenBlueLight{{to_mm<72>(43.26), to_mm<72>(246.64), Center, "Ch1 LED x23 RedGreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(43.26), to_mm<72>(280.86), Center, "Ch2 LED x23 RedGreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(43.26), to_mm<72>(315.07), Center, "Ch3 LED x23 RedGreenLight", ""}},
}};

    enum class Elem {
        Ch1_Mode_Switch_X40_Atten_X40_AttenuvertSwitch,
        Ch1_X23_WhitemediumknobKnob,
        Ch2_Mode_Switch_X40_Atten_X40_AttenuvertSwitch,
        Ch2_X23_WhitemediumknobKnob,
        Ch3_Mode_Switch_X40_Atten_X40_AttenuvertSwitch,
        Ch3_X23_WhitemediumknobKnob,
        Ch1_In,
        Ch1_Out,
        Ch2_In,
        Ch2_Out,
        Ch3_In,
        Ch3_Out,
        Ch1_Led_X23_RedgreenlightLight,
        Ch2_Led_X23_RedgreenlightLight,
        Ch3_Led_X23_RedgreenlightLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1_X23_Whitemediumknob, 
        KnobCh2_X23_Whitemediumknob, 
        KnobCh3_X23_Whitemediumknob, 
        NumKnobs,
    };
    
    enum {
        SwitchCh1_Mode_Switch_X40_Atten_X40_Attenuvert, 
        SwitchCh2_Mode_Switch_X40_Atten_X40_Attenuvert, 
        SwitchCh3_Mode_Switch_X40_Atten_X40_Attenuvert, 
        NumSwitches,
    };
    
    enum {
        InputCh1_In, 
        InputCh2_In, 
        InputCh3_In, 
        NumInJacks,
    };
    
    enum {
        OutputCh1_Out, 
        OutputCh2_Out, 
        OutputCh3_Out, 
        NumOutJacks,
    };
    
    enum {
        LedCh1_Led_X23_Redgreenlight, 
        LedCh2_Led_X23_Redgreenlight, 
        LedCh3_Led_X23_Redgreenlight, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
