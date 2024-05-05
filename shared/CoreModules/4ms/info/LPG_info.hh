#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct LPGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"LPG"};
    static constexpr std::string_view description{"Low Pass Gate"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/LPG_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/LPG.png"};

    using enum Coords;

    static constexpr std::array<Element, 7> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(57.81), to_mm<72>(57.85), Center, "Level", ""}},
		Davies1900hBlackKnob{{to_mm<72>(31.83), to_mm<72>(119.09), Center, "CV", ""}},
		Davies1900hBlackKnob{{to_mm<72>(83.37), to_mm<72>(119.09), Center, "Decay", ""}},
		AnalogJackInput4ms{{to_mm<72>(32.0), to_mm<72>(271.97), Center, "Input", ""}},
		GateJackInput4ms{{to_mm<72>(83.2), to_mm<72>(271.97), Center, "Ping", ""}},
		AnalogJackInput4ms{{to_mm<72>(32.0), to_mm<72>(313.57), Center, "CV Jack", ""}},
		AnalogJackOutput4ms{{to_mm<72>(83.2), to_mm<72>(313.57), Center, "Out", ""}},
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
        KnobLevel, 
        KnobCv, 
        KnobDecay, 
        NumKnobs,
    };
    
    
    enum {
        InputInput, 
        InputPing, 
        InputCv_Jack, 
        NumInJacks,
    };
    
    enum {
        OutputOut, 
        NumOutJacks,
    };
    
    
};
} // namespace MetaModule
