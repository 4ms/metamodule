#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct FollowInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Follow"};
    static constexpr std::string_view description{"Follower"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Follow_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/Follow.png"};

    using enum Coords;

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(46.67), Center, "Rise", ""}},
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(94.35), Center, "Fall", ""}},
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(142.56), Center, "Thresh", ""}},
		AnalogJackInput4ms{{to_mm<72>(28.93), to_mm<72>(214.97), Center, "Input", ""}},
		AnalogJackOutput4ms{{to_mm<72>(28.93), to_mm<72>(264.07), Center, "Gate", ""}},
		AnalogJackOutput4ms{{to_mm<72>(28.93), to_mm<72>(312.29), Center, "Env", ""}},
}};

    enum class Elem {
        RiseKnob,
        FallKnob,
        ThreshKnob,
        InputIn,
        GateOut,
        EnvOut,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobRise = 0,
        KnobFall = 1,
        KnobThresh = 2,
        NumKnobs,
    };
    
    
    enum {
        InputInput = 0,
        NumInJacks,
    };
    
    enum {
        OutputGate = 0,
        OutputEnv = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
