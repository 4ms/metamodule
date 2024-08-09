#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
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
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(84.53), Center, "Inverted Sign Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(15.74), to_mm<72>(120.53), Center, "Half Rect. Sign Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(120.53), Center, "Full Rect. Sign Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(181.73), Center, "Logic In A", ""}},
		AnalogJackInput4ms{{to_mm<72>(40.98), to_mm<72>(181.73), Center, "Logic In B", ""}},
		AnalogJackOutput4ms{{to_mm<72>(15.74), to_mm<72>(217.73), Center, "Logic Max Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(217.73), Center, "Logic Min Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(278.93), Center, "S&amp;H In", ""}},
		GateJackInput4ms{{to_mm<72>(40.98), to_mm<72>(278.93), Center, "S&amp;H Trig In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(15.74), to_mm<72>(314.93), Center, "Noise Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(314.93), Center, "S&amp;H Out", ""}},
		GreenRedLight{{to_mm<72>(14.89), to_mm<72>(61.1), Center, "Sign", ""}},
		GreenRedLight{{to_mm<72>(14.89), to_mm<72>(158.29), Center, "Logic", ""}},
		GreenRedLight{{to_mm<72>(14.89), to_mm<72>(255.48), Center, "S&amp;H", ""}},
}};

    enum class Elem {
        SignIn,
        InvertedSignOut,
        HalfRect_SignOut,
        FullRect_SignOut,
        LogicInAIn,
        LogicInBIn,
        LogicMaxOut,
        LogicMinOut,
        S_Amp_HIn,
        S_Amp_HTrigIn,
        NoiseOut,
        S_Amp_HOut,
        SignLight,
        LogicLight,
        S_Amp_HLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    
    
    enum {
        InputSign_In, 
        InputLogic_In_A, 
        InputLogic_In_B, 
        InputS_Amp_H_In, 
        InputS_Amp_H_Trig_In, 
        NumInJacks,
    };
    
    enum {
        OutputInverted_Sign_Out, 
        OutputHalf_Rect__Sign_Out, 
        OutputFull_Rect__Sign_Out, 
        OutputLogic_Max_Out, 
        OutputLogic_Min_Out, 
        OutputNoise_Out, 
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
