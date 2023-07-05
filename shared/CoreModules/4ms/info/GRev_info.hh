#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct GRevInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"GRev"};
    static constexpr std::string_view description{"Gated Reverse"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/GRev-artwork.svg"};

    static constexpr std::array<Element, 4> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.53), "Buffer", "", 0, 0, 1, 0.0f},
		GateJackInput4ms{to_mm<72>(28.63), to_mm<72>(214.97), "Rev", ""},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(264.07), "Input", ""},
		AnalogJackOutput4ms{to_mm<72>(28.63), to_mm<72>(312.29), "Out", ""},
}};

    enum class Elem {
        BufferKnob,
        RevIn,
        InputIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobBuffer = 0,
        NumKnobs,
    };
    
    
    enum {
        InputRev = 0,
        InputInput = 1,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
