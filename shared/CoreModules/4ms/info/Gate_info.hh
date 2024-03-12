#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct GateInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Gate"};
    static constexpr std::string_view description{"Gate Delay"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Gate_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/Gate.png"};

    using enum Coords;

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(46.52), Center, "Length", ""}},
		Knob9mm{{to_mm<72>(28.92), to_mm<72>(94.2), Center, "Delay", ""}},
		AnalogJackInput4ms{{to_mm<72>(28.92), to_mm<72>(168.85), Center, "Length CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(28.92), to_mm<72>(214.97), Center, "Delay CV", ""}},
		GateJackInput4ms{{to_mm<72>(28.92), to_mm<72>(264.07), Center, "Input", ""}},
		AnalogJackOutput4ms{{to_mm<72>(28.92), to_mm<72>(312.29), Center, "Out", ""}},
}};

    enum class Elem {
        LengthKnob,
        DelayKnob,
        LengthCvIn,
        DelayCvIn,
        InputIn,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobLength = 0,
        KnobDelay = 1,
        NumKnobs,
    };
    
    
    enum {
        InputLength_Cv = 0,
        InputDelay_Cv = 1,
        InputInput = 2,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
