#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct KPLSInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"KPLS"};
    static constexpr std::string_view description{"Karplus–Strong Voice"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/KPLS-artwork.svg"};

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(47.15), "Pitch", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.83), "Decay", "", 0, 0, 1, 0.25f},
		Knob9mm{to_mm<72>(29.1), to_mm<72>(143.04), "Spread", "", 0, 0, 1, 0.5f},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(215.22), "V/Oct", ""},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(264.32), "Trig", ""},
		AnalogJackOutput4ms{to_mm<72>(28.63), to_mm<72>(312.54), "Out", ""},
}};

    enum class Elem {
        PitchKnob,
        DecayKnob,
        SpreadKnob,
        V_OctIn,
        TrigIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobPitch = 0,
        KnobDecay = 1,
        KnobSpread = 2,
        NumKnobs,
    };
    
    
    enum {
        InputV_Oct = 0,
        InputTrig = 1,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
