#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct Seq4Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Seq4"};
    static constexpr std::string_view description{"4 Step Sequencer"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Seq4-artwork.svg"};

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.53), "1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.22), "2", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(142.91), "3", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(191.1), "4", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(29.28), to_mm<72>(263.82), "Clock", ""},
		AnalogJackOutput4ms{to_mm<72>(29.28), to_mm<72>(312.04), "Out", ""},
}};

    enum class Elem {
        _1Knob,
        _2Knob,
        _3Knob,
        _4Knob,
        ClockIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        Knob_1 = 0,
        Knob_2 = 1,
        Knob_3 = 2,
        Knob_4 = 3,
        NumKnobs,
    };
    
    
    enum {
        InputClock = 0,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
