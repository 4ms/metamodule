#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct LinksInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Links"};
    static constexpr std::string_view description{"M ultiples"};
    static constexpr uint32_t width_hp = 284;
    static constexpr std::string_view svg_filename{"res/modules/Links_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Links.png"};

    using enum Coords;

    static constexpr std::array<Element, 15> Elements{{
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(84.52), Center, "A1 In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(84.52), Center, "A1 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(15.74), to_mm<72>(120.52), Center, "A2 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(120.52), Center, "A3 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(181.72), Center, "B1 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(40.98), to_mm<72>(181.72), Center, "B2 In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(15.74), to_mm<72>(217.72), Center, "B1 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(217.72), Center, "B2 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(278.91), Center, "C1 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(40.98), to_mm<72>(278.91), Center, "C2 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(15.74), to_mm<72>(314.91), Center, "C3 In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(40.98), to_mm<72>(314.91), Center, "C1 Out", ""}},
		GreenRedLight{{to_mm<72>(28.36), to_mm<72>(61.13), Center, "A Light", ""}},
		GreenRedLight{{to_mm<72>(28.36), to_mm<72>(158.32), Center, "B Light", ""}},
		GreenRedLight{{to_mm<72>(28.36), to_mm<72>(255.51), Center, "C Light", ""}},
}};

    enum class Elem {
        A1In,
        A1Out,
        A2Out,
        A3Out,
        B1In,
        B2In,
        B1Out,
        B2Out,
        C1In,
        C2In,
        C3In,
        C1Out,
        ALight,
        BLight,
        CLight,
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
        LedA_Light, 
        LedB_Light, 
        LedC_Light, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
