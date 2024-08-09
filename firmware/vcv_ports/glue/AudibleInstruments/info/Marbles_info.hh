#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
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
		WhiteMomentary7mm{{to_mm<72>(46.78), to_mm<72>(50.91), Center, "T Deja Vu", ""}},
		WhiteMomentary7mm{{to_mm<72>(212.04), to_mm<72>(50.91), Center, "X Deja Vu", ""}},
		WhiteMediumKnob{{to_mm<72>(129.41), to_mm<72>(63.52), Center, "DejaVu", ""}, 0.5f},
		WhiteLargeKnob{{to_mm<72>(83.35), to_mm<72>(100.37), Center, "Clock Rate", ""}, 0.5f},
		WhiteLargeKnob{{to_mm<72>(175.48), to_mm<72>(100.37), Center, "Spread", ""}, 0.5f},
		Toggle3pos{{to_mm<72>(19.57), to_mm<72>(96.045), Center, "T Mode Switch", ""}, {"1", "2", "3"}},
		Toggle3pos{{to_mm<72>(239.26), to_mm<72>(96.045), Center, "X Mode Switch", ""}, {"1", "2", "3"}},
		WhiteMediumKnob{{to_mm<72>(129.41), to_mm<72>(145.44), Center, "Length", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(26.94), to_mm<72>(165.99), Center, "T Bias", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(231.89), to_mm<72>(165.99), Center, "X Bias", ""}, 0.5f},
		Toggle3pos{{to_mm<72>(75.41), to_mm<72>(158.675), Center, "Clock Range Switch", ""}, {"x4", "x1", "/4"}},
		Toggle3pos{{to_mm<72>(183.42), to_mm<72>(158.675), Center, "Output Range Switch", ""}, {"+/-5V", "+5V", "+2V"}},
		SmallButton{{to_mm<72>(129.41), to_mm<72>(191.22), Center, "External", ""}},
		WhiteMediumKnob{{to_mm<72>(89.3), to_mm<72>(209.36), Center, "Jitter", ""}, 0.5f},
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
		GateJackOutput4ms{{to_mm<72>(26.94), to_mm<72>(315.52), Center, "T1 Out", ""}},
		GateJackOutput4ms{{to_mm<72>(61.1), to_mm<72>(315.52), Center, "T2 Out", ""}},
		GateJackOutput4ms{{to_mm<72>(95.26), to_mm<72>(315.52), Center, "T3 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(129.41), to_mm<72>(315.52), Center, "Y Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(163.57), to_mm<72>(315.52), Center, "X1 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(197.73), to_mm<72>(315.52), Center, "X2 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(231.89), to_mm<72>(315.52), Center, "X3 Out", ""}},
		GreenRedLight{{to_mm<72>(19.57), to_mm<72>(70.82), Center, "T Mode LED", ""}},
		GreenRedLight{{to_mm<72>(239.26), to_mm<72>(70.82), Center, "X Mode Light", ""}},
		GreenRedLight{{to_mm<72>(106.53), to_mm<72>(157.85), Center, "Clock Range Light", ""}},
		GreenRedLight{{to_mm<72>(152.52), to_mm<72>(158.43), Center, "Output Range Light", ""}},
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
        ClockRateKnob,
        SpreadKnob,
        TModeSwitch,
        XModeSwitch,
        LengthKnob,
        TBiasKnob,
        XBiasKnob,
        ClockRangeSwitch,
        OutputRangeSwitch,
        ExternalButton,
        JitterKnob,
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
        KnobClock_Rate, 
        KnobSpread, 
        KnobLength, 
        KnobT_Bias, 
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
        SwitchExternal, 
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
        OutputT1_Out, 
        OutputT2_Out, 
        OutputT3_Out, 
        OutputY_Out, 
        OutputX1_Out, 
        OutputX2_Out, 
        OutputX3_Out, 
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
