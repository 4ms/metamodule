#pragma once
#include "CoreModules/AudibleInstruments/AudibleInstruments_elements.hh"
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
		WhiteMediumKnob{{to_mm<72>(42.64), to_mm<72>(230.44), Center, "Ch2 Probability", ""}, 0.5f},
		SmallButton{{to_mm<72>(73.2), to_mm<72>(63.04), Center, "Ch1 Toggle Mode", ""}},
		SmallButton{{to_mm<72>(73.2), to_mm<72>(212.46), Center, "Ch2 Toggle Mode", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.15), to_mm<72>(129.66), Center, "Ch1 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.15), to_mm<72>(279.04), Center, "Ch2 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(65.11), to_mm<72>(129.66), Center, "Ch1 Probability", ""}},
		AnalogJackInput4ms{{to_mm<72>(65.11), to_mm<72>(279.04), Center, "Ch2 Probability", ""}},
		AnalogJackOutput4ms{{to_mm<72>(20.15), to_mm<72>(165.66), Center, "Ch1 Out A", ""}},
		AnalogJackOutput4ms{{to_mm<72>(20.15), to_mm<72>(315.04), Center, "Ch2 Out A", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.11), to_mm<72>(165.66), Center, "Ch1 Out B", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.11), to_mm<72>(315.04), Center, "Ch2 Out B", ""}},
		GreenRedLight{{to_mm<72>(42.63), to_mm<72>(165.69), Center, "Ch1 Mode", ""}},
		GreenRedLight{{to_mm<72>(42.63), to_mm<72>(315.07), Center, "Ch2 Mode", ""}},
}};

    enum class Elem {
        Ch1ProbabilityKnob,
        Ch2ProbabilityKnob,
        Ch1ToggleModeButton,
        Ch2ToggleModeButton,
        Ch1In,
        Ch2In,
        Ch1ProbabilityIn,
        Ch2ProbabilityIn,
        Ch1OutAOut,
        Ch2OutAOut,
        Ch1OutBOut,
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
        SwitchCh1_Toggle_Mode, 
        SwitchCh2_Toggle_Mode, 
        NumSwitches,
    };
    
    enum {
        InputCh1_In, 
        InputCh2_In, 
        InputCh1_Probability, 
        InputCh2_Probability, 
        NumInJacks,
    };
    
    enum {
        OutputCh1_Out_A, 
        OutputCh2_Out_A, 
        OutputCh1_Out_B, 
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
