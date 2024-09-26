#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct PlaitsInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Plaits"};
    static constexpr std::string_view description{"Macro Oscillator 2"};
    static constexpr uint32_t width_hp = 34;
    static constexpr std::string_view svg_filename{"res/modules/Plaits_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Plaits.png"};

    using enum Coords;

    static constexpr std::array<Element, 29> Elements{{
		SmallButton{{to_mm<72>(73.35), to_mm<72>(48.44), Center, "Pitched Model", ""}},
		SmallButton{{to_mm<72>(98.58), to_mm<72>(48.44), Center, "Perc. Model", ""}},
		WhiteLargeKnob{{to_mm<72>(34.73), to_mm<72>(82.74), Center, "Frequency", ""}, 0.5f},
		WhiteLargeKnob{{to_mm<72>(137.28), to_mm<72>(82.74), Center, "Harmonics", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(31.16), to_mm<72>(160.13), Center, "Timbre", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(140.79), to_mm<72>(160.13), Center, "Morph", ""}, 0.5f},
		Trimpot{{to_mm<72>(31.14), to_mm<72>(228.45), Center, "Timbre Atten", ""}, 0.5f},
		Trimpot{{to_mm<72>(85.96), to_mm<72>(228.45), Center, "FM Atten", ""}, 0.5f},
		Trimpot{{to_mm<72>(140.77), to_mm<72>(228.45), Center, "Morph Atten", ""}, 0.5f},
		AnalogJackInput4ms{{to_mm<72>(21.1), to_mm<72>(273.52), Center, "Model In", ""}},
		AnalogJackInput4ms{{to_mm<72>(53.54), to_mm<72>(273.52), Center, "Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(85.99), to_mm<72>(273.52), Center, "FM CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(118.43), to_mm<72>(273.52), Center, "Morph CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(150.88), to_mm<72>(273.52), Center, "Harmonics CV", ""}},
		GateJackInput4ms{{to_mm<72>(21.1), to_mm<72>(314.91), Center, "Trigger", ""}},
		AnalogJackInput4ms{{to_mm<72>(53.54), to_mm<72>(314.91), Center, "Level CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(85.99), to_mm<72>(314.91), Center, "V/Oct", ""}},
		AnalogJackOutput4ms{{to_mm<72>(118.43), to_mm<72>(314.91), Center, "Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(150.88), to_mm<72>(314.91), Center, "Aux Out", ""}},
		GreenRedLight{{to_mm<72>(85.98), to_mm<72>(70.13), Center, "1 LED", ""}},
		GreenRedLight{{to_mm<72>(85.98), to_mm<72>(85.44), Center, "2 LED", ""}},
		GreenRedLight{{to_mm<72>(85.98), to_mm<72>(100.74), Center, "3 LED", ""}},
		GreenRedLight{{to_mm<72>(85.98), to_mm<72>(116.05), Center, "4 LED", ""}},
		GreenRedLight{{to_mm<72>(85.98), to_mm<72>(131.36), Center, "5 LED", ""}},
		GreenRedLight{{to_mm<72>(85.98), to_mm<72>(146.67), Center, "6 LED", ""}},
		GreenRedLight{{to_mm<72>(85.98), to_mm<72>(161.98), Center, "7 LED", ""}},
		GreenRedLight{{to_mm<72>(85.98), to_mm<72>(177.28), Center, "8 LED", ""}},
		AltParamContinuous{{to_mm<72>(137.27), to_mm<72>(25.275), Center, "LPG Color", ""}, 0.5f},
		AltParamContinuous{{to_mm<72>(34.73), to_mm<72>(25.275), Center, "LPG Decay", ""}, 0.5f},
}};

    enum class Elem {
        PitchedModelButton,
        Perc_ModelButton,
        FrequencyKnob,
        HarmonicsKnob,
        TimbreKnob,
        MorphKnob,
        TimbreAttenKnob,
        FmAttenKnob,
        MorphAttenKnob,
        ModelIn,
        TimbreCvIn,
        FmCvIn,
        MorphCvIn,
        HarmonicsCvIn,
        TriggerIn,
        LevelCvIn,
        V_OctIn,
        Out,
        AuxOut,
        _1LedLight,
        _2LedLight,
        _3LedLight,
        _4LedLight,
        _5LedLight,
        _6LedLight,
        _7LedLight,
        _8LedLight,
        LpgColorAltParam,
        LpgDecayAltParam,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobFrequency, 
        KnobHarmonics, 
        KnobTimbre, 
        KnobMorph, 
        KnobTimbre_Atten, 
        KnobFm_Atten, 
        KnobMorph_Atten, 
        NumKnobs,
    };
    
    enum {
        SwitchPitched_Model, 
        SwitchPerc__Model, 
        NumSwitches,
    };
    
    enum {
        InputModel_In, 
        InputTimbre_Cv, 
        InputFm_Cv, 
        InputMorph_Cv, 
        InputHarmonics_Cv, 
        InputTrigger, 
        InputLevel_Cv, 
        InputV_Oct, 
        NumInJacks,
    };
    
    enum {
        OutputOut, 
        OutputAux_Out, 
        NumOutJacks,
    };
    
    enum {
        Led_1_Led, 
        Led_2_Led, 
        Led_3_Led, 
        Led_4_Led, 
        Led_5_Led, 
        Led_6_Led, 
        Led_7_Led, 
        Led_8_Led, 
        NumDiscreteLeds,
    };
    
    enum {
        AltParamLpg_Color, 
        AltParamLpg_Decay, 
    };
};
} // namespace MetaModule
