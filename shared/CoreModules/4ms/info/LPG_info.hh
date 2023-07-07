#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct LPGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"LPG"};
    static constexpr std::string_view description{"Low Pass Gate"};
    static constexpr uint32_t width_hp = 8;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/LPG-artwork.svg"};

    static constexpr std::array<Element, 7> Elements{{
		Davies1900hBlackKnob{to_mm<72>(57.94), to_mm<72>(57.97), "Level", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(31.96), to_mm<72>(119.21), "CV", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(83.49), to_mm<72>(119.21), "Decay", "", 0, 0, 1, 0.875f},
		AnalogJackInput4ms{to_mm<72>(32.13), to_mm<72>(272.09), "Input", ""},
		GateJackInput4ms{to_mm<72>(83.32), to_mm<72>(272.09), "Ping", ""},
		AnalogJackInput4ms{to_mm<72>(32.13), to_mm<72>(313.7), "CV Jack", ""},
		AnalogJackOutput4ms{to_mm<72>(83.32), to_mm<72>(313.7), "Out", ""},
}};

    enum class Elem {
        LevelKnob,
        CvKnob,
        DecayKnob,
        InputIn,
        PingIn,
        CvJackIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobLevel = 0,
        KnobCv = 1,
        KnobDecay = 2,
        NumKnobs,
    };
    
    
    enum {
        InputInput = 0,
        InputPing = 1,
        InputCv_Jack = 2,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
