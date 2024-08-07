#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct BlindsInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Blinds"};
    static constexpr std::string_view description{"Polarizing Mixer"};
    static constexpr uint32_t width_hp = 34;
    static constexpr std::string_view svg_filename{"res/modules/Blinds_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Blinds.png"};

    using enum Coords;

    static constexpr std::array<Element, 28> Elements{{
		WhiteMediumKnob{{to_mm<72>(27.38), to_mm<72>(69.52), Center, "Ch1", ""}, 0.5f},
		WhiteSmallKnob{{to_mm<72>(77.98), to_mm<72>(69.52), Center, "Ch1 Atten", ""}, 0.0f},
		WhiteMediumKnob{{to_mm<72>(27.38), to_mm<72>(145.06), Center, "Ch2", ""}, 0.5f},
		WhiteSmallKnob{{to_mm<72>(77.98), to_mm<72>(145.06), Center, "Ch2 Atten", ""}, 0.0f},
		WhiteMediumKnob{{to_mm<72>(27.38), to_mm<72>(220.6), Center, "Ch3", ""}, 0.421875f},
		WhiteSmallKnob{{to_mm<72>(77.98), to_mm<72>(220.6), Center, "Ch3 Atten", ""}, 0.0f},
		WhiteMediumKnob{{to_mm<72>(27.38), to_mm<72>(296.15), Center, "Ch4", ""}, 0.5f},
		WhiteSmallKnob{{to_mm<72>(77.98), to_mm<72>(296.15), Center, "Ch4 Atten", ""}, 0.0f},
		AnalogJackInput4ms{{to_mm<72>(117.44), to_mm<72>(50.67), Center, "Ch1 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(150.01), to_mm<72>(50.67), Center, "Ch1 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.44), to_mm<72>(88.37), Center, "Ch1 CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.44), to_mm<72>(126.21), Center, "Ch2 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(150.01), to_mm<72>(126.21), Center, "Ch2 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.44), to_mm<72>(163.91), Center, "Ch2 CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.44), to_mm<72>(201.75), Center, "Ch3 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(150.01), to_mm<72>(201.75), Center, "Ch3 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.44), to_mm<72>(239.45), Center, "Ch3 CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.44), to_mm<72>(277.3), Center, "Ch4 IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(150.01), to_mm<72>(277.3), Center, "Ch4 Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.44), to_mm<72>(315.0), Center, "Ch4 CV", ""}},
		RedGreenLight{{to_mm<72>(77.97), to_mm<72>(97.3), Center, "Ch1 Atten", ""}},
		RedGreenLight{{to_mm<72>(150.01), to_mm<72>(88.37), Center, "Ch1", ""}},
		RedGreenLight{{to_mm<72>(77.97), to_mm<72>(172.84), Center, "Ch2 Atten", ""}},
		RedGreenLight{{to_mm<72>(150.01), to_mm<72>(163.91), Center, "Ch2", ""}},
		RedGreenLight{{to_mm<72>(77.97), to_mm<72>(248.38), Center, "Ch3 Atten", ""}},
		RedGreenLight{{to_mm<72>(150.01), to_mm<72>(239.45), Center, "Ch3", ""}},
		RedGreenLight{{to_mm<72>(77.97), to_mm<72>(323.93), Center, "Ch4 Atten", ""}},
		RedGreenLight{{to_mm<72>(150.01), to_mm<72>(315.0), Center, "Ch4", ""}},
}};

    enum class Elem {
        Ch1Knob,
        Ch1AttenKnob,
        Ch2Knob,
        Ch2AttenKnob,
        Ch3Knob,
        Ch3AttenKnob,
        Ch4Knob,
        Ch4AttenKnob,
        Ch1In,
        Ch1Out,
        Ch1CvIn,
        Ch2In,
        Ch2Out,
        Ch2CvIn,
        Ch3In,
        Ch3Out,
        Ch3CvIn,
        Ch4In,
        Ch4Out,
        Ch4CvIn,
        Ch1AttenLight,
        Ch1Light,
        Ch2AttenLight,
        Ch2Light,
        Ch3AttenLight,
        Ch3Light,
        Ch4AttenLight,
        Ch4Light,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1, 
        KnobCh1_Atten, 
        KnobCh2, 
        KnobCh2_Atten, 
        KnobCh3, 
        KnobCh3_Atten, 
        KnobCh4, 
        KnobCh4_Atten, 
        NumKnobs,
    };
    
    
    enum {
        InputCh1_In, 
        InputCh1_Cv, 
        InputCh2_In, 
        InputCh2_Cv, 
        InputCh3_In, 
        InputCh3_Cv, 
        InputCh4_In, 
        InputCh4_Cv, 
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
        LedCh1_Atten, 
        LedCh1, 
        LedCh2_Atten, 
        LedCh2, 
        LedCh3_Atten, 
        LedCh3, 
        LedCh4_Atten, 
        LedCh4, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
