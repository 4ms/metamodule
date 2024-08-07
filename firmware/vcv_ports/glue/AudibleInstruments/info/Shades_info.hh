#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ShadesInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Shades"};
    static constexpr std::string_view description{"Mixer"};
    static constexpr uint32_t width_hp = 6;
    static constexpr std::string_view svg_filename{"res/modules/Shades_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Shades.png"};

    using enum Coords;

    static constexpr std::array<Element, 15> Elements{{
		Toggle2pos{{to_mm<72>(16.27), to_mm<72>(59.415), Center, "Ch1 Mode Switch", ""}, {"Atten", "Attenuvert"}},
		WhiteMediumKnob{{to_mm<72>(57.66), to_mm<72>(59.44), Center, "Ch1", ""}, 0.5f},
		Toggle2pos{{to_mm<72>(16.27), to_mm<72>(122.455), Center, "Ch2 Mode Switch", ""}, {"Atten", "Attenuvert"}},
		WhiteMediumKnob{{to_mm<72>(57.66), to_mm<72>(122.46), Center, "Ch2", ""}, 0.5f},
		Toggle2pos{{to_mm<72>(16.27), to_mm<72>(185.475), Center, "Ch3 Mode Switch", ""}, {"Atten", "Attenuvert"}},
		WhiteMediumKnob{{to_mm<72>(57.66), to_mm<72>(185.47), Center, "Ch3", ""}, 0.5f},
		AnalogJackInput4ms{{to_mm<72>(20.75), to_mm<72>(246.71), Center, "Ch1 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.76), to_mm<72>(246.64), Center, "Ch1 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.75), to_mm<72>(280.86), Center, "Ch2 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.76), to_mm<72>(280.86), Center, "Ch2 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.75), to_mm<72>(315.07), Center, "Ch3 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.76), to_mm<72>(315.07), Center, "Ch3 Out", ""}},
		RedGreenLight{{to_mm<72>(43.26), to_mm<72>(246.64), Center, "Ch1 LED", ""}},
		RedGreenLight{{to_mm<72>(43.26), to_mm<72>(280.86), Center, "Ch2 LED", ""}},
		RedGreenLight{{to_mm<72>(43.26), to_mm<72>(315.07), Center, "Ch3 LED", ""}},
}};

    enum class Elem {
        Ch1ModeSwitch,
        Ch1Knob,
        Ch2ModeSwitch,
        Ch2Knob,
        Ch3ModeSwitch,
        Ch3Knob,
        Ch1In,
        Ch1Out,
        Ch2In,
        Ch2Out,
        Ch3In,
        Ch3Out,
        Ch1LedLight,
        Ch2LedLight,
        Ch3LedLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1, 
        KnobCh2, 
        KnobCh3, 
        NumKnobs,
    };
    
    enum {
        SwitchCh1_Mode_Switch, 
        SwitchCh2_Mode_Switch, 
        SwitchCh3_Mode_Switch, 
        NumSwitches,
    };
    
    enum {
        InputCh1_In, 
        InputCh2_In, 
        InputCh3_In, 
        NumInJacks,
    };
    
    enum {
        OutputCh1_Out, 
        OutputCh2_Out, 
        OutputCh3_Out, 
        NumOutJacks,
    };
    
    enum {
        LedCh1_Led, 
        LedCh2_Led, 
        LedCh3_Led, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
