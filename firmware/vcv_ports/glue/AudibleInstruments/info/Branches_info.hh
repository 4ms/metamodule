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
		WhiteMediumKnob{{to_mm<72>(42.64), to_mm<72>(81.06), Center, "Ch1 Probability", ""}, 0.5f},
		OrangeButton{{to_mm<72>(73.2), to_mm<72>(63.04), Center, "Ch1 Mode", ""}},
		WhiteMediumKnob{{to_mm<72>(42.64), to_mm<72>(230.44), Center, "Ch2 Probability", ""}, 0.5f},
		OrangeButton{{to_mm<72>(73.2), to_mm<72>(212.46), Center, "Ch2 Mode", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.15), to_mm<72>(129.66), Center, "Ch1 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(65.11), to_mm<72>(129.66), Center, "Ch1 Probability", ""}},
		AnalogJackOutput4ms{{to_mm<72>(20.15), to_mm<72>(165.66), Center, "Ch1 Out A", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.11), to_mm<72>(165.66), Center, "Ch1 Out B", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.15), to_mm<72>(279.04), Center, "Ch2 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(65.11), to_mm<72>(279.04), Center, "Ch2 Probability", ""}},
		AnalogJackOutput4ms{{to_mm<72>(20.15), to_mm<72>(315.04), Center, "Ch2 Out A", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.11), to_mm<72>(315.04), Center, "Ch2 Out B", ""}},
		OrangeLight{{to_mm<72>(42.63), to_mm<72>(165.69), Center, "Ch1 Mode", ""}},
		OrangeLight{{to_mm<72>(42.63), to_mm<72>(315.07), Center, "Ch2 Mode", ""}},
}};

    enum class Elem {
        Ch1ProbabilityKnob,
        Ch1ModeButton,
        Ch2ProbabilityKnob,
        Ch2ModeButton,
        Ch1In,
        Ch1ProbabilityIn,
        Ch1OutAOut,
        Ch1OutBOut,
        Ch2In,
        Ch2ProbabilityIn,
        Ch2OutAOut,
        Ch2OutBOut,
        Ch1ModeLight,
        Ch2ModeLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1_Probability, 
        KnobCh2_Probability, 
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
        LedCh1_Mode, 
        LedCh2_Mode, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
