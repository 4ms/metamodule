#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct MarblesInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Marbles"};
    static constexpr std::string_view description{"Random Sampler"};
    static constexpr uint32_t width_hp = 19;
    static constexpr std::string_view svg_filename{"res/modules/Marbles_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Marbles.png"};

    using enum Coords;

    static constexpr std::array<Element, 43> Elements{{
		OrangeButton{{to_mm<72>(46.78), to_mm<72>(50.91), Center, "T Deja Vu", ""}},
		OrangeButton{{to_mm<72>(212.04), to_mm<72>(50.91), Center, "X Deja Vu", ""}},
		WhiteMediumKnob{{to_mm<72>(129.41), to_mm<72>(63.52), Center, "DejaVu", ""}, 0.5f},
		Toggle3pos{{to_mm<72>(19.57), to_mm<72>(96.045), Center, "t Mode Switch", ""}, {"1", "2", "3"}},
		WhiteLargeKnob{{to_mm<72>(83.35), to_mm<72>(100.37), Center, "Rate", ""}, 0.5f},
		WhiteLargeKnob{{to_mm<72>(175.48), to_mm<72>(100.37), Center, "Spread", ""}, 0.5f},
		Toggle3pos{{to_mm<72>(239.26), to_mm<72>(96.045), Center, "X Mode Switch", ""}, {"1", "2", "3"}},
		WhiteMediumKnob{{to_mm<72>(26.94), to_mm<72>(165.99), Center, "T Bias", ""}, 0.5f},
		Toggle3pos{{to_mm<72>(75.41), to_mm<72>(158.675), Center, "Clock Range Switch", ""}, {"d4", "x1", "x4"}},
		WhiteMediumKnob{{to_mm<72>(129.41), to_mm<72>(145.44), Center, "Length", ""}, 0.5f},
		Toggle3pos{{to_mm<72>(183.42), to_mm<72>(158.675), Center, "Output Range Switch", ""}, {"2", "5", "5"}},
		WhiteMediumKnob{{to_mm<72>(231.89), to_mm<72>(165.99), Center, "X Bias", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(89.3), to_mm<72>(209.36), Center, "Jitter", ""}, 0.5f},
		Toggle2posHoriz{{to_mm<72>(129.42), to_mm<72>(191.225), Center, "Mode Switch", ""}, {"Off", "On"}},
		WhiteMediumKnob{{to_mm<72>(169.52), to_mm<72>(209.36), Center, "Steps", ""}, 0.5f},
		AnalogJackInput4ms{{to_mm<72>(26.94), to_mm<72>(232.75), Center, "T Bias CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(231.89), to_mm<72>(232.75), Center, "X Bias CV", ""}},
		GateJackInput4ms{{to_mm<72>(26.94), to_mm<72>(274.14), Center, "T Clock", ""}},
		AnalogJackInput4ms{{to_mm<72>(61.1), to_mm<72>(274.14), Center, "Rate CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(95.26), to_mm<72>(274.14), Center, "Jitter CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(129.41), to_mm<72>(274.14), Center, "Deja Vu CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(163.57), to_mm<72>(274.14), Center, "Steps CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(197.73), to_mm<72>(274.14), Center, "Spread CV", ""}},
		GateJackInput4ms{{to_mm<72>(231.89), to_mm<72>(274.14), Center, "X Clock", ""}},
		GateJackOutput4ms{{to_mm<72>(26.94), to_mm<72>(315.52), Center, "t1", ""}},
		GateJackOutput4ms{{to_mm<72>(61.1), to_mm<72>(315.52), Center, "t2", ""}},
		GateJackOutput4ms{{to_mm<72>(95.26), to_mm<72>(315.52), Center, "t3", ""}},
		AnalogJackOutput4ms{{to_mm<72>(129.41), to_mm<72>(315.52), Center, "Y", ""}},
		AnalogJackOutput4ms{{to_mm<72>(163.57), to_mm<72>(315.52), Center, "X1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(197.73), to_mm<72>(315.52), Center, "X2", ""}},
		AnalogJackOutput4ms{{to_mm<72>(231.89), to_mm<72>(315.52), Center, "X3", ""}},
		RedGreenLight{{to_mm<72>(19.57), to_mm<72>(70.82), Center, "t Mode LED", ""}},
		RedGreenLight{{to_mm<72>(239.26), to_mm<72>(70.82), Center, "X Mode Light", ""}},
		RedGreenLight{{to_mm<72>(106.53), to_mm<72>(157.85), Center, "Clock Range Light", ""}},
		RedGreenLight{{to_mm<72>(152.52), to_mm<72>(158.43), Center, "Output Range Light", ""}},
		GreenLight{{to_mm<72>(129.41), to_mm<72>(216.45), Center, "External Light", ""}},
		GreenLight{{to_mm<72>(17.02), to_mm<72>(297.52), Center, "t1", ""}},
		GreenLight{{to_mm<72>(51.18), to_mm<72>(297.52), Center, "t2", ""}},
		GreenLight{{to_mm<72>(85.34), to_mm<72>(297.52), Center, "t3", ""}},
		GreenLight{{to_mm<72>(119.49), to_mm<72>(297.52), Center, "Y", ""}},
		GreenLight{{to_mm<72>(153.65), to_mm<72>(297.52), Center, "X1", ""}},
		GreenLight{{to_mm<72>(187.81), to_mm<72>(297.52), Center, "X2", ""}},
		GreenLight{{to_mm<72>(221.97), to_mm<72>(297.52), Center, "X3", ""}},
}};

    enum class Elem {
        TDejaVuButton,
        XDejaVuButton,
        DejavuKnob,
        TModeSwitch,
        RateKnob,
        SpreadKnob,
        XModeSwitch,
        TBiasKnob,
        ClockRangeSwitch,
        LengthKnob,
        OutputRangeSwitch,
        XBiasKnob,
        JitterKnob,
        ModeSwitch,
        StepsKnob,
        TBiasCvIn,
        XBiasCvIn,
        TClockIn,
        RateCvIn,
        JitterCvIn,
        DejaVuCvIn,
        StepsCvIn,
        SpreadCvIn,
        XClockIn,
        T1Out,
        T2Out,
        T3Out,
        YOut,
        X1Out,
        X2Out,
        X3Out,
        TModeLedLight,
        XModeLight,
        ClockRangeLight,
        OutputRangeLight,
        ExternalLight,
        T1Light,
        T2Light,
        T3Light,
        YLight,
        X1Light,
        X2Light,
        X3Light,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobDejavu, 
        KnobRate, 
        KnobSpread, 
        KnobT_Bias, 
        KnobLength, 
        KnobX_Bias, 
        KnobJitter, 
        KnobSteps, 
        NumKnobs,
    };
    
    enum {
        SwitchT_Deja_Vu, 
        SwitchX_Deja_Vu, 
        SwitchT_Mode_Switch, 
        SwitchX_Mode_Switch, 
        SwitchClock_Range_Switch, 
        SwitchOutput_Range_Switch, 
        SwitchMode_Switch, 
        NumSwitches,
    };
    
    enum {
        InputT_Bias_Cv, 
        InputX_Bias_Cv, 
        InputT_Clock, 
        InputRate_Cv, 
        InputJitter_Cv, 
        InputDeja_Vu_Cv, 
        InputSteps_Cv, 
        InputSpread_Cv, 
        InputX_Clock, 
        NumInJacks,
    };
    
    enum {
        OutputT1, 
        OutputT2, 
        OutputT3, 
        OutputY, 
        OutputX1, 
        OutputX2, 
        OutputX3, 
        NumOutJacks,
    };
    
    enum {
        LedT_Mode_Led, 
        LedX_Mode_Light, 
        LedClock_Range_Light, 
        LedOutput_Range_Light, 
        LedExternal_Light, 
        LedT1, 
        LedT2, 
        LedT3, 
        LedY, 
        LedX1, 
        LedX2, 
        LedX3, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
