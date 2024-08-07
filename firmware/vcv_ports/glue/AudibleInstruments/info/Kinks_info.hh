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
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(278.93), Center, "S x26 H IN", ""}},
		GateJackInput4ms{{to_mm<72>(40.98), to_mm<72>(278.93), Center, "Trig", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(314.93), Center, "Noise", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(314.93), Center, "S x26 H Out", ""}},
		RedGreenBlueLight{{to_mm<72>(14.89), to_mm<72>(61.1), Center, "Sign x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(14.89), to_mm<72>(158.29), Center, "Logic x40 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(14.89), to_mm<72>(255.48), Center, "S x26 H x40 GreenLight", ""}},
}};

    enum class Elem {
        Sign_In,
        Sign_Out,
        Half_Sign_Out,
        Full_Sign_Out,
        In_AIn,
        In_BIn,
        MaxOut,
        MinOut,
        S_X26_H_In,
        TrigIn,
        NoiseIn,
        S_X26_H_Out,
        Sign_X23_GreenlightLight,
        Logic_X40_GreenlightLight,
        S_X26_H_X40_GreenlightLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    
    
    enum {
        InputSign_In, 
        InputIn_A, 
        InputIn_B, 
        InputS_X26_H_In, 
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
        OutputS_X26_H_Out, 
        NumOutJacks,
    };
    
    enum {
        LedSign_X23_Greenlight, 
        LedLogic_X40_Greenlight, 
        LedS_X26_H_X40_Greenlight, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
