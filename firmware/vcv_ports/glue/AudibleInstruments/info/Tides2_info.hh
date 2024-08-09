#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct Tides2Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Tides2"};
    static constexpr std::string_view description{"Tidal Modulator 2"};
    static constexpr uint32_t width_hp = 14;
    static constexpr std::string_view svg_filename{"res/modules/Tides2_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Tides2.png"};

    using enum Coords;

    static constexpr std::array<Element, 31> Elements{{
		SmallButton{{to_mm<72>(21.35), to_mm<72>(45.94), Center, "Freq Range", ""}},
		SmallButton{{to_mm<72>(100.58), to_mm<72>(109.86), Center, "Ramp Mode", ""}},
		SmallButton{{to_mm<72>(179.81), to_mm<72>(45.94), Center, "Output Mode", ""}},
		WhiteLargeKnob{{to_mm<72>(46.58), to_mm<72>(94.97), Center, "Frequency", ""}, 0.5f},
		WhiteLargeKnob{{to_mm<72>(154.58), to_mm<72>(94.97), Center, "Shape", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(100.58), to_mm<72>(157.62), Center, "Smoothness", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(33.12), to_mm<72>(171.94), Center, "Slope", ""}, 0.5f},
		Trimpot{{to_mm<72>(26.6), to_mm<72>(228.63), Center, "Slope Atten", ""}, 0.5f},
		Trimpot{{to_mm<72>(63.59), to_mm<72>(228.63), Center, "Frequency Atten", ""}, 0.5f},
		Trimpot{{to_mm<72>(100.58), to_mm<72>(228.63), Center, "Smoothness Atten", ""}, 0.5f},
		Trimpot{{to_mm<72>(137.57), to_mm<72>(228.63), Center, "Shape Atten", ""}, 0.5f},
		Trimpot{{to_mm<72>(174.57), to_mm<72>(228.63), Center, "Shift Level Atten", ""}, 0.5f},
		AnalogJackInput4ms{{to_mm<72>(19.51), to_mm<72>(273.7), Center, "Slope CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(51.97), to_mm<72>(273.7), Center, "Frequency CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(84.42), to_mm<72>(273.7), Center, "V Oct", ""}},
		AnalogJackInput4ms{{to_mm<72>(116.88), to_mm<72>(273.7), Center, "Smoothness CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(149.34), to_mm<72>(273.7), Center, "Shape CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(181.79), to_mm<72>(273.7), Center, "Shift Level CV", ""}},
		GateJackInput4ms{{to_mm<72>(19.51), to_mm<72>(315.09), Center, "Trig", ""}},
		GateJackInput4ms{{to_mm<72>(51.97), to_mm<72>(315.09), Center, "Clock", ""}},
		AnalogJackOutput4ms{{to_mm<72>(84.42), to_mm<72>(315.09), Center, "Ch1 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(116.88), to_mm<72>(315.09), Center, "Ch2 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(149.34), to_mm<72>(315.09), Center, "Ch3 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(181.79), to_mm<72>(315.09), Center, "Ch4 Out", ""}},
		GreenRedLight{{to_mm<72>(64.37), to_mm<72>(25.67), Center, "Freq Range LED", ""}},
		GreenRedLight{{to_mm<72>(136.94), to_mm<72>(25.67), Center, "Output Mode LED", ""}},
		GreenRedLight{{to_mm<72>(100.58), to_mm<72>(86.57), Center, "Ramp Mode LED", ""}},
		GreenLight{{to_mm<72>(74.5), to_mm<72>(297.09), Center, "Ch1 LED", ""}},
		GreenLight{{to_mm<72>(106.96), to_mm<72>(297.09), Center, "Ch2 LED", ""}},
		GreenLight{{to_mm<72>(139.42), to_mm<72>(297.09), Center, "Ch3 LED", ""}},
		GreenLight{{to_mm<72>(171.87), to_mm<72>(297.09), Center, "Ch4 LED", ""}},
}};

    enum class Elem {
        FreqRangeButton,
        RampModeButton,
        OutputModeButton,
        FrequencyKnob,
        ShapeKnob,
        SmoothnessKnob,
        SlopeKnob,
        SlopeAttenKnob,
        FrequencyAttenKnob,
        SmoothnessAttenKnob,
        ShapeAttenKnob,
        ShiftLevelAttenKnob,
        SlopeCvIn,
        FrequencyCvIn,
        VOctIn,
        SmoothnessCvIn,
        ShapeCvIn,
        ShiftLevelCvIn,
        TrigIn,
        ClockIn,
        Ch1Out,
        Ch2Out,
        Ch3Out,
        Ch4Out,
        FreqRangeLedLight,
        OutputModeLedLight,
        RampModeLedLight,
        Ch1LedLight,
        Ch2LedLight,
        Ch3LedLight,
        Ch4LedLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobFrequency, 
        KnobShape, 
        KnobSmoothness, 
        KnobSlope, 
        KnobSlope_Atten, 
        KnobFrequency_Atten, 
        KnobSmoothness_Atten, 
        KnobShape_Atten, 
        KnobShift_Level_Atten, 
        NumKnobs,
    };
    
    enum {
        SwitchFreq_Range, 
        SwitchRamp_Mode, 
        SwitchOutput_Mode, 
        NumSwitches,
    };
    
    enum {
        InputSlope_Cv, 
        InputFrequency_Cv, 
        InputV_Oct, 
        InputSmoothness_Cv, 
        InputShape_Cv, 
        InputShift_Level_Cv, 
        InputTrig, 
        InputClock, 
        NumInJacks,
    };
    
    enum {
        OutputCh1_Out, 
        OutputCh2_Out, 
        OutputCh3_Out, 
        OutputCh4_Out, 
        NumOutJacks,
    };
    
    enum {
        LedFreq_Range_Led, 
        LedOutput_Mode_Led, 
        LedRamp_Mode_Led, 
        LedCh1_Led, 
        LedCh2_Led, 
        LedCh3_Led, 
        LedCh4_Led, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
