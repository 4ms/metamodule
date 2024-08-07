#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
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
		Toggle3posHoriz{{to_mm<72>(32.24), to_mm<72>(62.935), Center, "Output Mode Switch", ""}, {"1", "2", "3"}},
		BlueLargeKnob{{to_mm<72>(100.67), to_mm<72>(82.74), Center, "Frequency", ""}, 0.5f},
		BlueMediumKnob{{to_mm<72>(169.1), to_mm<72>(82.74), Center, "FM", ""}, 0.5f},
		Toggle3posHoriz{{to_mm<72>(32.24), to_mm<72>(102.555), Center, "Frequency Range Switch", ""}, {"L", "M", "H"}},
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
		GateJackOutput4ms{{to_mm<72>(66.45), to_mm<72>(314.93), Center, "High", ""}},
		GateJackOutput4ms{{to_mm<72>(100.67), to_mm<72>(314.93), Center, "Low", ""}},
		AnalogJackOutput4ms{{to_mm<72>(134.88), to_mm<72>(314.93), Center, "Uni", ""}},
		AnalogJackOutput4ms{{to_mm<72>(169.09), to_mm<72>(314.93), Center, "Bi", ""}},
		RedGreenLight{{to_mm<72>(59.25), to_mm<72>(62.93), Center, "Output Mode Light", ""}},
		RedGreenLight{{to_mm<72>(59.25), to_mm<72>(82.74), Center, "Freq Light", ""}},
		RedGreenLight{{to_mm<72>(59.25), to_mm<72>(102.56), Center, "Freq Range Light", ""}},
}};

    enum class Elem {
        OutputModeSwitch,
        FrequencyKnob,
        FmKnob,
        FrequencyRangeSwitch,
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
        HighOut,
        LowOut,
        UniOut,
        BiOut,
        OutputModeLight,
        FreqLight,
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
        SwitchOutput_Mode_Switch, 
        SwitchFrequency_Range_Switch, 
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
        OutputHigh, 
        OutputLow, 
        OutputUni, 
        OutputBi, 
        NumOutJacks,
    };
    
    enum {
        LedOutput_Mode_Light, 
        LedFreq_Light, 
        LedFreq_Range_Light, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
