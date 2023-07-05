#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct FollowInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Follow"};
    static constexpr std::string_view description{"Follower"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Follow-artwork.svg"};

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.67), "Rise", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.35), "Fall", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(142.56), "Thresh", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(28.93), to_mm<72>(214.97), "Input", ""},
		AnalogJackOutput4ms{to_mm<72>(28.93), to_mm<72>(264.07), "Gate", ""},
		AnalogJackOutput4ms{to_mm<72>(28.93), to_mm<72>(312.29), "Env", ""},
}};

    enum class Elem {
        RiseKnob,
        FallKnob,
        ThreshKnob,
        InputIn,
        GateOut,
        EnvOut,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
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
