#pragma once
#include "CoreModules/AudibleInstruments/AudibleInstruments_elements.hh"
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
		WhiteMediumKnob{{to_mm<72>(57.66), to_mm<72>(59.44), Center, "Ch1 Gain", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(57.66), to_mm<72>(122.46), Center, "Ch2 Gain", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(57.66), to_mm<72>(185.47), Center, "Ch3 Gain", ""}, 0.5f},
		Toggle2pos{{to_mm<72>(16.27), to_mm<72>(59.415), Center, "Ch1 Mode", ""}, {"Atten", "Attenuvert"}},
		Toggle2pos{{to_mm<72>(16.27), to_mm<72>(122.455), Center, "Ch2 Mode", ""}, {"Atten", "Attenuvert"}},
		Toggle2pos{{to_mm<72>(16.27), to_mm<72>(185.475), Center, "Ch3 Mode", ""}, {"Atten", "Attenuvert"}},
		AnalogJackInput4ms{{to_mm<72>(20.75), to_mm<72>(246.71), Center, "Ch1 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.75), to_mm<72>(280.86), Center, "Ch2 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(20.75), to_mm<72>(315.07), Center, "Ch3 In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.76), to_mm<72>(246.64), Center, "Ch1 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.76), to_mm<72>(280.86), Center, "Ch2 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(65.76), to_mm<72>(315.07), Center, "Ch3 Out", ""}},
		GreenRedLight{{to_mm<72>(43.26), to_mm<72>(246.64), Center, "Ch1 LED", ""}},
		GreenRedLight{{to_mm<72>(43.26), to_mm<72>(280.86), Center, "Ch2 LED", ""}},
		GreenRedLight{{to_mm<72>(43.26), to_mm<72>(315.07), Center, "Ch3 LED", ""}},
}};

    enum class Elem {
        Ch1GainKnob,
        Ch2GainKnob,
        Ch3GainKnob,
        Ch1ModeSwitch,
        Ch2ModeSwitch,
        Ch3ModeSwitch,
        Ch1In,
        Ch2In,
        Ch3In,
        Ch1Out,
        Ch2Out,
        Ch3Out,
        Ch1LedLight,
        Ch2LedLight,
        Ch3LedLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1_Gain, 
        KnobCh2_Gain, 
        KnobCh3_Gain, 
        NumKnobs,
    };
    
    enum {
        SwitchCh1_Mode, 
        SwitchCh2_Mode, 
        SwitchCh3_Mode, 
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
