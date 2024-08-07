#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct KinksInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Kinks"};
    static constexpr std::string_view description{"Utilities"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Kinks_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Kinks.png"};

    using enum Coords;

    static constexpr std::array<Element, 15> Elements{{
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(84.53), Center, "Sign In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(84.53), Center, "Sign Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(15.74), to_mm<72>(120.53), Center, "Half Sign Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(120.53), Center, "Full Sign Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(181.73), Center, "IN A", ""}},
		AnalogJackInput4ms{{to_mm<72>(40.98), to_mm<72>(181.73), Center, "IN B", ""}},
		AnalogJackOutput4ms{{to_mm<72>(15.74), to_mm<72>(217.73), Center, "MAX", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(217.73), Center, "MIN", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(278.93), Center, "S&amp;H IN", ""}},
		GateJackInput4ms{{to_mm<72>(40.98), to_mm<72>(278.93), Center, "Trig", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(314.93), Center, "Noise", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(314.93), Center, "S&amp;H Out", ""}},
		GreenLight{{to_mm<72>(14.89), to_mm<72>(61.1), Center, "Sign", ""}},
		GreenLight{{to_mm<72>(14.89), to_mm<72>(158.29), Center, "Logic", ""}},
		GreenLight{{to_mm<72>(14.89), to_mm<72>(255.48), Center, "S&amp;H", ""}},
}};

    enum class Elem {
        SignIn,
        SignOut,
        HalfSignOut,
        FullSignOut,
        InAIn,
        InBIn,
        MaxOut,
        MinOut,
        S_Amp_HIn,
        TrigIn,
        NoiseIn,
        S_Amp_HOut,
        SignLight,
        LogicLight,
        S_Amp_HLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    
    
    enum {
        InputSign_In, 
        InputIn_A, 
        InputIn_B, 
        InputS_Amp_H_In, 
        InputTrig, 
        InputNoise, 
        NumInJacks,
    };
    
    enum {
        OutputSign_Out, 
        OutputHalf_Sign_Out, 
        OutputFull_Sign_Out, 
        OutputMax, 
        OutputMin, 
        OutputS_Amp_H_Out, 
        NumOutJacks,
    };
    
    enum {
        LedSign, 
        LedLogic, 
        LedS_Amp_H, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
