#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct InfOscInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"InfOsc"};
    static constexpr std::string_view description{"Infinite Oscillator"};
    static constexpr uint32_t width_hp = 15;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/InfOsc-artwork.svg"};

    static constexpr std::array<Element, 20> Elements{{
		Davies1900hBlackKnob{to_mm<72>(43.62), to_mm<72>(46.55), "Track", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(108.12), to_mm<72>(46.55), "Abs", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(172.62), to_mm<72>(46.55), "Range", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(43.62), to_mm<72>(105.5), "FM", "", 0, 0, 1, 0.0f},
		DaviesLargeKnob{to_mm<72>(108.13), to_mm<72>(117.06), "Pitch", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(172.62), to_mm<72>(105.5), "Phase", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(43.3), to_mm<72>(164.67), "Modshape", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(172.52), to_mm<72>(164.62), "Wave", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(35.96), to_mm<72>(214.54), "PM CV", ""},
		AnalogJackInput4ms{to_mm<72>(83.96), to_mm<72>(214.54), "Scan CV", ""},
		AnalogJackInput4ms{to_mm<72>(131.96), to_mm<72>(214.54), "Add CV", ""},
		AnalogJackInput4ms{to_mm<72>(179.96), to_mm<72>(214.54), "Reset CV", ""},
		AnalogJackInput4ms{to_mm<72>(35.96), to_mm<72>(263.64), "Mod CV", ""},
		AnalogJackInput4ms{to_mm<72>(83.96), to_mm<72>(263.64), "Abs CV", ""},
		AnalogJackInput4ms{to_mm<72>(131.96), to_mm<72>(263.64), "Lin CV", ""},
		AnalogJackInput4ms{to_mm<72>(179.96), to_mm<72>(263.64), "Phase CV", ""},
		AnalogJackInput4ms{to_mm<72>(35.96), to_mm<72>(311.23), "Pitch CV", ""},
		AnalogJackInput4ms{to_mm<72>(83.96), to_mm<72>(311.23), "Range CV", ""},
		AnalogJackInput4ms{to_mm<72>(131.96), to_mm<72>(311.23), "FM CV", ""},
		AnalogJackOutput4ms{to_mm<72>(179.96), to_mm<72>(311.23), "Out", ""},
}};

    enum class Elem {
        TrackKnob,
        AbsKnob,
        RangeKnob,
        FmKnob,
        PitchKnob,
        PhaseKnob,
        ModshapeKnob,
        WaveKnob,
        PmCvIn,
        ScanCvIn,
        AddCvIn,
        ResetCvIn,
        ModCvIn,
        AbsCvIn,
        LinCvIn,
        PhaseCvIn,
        PitchCvIn,
        RangeCvIn,
        FmCvIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobTrack = 0,
        KnobAbs = 1,
        KnobRange = 2,
        KnobFm = 3,
        KnobPitch = 4,
        KnobPhase = 5,
        KnobModshape = 6,
        KnobWave = 7,
        NumKnobs,
    };
    
    
    enum {
        InputPm_Cv = 0,
        InputScan_Cv = 1,
        InputAdd_Cv = 2,
        InputReset_Cv = 3,
        InputMod_Cv = 4,
        InputAbs_Cv = 5,
        InputLin_Cv = 6,
        InputPhase_Cv = 7,
        InputPitch_Cv = 8,
        InputRange_Cv = 9,
        InputFm_Cv = 10,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
