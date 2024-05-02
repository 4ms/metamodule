#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct DetuneInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Detune"};
    static constexpr std::string_view description{"Detuner"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Detune_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/Detune.png"};

    using enum Coords;

    static constexpr std::array<Element, 8> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(31.96), to_mm<72>(57.97), Center, "W Speed", ""}},
		Davies1900hBlackKnob{{to_mm<72>(83.49), to_mm<72>(57.97), Center, "F Speed", ""}},
		Davies1900hBlackKnob{{to_mm<72>(31.96), to_mm<72>(119.21), Center, "W Depth", ""}},
		Davies1900hBlackKnob{{to_mm<72>(83.49), to_mm<72>(119.21), Center, "F Depth", ""}},
		AnalogJackInput4ms{{to_mm<72>(32.13), to_mm<72>(272.09), Center, "Input", ""}},
		AnalogJackInput4ms{{to_mm<72>(83.32), to_mm<72>(272.09), Center, "Detune", ""}},
		AnalogJackInput4ms{{to_mm<72>(32.13), to_mm<72>(313.7), Center, "Depth", ""}},
		AnalogJackOutput4ms{{to_mm<72>(83.32), to_mm<72>(313.7), Center, "Out", ""}},
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

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
