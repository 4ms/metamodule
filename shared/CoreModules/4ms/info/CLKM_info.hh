#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct CLKMInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"CLKM"};
    static constexpr std::string_view description{"Clock Multiplier"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/CLKM_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 4> Elements{{
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(46.53), Center, "Multiply", ""}},
		AnalogJackInput4ms{{to_mm<72>(28.63), to_mm<72>(214.97), Center, "CV", ""}},
		GateJackInput4ms{{to_mm<72>(28.63), to_mm<72>(264.07), Center, "Clk In", ""}},
		GateJackOutput4ms{{to_mm<72>(28.63), to_mm<72>(312.29), Center, "Clk Out", ""}},
}};

    enum class Elem {
        MultiplyKnob,
        CvIn,
        ClkIn,
        ClkOut,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobMultiply = 0,
        NumKnobs,
    };
    
    
    enum {
        InputCv = 0,
        InputClk_In = 1,
        NumInJacks,
    };
    
    enum {
        OutputClk_Out = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
