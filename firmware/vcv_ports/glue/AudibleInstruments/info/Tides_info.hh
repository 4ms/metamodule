#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct TidesInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Tides"};
    static constexpr std::string_view description{"Tidal Modulator"};
    static constexpr uint32_t width_hp = 14;
    static constexpr std::string_view svg_filename{"res/modules/Tides_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Tides.png"};

    using enum Coords;

    static constexpr std::array<Element, 23> Elements{{
		Toggle3posHoriz{{to_mm<72>(32.24), to_mm<72>(62.935), Center, "Output Mode", ""}, {"1", "2", "3"}},
		Toggle3posHoriz{{to_mm<72>(32.24), to_mm<72>(102.555), Center, "Frequency Range", ""}, {"L", "M", "H"}},
		BlueLargeKnob{{to_mm<72>(100.67), to_mm<72>(82.74), Center, "Frequency", ""}, 0.5f},
		BlueMediumKnob{{to_mm<72>(169.1), to_mm<72>(82.74), Center, "FM", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(32.24), to_mm<72>(167.33), Center, "Shape", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(100.67), to_mm<72>(167.33), Center, "Slope", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(169.1), to_mm<72>(167.33), Center, "Smoothness", ""}, 0.5f},
		AnalogJackInput4ms{{to_mm<72>(32.24), to_mm<72>(221.33), Center, "Shape CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(100.67), to_mm<72>(221.33), Center, "Slope CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(169.09), to_mm<72>(221.33), Center, "Smoothness CV", ""}},
		GateJackInput4ms{{to_mm<72>(32.24), to_mm<72>(273.54), Center, "Trig", ""}},
		GateJackInput4ms{{to_mm<72>(66.45), to_mm<72>(273.54), Center, "Freeze", ""}},
		AnalogJackInput4ms{{to_mm<72>(100.67), to_mm<72>(273.54), Center, "V/Oct", ""}},
		AnalogJackInput4ms{{to_mm<72>(134.88), to_mm<72>(273.54), Center, "FM In", ""}},
		AnalogJackInput4ms{{to_mm<72>(169.09), to_mm<72>(273.54), Center, "Level", ""}},
		GateJackInput4ms{{to_mm<72>(32.24), to_mm<72>(314.93), Center, "Clock", ""}},
		GateJackOutput4ms{{to_mm<72>(66.45), to_mm<72>(314.93), Center, "High Tide Out", ""}},
		GateJackOutput4ms{{to_mm<72>(100.67), to_mm<72>(314.93), Center, "Low Tide Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(134.88), to_mm<72>(314.93), Center, "Unipolar", ""}},
		AnalogJackOutput4ms{{to_mm<72>(169.09), to_mm<72>(314.93), Center, "Bipolar", ""}},
		GreenRedLight{{to_mm<72>(59.25), to_mm<72>(62.93), Center, "Output Mode Light", ""}},
		GreenRedLight{{to_mm<72>(59.25), to_mm<72>(82.74), Center, "Phase Light", ""}},
		GreenRedLight{{to_mm<72>(59.25), to_mm<72>(102.56), Center, "Freq Range Light", ""}},
}};

    enum class Elem {
        OutputModeSwitch,
        FrequencyRangeSwitch,
        FrequencyKnob,
        FmKnob,
        ShapeKnob,
        SlopeKnob,
        SmoothnessKnob,
        ShapeCvIn,
        SlopeCvIn,
        SmoothnessCvIn,
        TrigIn,
        FreezeIn,
        V_OctIn,
        FmIn,
        LevelIn,
        ClockIn,
        HighTideOut,
        LowTideOut,
        UnipolarOut,
        BipolarOut,
        OutputModeLight,
        PhaseLight,
        FreqRangeLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobFrequency, 
        KnobFm, 
        KnobShape, 
        KnobSlope, 
        KnobSmoothness, 
        NumKnobs,
    };
    
    enum {
        SwitchOutput_Mode, 
        SwitchFrequency_Range, 
        NumSwitches,
    };
    
    enum {
        InputShape_Cv, 
        InputSlope_Cv, 
        InputSmoothness_Cv, 
        InputTrig, 
        InputFreeze, 
        InputV_Oct, 
        InputFm_In, 
        InputLevel, 
        InputClock, 
        NumInJacks,
    };
    
    enum {
        OutputHigh_Tide_Out, 
        OutputLow_Tide_Out, 
        OutputUnipolar, 
        OutputBipolar, 
        NumOutJacks,
    };
    
    enum {
        LedOutput_Mode_Light, 
        LedPhase_Light, 
        LedFreq_Range_Light, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
