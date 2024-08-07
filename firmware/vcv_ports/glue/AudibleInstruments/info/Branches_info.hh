#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct BranchesInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Branches"};
    static constexpr std::string_view description{"Gate Generator"};
    static constexpr uint32_t width_hp = 6;
    static constexpr std::string_view svg_filename{"res/modules/Branches_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Branches.png"};

    using enum Coords;

    static constexpr std::array<Element, 14> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(42.64), to_mm<72>(81.06), Center, "Ch1 Probability x23 WhiteMediumKnob", ""}, 0.5f},
		OrangeButton{{to_mm<72>(73.2), to_mm<72>(63.04), Center, "Ch1 Mode", ""}},
		Davies1900hBlackKnob{{to_mm<72>(42.64), to_mm<72>(230.44), Center, "Ch2 Probability x23 WhiteMediumKnob", ""}, 0.5f},
		OrangeButton{{to_mm<72>(73.2), to_mm<72>(212.46), Center, "Ch2 Mode", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.15), to_mm<72>(129.66), Center, "Ch1 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(65.11), to_mm<72>(129.66), Center, "Ch1 Probability", ""}},
		AnalogJackOutput4ms{{to_mm<72>(20.15), to_mm<72>(165.66), Center, "Ch1 Out A", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.11), to_mm<72>(165.66), Center, "Ch1 Out B", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.15), to_mm<72>(279.04), Center, "Ch2 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(65.11), to_mm<72>(279.04), Center, "Ch2 Probability", ""}},
		AnalogJackOutput4ms{{to_mm<72>(20.15), to_mm<72>(315.04), Center, "Ch2 Out A", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.11), to_mm<72>(315.04), Center, "Ch2 Out B", ""}},
		RedGreenBlueLight{{to_mm<72>(42.63), to_mm<72>(165.69), Center, "Ch1 Mode x23 OrangeLight", ""}},
		RedGreenBlueLight{{to_mm<72>(42.63), to_mm<72>(315.07), Center, "Ch2 Mode x23 OrangeLight", ""}},
}};

    enum class Elem {
        Ch1_Probability_X23_WhitemediumknobKnob,
        Ch1_ModeButton,
        Ch2_Probability_X23_WhitemediumknobKnob,
        Ch2_ModeButton,
        Ch1_In,
        Ch1_ProbabilityIn,
        Ch1_Out_AOut,
        Ch1_Out_BOut,
        Ch2_In,
        Ch2_ProbabilityIn,
        Ch2_Out_AOut,
        Ch2_Out_BOut,
        Ch1_Mode_X23_OrangelightLight,
        Ch2_Mode_X23_OrangelightLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1_Probability_X23_Whitemediumknob, 
        KnobCh2_Probability_X23_Whitemediumknob, 
        NumKnobs,
    };
    
    enum {
        SwitchCh1_Mode, 
        SwitchCh2_Mode, 
        NumSwitches,
    };
    
    enum {
        InputCh1_In, 
        InputCh1_Probability, 
        InputCh2_In, 
        InputCh2_Probability, 
        NumInJacks,
    };
    
    enum {
        OutputCh1_Out_A, 
        OutputCh1_Out_B, 
        OutputCh2_Out_A, 
        OutputCh2_Out_B, 
        NumOutJacks,
    };
    
    enum {
        LedCh1_Mode_X23_Orangelight, 
        LedCh2_Mode_X23_Orangelight, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
