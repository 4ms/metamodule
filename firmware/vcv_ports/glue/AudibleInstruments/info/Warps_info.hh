#pragma once
#include "CoreModules/AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct WarpsInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Warps"};
    static constexpr std::string_view description{"Meta Modulator"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/Warps_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Warps.png"};

    using enum Coords;

    static constexpr std::array<Element, 15> Elements{{
		Rogan6PSWhite{{to_mm<72>(71.71), to_mm<72>(94.73), Center, "Algorithm", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(109.63), to_mm<72>(185.46), Center, "Timbre", ""}, 0.421875f},
		MomentaryButton{{to_mm<72>(23.15), to_mm<72>(182.05), Center, "Int. Osc Mode", ""}},
		Knob9mm{{to_mm<72>(23.09), to_mm<72>(213.52), Center, "Osc Amp/Freq", ""}, 0.0f},
		Knob9mm{{to_mm<72>(59.95), to_mm<72>(213.52), Center, "Mod Amp", ""}, 0.0f},
		AnalogJackInput4ms{{to_mm<72>(20.3), to_mm<72>(273.63), Center, "Level 1 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(54.57), to_mm<72>(273.63), Center, "Level 2 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(88.9), to_mm<72>(273.63), Center, "Algorithm CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(123.23), to_mm<72>(273.63), Center, "Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.3), to_mm<72>(315.03), Center, "Carrier In", ""}},
		AnalogJackInput4ms{{to_mm<72>(54.57), to_mm<72>(315.03), Center, "Mod In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(88.9), to_mm<72>(315.03), Center, "Mod Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(123.23), to_mm<72>(315.03), Center, "Aux Out", ""}},
		Rogan6PSLight{{to_mm<72>(71.71), to_mm<72>(94.73), Center, "Algorithm Light", ""}},
		RedGreenBlueLight{{to_mm<72>(23.09), to_mm<72>(163.91), Center, "Carrier LightGreenRedLight", ""}},
}};

    enum class Elem {
        AlgorithmKnob,
        TimbreKnob,
        Int_OscModeButton,
        OscAmp_FreqKnob,
        ModAmpKnob,
        Level1In,
        Level2In,
        AlgorithmCvIn,
        TimbreCvIn,
        CarrierIn,
        ModIn,
        ModOut,
        AuxOut,
        AlgorithmLight,
        CarrierLightgreenredlightLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobAlgorithm, 
        KnobTimbre, 
        KnobOsc_Amp_Freq, 
        KnobMod_Amp, 
        NumKnobs,
    };
    
    enum {
        SwitchInt__Osc_Mode, 
        NumSwitches,
    };
    
    enum {
        InputLevel_1_In, 
        InputLevel_2_In, 
        InputAlgorithm_Cv, 
        InputTimbre_Cv, 
        InputCarrier_In, 
        InputMod_In, 
        NumInJacks,
    };
    
    enum {
        OutputMod_Out, 
        OutputAux_Out, 
        NumOutJacks,
    };
    
    enum {
        LedAlgorithm_Light, 
        LedCarrier_Lightgreenredlight, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
