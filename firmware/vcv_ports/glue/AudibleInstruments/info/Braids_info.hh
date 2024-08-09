#pragma once
#include "CoreModules/AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct BraidsInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Braids"};
    static constexpr std::string_view description{"Macro Oscillator"};
    static constexpr uint32_t width_hp = 16;
    static constexpr std::string_view svg_filename{"res/modules/Braids_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Braids.png"};

    using enum Coords;

    static constexpr std::array<Element, 13> Elements{{
		WhiteMediumKnob{{to_mm<72>(39.78), to_mm<72>(154.86), Center, "Fine", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(115.38), to_mm<72>(154.86), Center, "Coarse", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(190.98), to_mm<72>(154.86), Center, "FM", ""}, 0.5f},
		BlueMediumKnob{{to_mm<72>(39.78), to_mm<72>(230.46), Center, "Timbre", ""}, 0.5f},
		BlueMediumKnob{{to_mm<72>(115.38), to_mm<72>(230.46), Center, "Modulation", ""}, 0.5f},
		RedMediumKnob{{to_mm<72>(190.98), to_mm<72>(230.46), Center, "Color", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(190.98), to_mm<72>(77.46), Center, "Edit", ""}, 0.5f},
		GateJackInput4ms{{to_mm<72>(21.77), to_mm<72>(315.06), Center, "Trig", ""}},
		AnalogJackInput4ms{{to_mm<72>(57.78), to_mm<72>(315.06), Center, "V/Oct", ""}},
		AnalogJackInput4ms{{to_mm<72>(93.78), to_mm<72>(315.06), Center, "FM", ""}},
		AnalogJackInput4ms{{to_mm<72>(129.78), to_mm<72>(315.06), Center, "Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(165.78), to_mm<72>(315.06), Center, "Color CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(208.97), to_mm<72>(315.06), Center, "Out", ""}},
}};

    enum class Elem {
        FineKnob,
        CoarseKnob,
        FmKnob,
        TimbreKnob,
        ModulationKnob,
        ColorKnob,
        EditKnob,
        TrigIn,
        V_OctIn,
        FmIn,
        TimbreCvIn,
        ColorCvIn,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobFine, 
        KnobCoarse, 
        KnobFm, 
        KnobTimbre, 
        KnobModulation, 
        KnobColor, 
        KnobEdit, 
        NumKnobs,
    };
    
    
    enum {
        InputTrig, 
        InputV_Oct, 
        InputFm, 
        InputTimbre_Cv, 
        InputColor_Cv, 
        NumInJacks,
    };
    
    enum {
        OutputOut, 
        NumOutJacks,
    };
    
    
};
} // namespace MetaModule
