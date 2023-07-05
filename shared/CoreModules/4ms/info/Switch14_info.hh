#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct Switch14Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Switch14"};
    static constexpr std::string_view description{"1 to 4 Switch"};
    static constexpr uint32_t width_hp = 8;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Switch14-artwork.svg"};

    static constexpr std::array<Element, 8> Elements{{
		AnalogJackInput4ms{to_mm<72>(31.89), to_mm<72>(167.17), "In", ""},
		AnalogJackInput4ms{to_mm<72>(83.42), to_mm<72>(167.17), "Reset", ""},
		AnalogJackInput4ms{to_mm<72>(31.89), to_mm<72>(214.56), "Clock", ""},
		AnalogJackInput4ms{to_mm<72>(83.42), to_mm<72>(214.56), "CV", ""},
		AnalogJackOutput4ms{to_mm<72>(31.89), to_mm<72>(263.28), "Out 1", ""},
		AnalogJackOutput4ms{to_mm<72>(83.42), to_mm<72>(263.28), "Out 2", ""},
		AnalogJackOutput4ms{to_mm<72>(31.89), to_mm<72>(312.0), "Out 3", ""},
		AnalogJackOutput4ms{to_mm<72>(83.42), to_mm<72>(312.0), "Out 4", ""},
}};

    enum class Elem {
        In,
        ResetIn,
        ClockIn,
        CvIn,
        Out1Out,
        Out2Out,
        Out3Out,
        Out4Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    
    
    enum {
        InputIn = 0,
        InputReset = 1,
        InputClock = 2,
        InputCv = 3,
        NumInJacks,
    };
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
        OutputOut_3 = 2,
        OutputOut_4 = 3,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
