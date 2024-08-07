#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
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
		Davies1900hBlackKnob{{to_mm<72>(190.98), to_mm<72>(77.46), Center, "Edit x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(39.78), to_mm<72>(154.86), Center, "Fine x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(115.38), to_mm<72>(154.86), Center, "Coarse x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(190.98), to_mm<72>(154.86), Center, "FM x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(39.78), to_mm<72>(230.46), Center, "Timbre x23 BlueMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(115.38), to_mm<72>(230.46), Center, "Modulation x23 BlueMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(190.98), to_mm<72>(230.46), Center, "Color x23 RedMediumKnob", ""}, 0.5f},
		GateJackInput4ms{{to_mm<72>(21.77), to_mm<72>(315.06), Center, "Trig", ""}},
		AnalogJackInput4ms{{to_mm<72>(57.78), to_mm<72>(315.06), Center, "V x2F Oct", ""}},
		AnalogJackInput4ms{{to_mm<72>(93.78), to_mm<72>(315.06), Center, "FM", ""}},
		AnalogJackInput4ms{{to_mm<72>(129.78), to_mm<72>(315.06), Center, "Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(165.78), to_mm<72>(315.06), Center, "Color CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(208.97), to_mm<72>(315.06), Center, "Out", ""}},
}};

    enum class Elem {
        Edit_X23_WhitemediumknobKnob,
        Fine_X23_WhitemediumknobKnob,
        Coarse_X23_WhitemediumknobKnob,
        Fm_X23_WhitemediumknobKnob,
        Timbre_X23_BluemediumknobKnob,
        Modulation_X23_BluemediumknobKnob,
        Color_X23_RedmediumknobKnob,
        TrigIn,
        V_X2F_OctIn,
        FmIn,
        Timbre_CvIn,
        Color_CvIn,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobEdit_X23_Whitemediumknob, 
        KnobFine_X23_Whitemediumknob, 
        KnobCoarse_X23_Whitemediumknob, 
        KnobFm_X23_Whitemediumknob, 
        KnobTimbre_X23_Bluemediumknob, 
        KnobModulation_X23_Bluemediumknob, 
        KnobColor_X23_Redmediumknob, 
        NumKnobs,
    };
    
    
    enum {
        InputTrig, 
        InputV_X2F_Oct, 
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
