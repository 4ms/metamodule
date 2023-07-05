#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct MultiLFOInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"MultiLFO"};
    static constexpr std::string_view description{"Multi LFO"};
    static constexpr uint32_t width_hp = 8;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/MultiLFO-artwork.svg"};

    static constexpr std::array<Element, 11> Elements{{
		DaviesLargeKnob{to_mm<72>(57.67), to_mm<72>(55.73), "Rate", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(31.96), to_mm<72>(119.41), "Phase", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(83.49), to_mm<72>(119.75), "PW", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(32.1), to_mm<72>(167.36), "Reset", ""},
		AnalogJackInput4ms{to_mm<72>(83.63), to_mm<72>(167.36), "PW CV", ""},
		AnalogJackInput4ms{to_mm<72>(32.1), to_mm<72>(214.57), "Rate CV", ""},
		AnalogJackInput4ms{to_mm<72>(83.63), to_mm<72>(214.57), "Phase CV", ""},
		AnalogJackOutput4ms{to_mm<72>(32.1), to_mm<72>(263.64), "Inv Saw", ""},
		AnalogJackOutput4ms{to_mm<72>(83.63), to_mm<72>(263.67), "Pulse", ""},
		AnalogJackOutput4ms{to_mm<72>(32.1), to_mm<72>(311.23), "Saw", ""},
		AnalogJackOutput4ms{to_mm<72>(83.63), to_mm<72>(311.26), "Sine", ""},
}};

    enum class Elem {
        RateKnob,
        PhaseKnob,
        PwKnob,
        ResetIn,
        PwCvIn,
        RateCvIn,
        PhaseCvIn,
        InvSawOut,
        PulseOut,
        SawOut,
        SineOut,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobRate = 0,
        KnobPhase = 1,
        KnobPw = 2,
        NumKnobs,
    };
    
    
    enum {
        InputReset = 0,
        InputPw_Cv = 1,
        InputRate_Cv = 2,
        InputPhase_Cv = 3,
        NumInJacks,
    };
    
    enum {
        OutputInv_Saw = 0,
        OutputPulse = 1,
        OutputSaw = 2,
        OutputSine = 3,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
