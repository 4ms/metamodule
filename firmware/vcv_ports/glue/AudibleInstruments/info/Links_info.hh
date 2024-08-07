#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct LinksInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Links"};
    static constexpr std::string_view description{"Multiples"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Links_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Links.png"};

    using enum Coords;

    static constexpr std::array<Element, 15> Elements{{
		AnalogJackInput4ms{{to_mm<72>(15.87), to_mm<72>(84.67), Center, "A1 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(41.11), to_mm<72>(84.67), Center, "A1 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(15.87), to_mm<72>(120.67), Center, "A2 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(41.11), to_mm<72>(120.67), Center, "A3 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.87), to_mm<72>(181.87), Center, "B1 IN", ""}},
		AnalogJackInput4ms{{to_mm<72>(41.11), to_mm<72>(181.87), Center, "B2 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(15.87), to_mm<72>(217.87), Center, "B1 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(41.11), to_mm<72>(217.87), Center, "B2 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.87), to_mm<72>(279.07), Center, "C1 IN", ""}},
		AnalogJackInput4ms{{to_mm<72>(41.11), to_mm<72>(279.07), Center, "C2 IN", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.87), to_mm<72>(315.07), Center, "C3 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(41.11), to_mm<72>(315.07), Center, "C1 Out", ""}},
		RedGreenBlueLight{{to_mm<72>(28.49), to_mm<72>(61.27), Center, "A LED x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(28.49), to_mm<72>(158.47), Center, "B LED x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(28.49), to_mm<72>(255.67), Center, "C LED x23 GreenLight", ""}},
}};

    enum class Elem {
        A1_In,
        A1_Out,
        A2_Out,
        A3_Out,
        B1_In,
        B2_In,
        B1_Out,
        B2_Out,
        C1_In,
        C2_In,
        C3_In,
        C1_Out,
        A_Led_X23_GreenlightLight,
        B_Led_X23_GreenlightLight,
        C_Led_X23_GreenlightLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    
    
    enum {
        InputA1_In, 
        InputB1_In, 
        InputB2_In, 
        InputC1_In, 
        InputC2_In, 
        InputC3_In, 
        NumInJacks,
    };
    
    enum {
        OutputA1_Out, 
        OutputA2_Out, 
        OutputA3_Out, 
        OutputB1_Out, 
        OutputB2_Out, 
        OutputC1_Out, 
        NumOutJacks,
    };
    
    enum {
        LedA_Led_X23_Greenlight, 
        LedB_Led_X23_Greenlight, 
        LedC_Led_X23_Greenlight, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
