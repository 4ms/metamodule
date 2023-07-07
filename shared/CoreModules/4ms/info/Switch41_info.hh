#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct Switch41Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Switch41"};
    static constexpr std::string_view description{"4 to 1 Switch"};
    static constexpr uint32_t width_hp = 8;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Switch41-artwork.svg"};

    static constexpr std::array<Element, 8> Elements{{
		AnalogJackInput4ms{to_mm<72>(31.89), to_mm<72>(167.17), "In 1", ""},
		AnalogJackInput4ms{to_mm<72>(83.42), to_mm<72>(167.17), "In 2", ""},
		AnalogJackInput4ms{to_mm<72>(31.89), to_mm<72>(214.56), "In 3", ""},
		AnalogJackInput4ms{to_mm<72>(83.42), to_mm<72>(214.56), "In 4", ""},
		AnalogJackInput4ms{to_mm<72>(31.89), to_mm<72>(263.28), "Clock", ""},
		AnalogJackInput4ms{to_mm<72>(83.42), to_mm<72>(263.28), "CV", ""},
		AnalogJackInput4ms{to_mm<72>(31.89), to_mm<72>(312.0), "Reset", ""},
		AnalogJackOutput4ms{to_mm<72>(83.42), to_mm<72>(312.0), "Out", ""},
}};

    enum class Elem {
        In1In,
        In2In,
        In3In,
        In4In,
        ClockIn,
        CvIn,
        ResetIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
        InputIn_3 = 2,
        InputIn_4 = 3,
        InputClock = 4,
        InputCv = 5,
        InputReset = 6,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
