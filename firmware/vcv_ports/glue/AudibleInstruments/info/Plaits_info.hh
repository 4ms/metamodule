#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
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

    static constexpr std::array<Element, 27> Elements{{
		OrangeButton{{to_mm<72>(73.35), to_mm<72>(48.44), Center, "Pitch Models", ""}},
		OrangeButton{{to_mm<72>(98.58), to_mm<72>(48.44), Center, "Percussive Models", ""}},
		DaviesLargeKnob{{to_mm<72>(34.73), to_mm<72>(82.74), Center, "Frequency x23 WhiteLargeKnob", ""}, 0.5f},
		DaviesLargeKnob{{to_mm<72>(137.28), to_mm<72>(82.74), Center, "Harmonics x23 WhiteLargeKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(31.16), to_mm<72>(160.13), Center, "Timbre x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(140.79), to_mm<72>(160.13), Center, "Morph x23 WhiteMediumKnob", ""}, 0.5f},
		Knob9mm{{to_mm<72>(31.14), to_mm<72>(228.45), Center, "Timbre Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(85.96), to_mm<72>(228.45), Center, "FM Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Knob9mm{{to_mm<72>(140.77), to_mm<72>(228.45), Center, "Morph Atten x23 WhiteSmallKnob", ""}, 0.0f},
		AnalogJackInput4ms{{to_mm<72>(21.1), to_mm<72>(273.52), Center, "Model CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(53.54), to_mm<72>(273.52), Center, "Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(85.99), to_mm<72>(273.52), Center, "FM CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(118.43), to_mm<72>(273.52), Center, "Morph CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(150.88), to_mm<72>(273.52), Center, "Harmo CV", ""}},
		GateJackOutput4ms{{to_mm<72>(21.1), to_mm<72>(314.91), Center, "Strum", ""}},
		AnalogJackInput4ms{{to_mm<72>(53.54), to_mm<72>(314.91), Center, "Level CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(85.99), to_mm<72>(314.91), Center, "V x2F Oct", ""}},
		AnalogJackOutput4ms{{to_mm<72>(118.43), to_mm<72>(314.91), Center, "Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(150.88), to_mm<72>(314.91), Center, "Aux", ""}},
		RedGreenBlueLight{{to_mm<72>(85.98), to_mm<72>(70.13), Center, " x31  LED x23 RedGreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(85.98), to_mm<72>(85.44), Center, " x32  LED x23 RedGreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(85.98), to_mm<72>(100.74), Center, " x33  LED x23 RedGreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(85.98), to_mm<72>(116.05), Center, " x34  LED x23 RedGreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(85.98), to_mm<72>(131.36), Center, " x35  LED x23 RedGreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(85.98), to_mm<72>(146.67), Center, " x36  LED x23 RedGreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(85.98), to_mm<72>(161.98), Center, " x37  LED x23 RedGreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(85.98), to_mm<72>(177.28), Center, " x38  LED x23 RedGreenLight", ""}},
}};

    enum class Elem {
        Pitch_ModelsButton,
        Percussive_ModelsButton,
        Frequency_X23_WhitelargeknobKnob,
        Harmonics_X23_WhitelargeknobKnob,
        Timbre_X23_WhitemediumknobKnob,
        Morph_X23_WhitemediumknobKnob,
        Timbre_Atten_X23_WhitesmallknobKnob,
        Fm_Atten_X23_WhitesmallknobKnob,
        Morph_Atten_X23_WhitesmallknobKnob,
        Model_CvIn,
        Timbre_CvIn,
        Fm_CvIn,
        Morph_CvIn,
        Harmo_CvIn,
        StrumOut,
        Level_CvIn,
        V_X2F_OctIn,
        Out,
        AuxOut,
        _X31__Led_X23_RedgreenlightLight,
        _X32__Led_X23_RedgreenlightLight,
        _X33__Led_X23_RedgreenlightLight,
        _X34__Led_X23_RedgreenlightLight,
        _X35__Led_X23_RedgreenlightLight,
        _X36__Led_X23_RedgreenlightLight,
        _X37__Led_X23_RedgreenlightLight,
        _X38__Led_X23_RedgreenlightLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobFrequency_X23_Whitelargeknob, 
        KnobHarmonics_X23_Whitelargeknob, 
        KnobTimbre_X23_Whitemediumknob, 
        KnobMorph_X23_Whitemediumknob, 
        KnobTimbre_Atten_X23_Whitesmallknob, 
        KnobFm_Atten_X23_Whitesmallknob, 
        KnobMorph_Atten_X23_Whitesmallknob, 
        NumKnobs,
    };
    
    enum {
        SwitchPitch_Models, 
        SwitchPercussive_Models, 
        NumSwitches,
    };
    
    enum {
        InputModel_Cv, 
        InputTimbre_Cv, 
        InputFm_Cv, 
        InputMorph_Cv, 
        InputHarmo_Cv, 
        InputLevel_Cv, 
        InputV_X2F_Oct, 
        NumInJacks,
    };
    
    enum {
        OutputStrum, 
        OutputOut, 
        OutputAux, 
        NumOutJacks,
    };
    
    enum {
        Led_X31__Led_X23_Redgreenlight, 
        Led_X32__Led_X23_Redgreenlight, 
        Led_X33__Led_X23_Redgreenlight, 
        Led_X34__Led_X23_Redgreenlight, 
        Led_X35__Led_X23_Redgreenlight, 
        Led_X36__Led_X23_Redgreenlight, 
        Led_X37__Led_X23_Redgreenlight, 
        Led_X38__Led_X23_Redgreenlight, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
