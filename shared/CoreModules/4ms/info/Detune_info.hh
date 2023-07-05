#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct DetuneInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Detune"};
    static constexpr std::string_view description{"Detuner"};
    static constexpr uint32_t width_hp = 8;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Detune-artwork.svg"};

    static constexpr std::array<Element, 8> Elements{{
		Davies1900hBlackKnob{to_mm<72>(31.96), to_mm<72>(57.97), "W Speed", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(83.49), to_mm<72>(57.97), "F Speed", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(31.96), to_mm<72>(119.21), "W Depth", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(83.49), to_mm<72>(119.21), "F Depth", "", 0, 0, 1, 0.5f},
		AnalogJackInput4ms{to_mm<72>(32.13), to_mm<72>(272.09), "Input", ""},
		AnalogJackInput4ms{to_mm<72>(83.32), to_mm<72>(272.09), "Detune", ""},
		AnalogJackInput4ms{to_mm<72>(32.13), to_mm<72>(313.7), "Depth", ""},
		AnalogJackOutput4ms{to_mm<72>(83.32), to_mm<72>(313.7), "Out", ""},
}};

    enum class Elem {
        WSpeedKnob,
        FSpeedKnob,
        WDepthKnob,
        FDepthKnob,
        InputIn,
        DetuneIn,
        DepthIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobW_Speed = 0,
        KnobF_Speed = 1,
        KnobW_Depth = 2,
        KnobF_Depth = 3,
        NumKnobs,
    };
    
    
    enum {
        InputInput = 0,
        InputDetune = 1,
        InputDepth = 2,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
