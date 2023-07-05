#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct CLKDInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"CLKD"};
    static constexpr std::string_view description{"Clock Divider"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/CLKD-artwork.svg"};

    static constexpr std::array<Element, 4> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.53), "Divide", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(214.97), "CV", ""},
		GateJackInput4ms{to_mm<72>(28.63), to_mm<72>(264.07), "Clk In", ""},
		GateJackOutput4ms{to_mm<72>(28.63), to_mm<72>(312.29), "Clk Out", ""},
}};

    enum class Elem {
        DivideKnob,
        CvIn,
        ClkIn,
        ClkOut,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobDivide = 0,
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
