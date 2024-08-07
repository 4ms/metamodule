#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct RipplesInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Ripples"};
    static constexpr std::string_view description{"Filter"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Ripples_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Ripples.png"};

    using enum Coords;

    static constexpr std::array<Element, 12> Elements{{
		RedSmallKnob{{to_mm<72>(24.74), to_mm<72>(59.33), Center, "Resonance", ""}, 0.0f},
		WhiteLargeKnob{{to_mm<72>(57.15), to_mm<72>(120.53), Center, "Frequency", ""}, 0.5f},
		BlueMediumKnob{{to_mm<72>(89.54), to_mm<72>(181.73), Center, "FM", ""}, 0.875f},
		AnalogJackInput4ms{{to_mm<72>(22.91), to_mm<72>(246.5), Center, "Resonance CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(57.12), to_mm<72>(246.5), Center, "Frequency CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(91.34), to_mm<72>(246.5), Center, "FM", ""}},
		AnalogJackInput4ms{{to_mm<72>(22.91), to_mm<72>(280.72), Center, "In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(57.12), to_mm<72>(280.72), Center, "BP2", ""}},
		AnalogJackOutput4ms{{to_mm<72>(91.34), to_mm<72>(280.72), Center, "LP2", ""}},
		AnalogJackInput4ms{{to_mm<72>(22.91), to_mm<72>(314.93), Center, "Gain", ""}},
		AnalogJackOutput4ms{{to_mm<72>(57.12), to_mm<72>(314.93), Center, "LP4", ""}},
		AnalogJackOutput4ms{{to_mm<72>(91.34), to_mm<72>(314.93), Center, "LP4&gt;VCA", ""}},
}};

    enum class Elem {
        ResonanceKnob,
        FrequencyKnob,
        FmKnob,
        ResonanceCvIn,
        FrequencyCvIn,
        FmIn,
        In,
        Bp2Out,
        Lp2Out,
        GainIn,
        Lp4Out,
        Lp4_Gt_VcaOut,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobResonance, 
        KnobFrequency, 
        KnobFm, 
        NumKnobs,
    };
    
    
    enum {
        InputResonance_Cv, 
        InputFrequency_Cv, 
        InputFm, 
        InputIn, 
        InputGain, 
        NumInJacks,
    };
    
    enum {
        OutputBp2, 
        OutputLp2, 
        OutputLp4, 
        OutputLp4_Gt_Vca, 
        NumOutJacks,
    };
    
    
};
} // namespace MetaModule
