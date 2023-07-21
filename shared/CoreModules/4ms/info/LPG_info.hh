#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct LPGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"LPG"};
    static constexpr std::string_view description{"Low Pass Gate"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/LPG_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 7> Elements{{
		Davies1900hBlackKnob{to_mm<72>(57.94), to_mm<72>(57.97), Center, "Level", ""},
		Davies1900hBlackKnob{to_mm<72>(31.96), to_mm<72>(119.21), Center, "CV", ""},
		Davies1900hBlackKnob{to_mm<72>(83.49), to_mm<72>(119.21), Center, "Decay", ""},
		AnalogJackInput4ms{to_mm<72>(32.13), to_mm<72>(272.09), Center, "Input", ""},
		GateJackInput4ms{to_mm<72>(83.32), to_mm<72>(272.09), Center, "Ping", ""},
		AnalogJackInput4ms{to_mm<72>(32.13), to_mm<72>(313.7), Center, "CV Jack", ""},
		AnalogJackOutput4ms{to_mm<72>(83.32), to_mm<72>(313.7), Center, "Out", ""},
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

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
