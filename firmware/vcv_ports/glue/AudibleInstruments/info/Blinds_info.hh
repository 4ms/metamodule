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
		Davies1900hBlackKnob{{to_mm<72>(27.38), to_mm<72>(69.52), Center, "Ch1 x23 WhiteMediumKnob", ""}, 0.5f},
		Knob9mm{{to_mm<72>(77.98), to_mm<72>(69.52), Center, "Ch1 Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Davies1900hBlackKnob{{to_mm<72>(27.38), to_mm<72>(145.06), Center, "Ch2 x23 WhiteMediumKnob", ""}, 0.5f},
		Knob9mm{{to_mm<72>(77.98), to_mm<72>(145.06), Center, "Ch2 Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Davies1900hBlackKnob{{to_mm<72>(27.38), to_mm<72>(220.6), Center, "Ch3 x23 WhiteMediumKnob", ""}, 0.421875f},
		Knob9mm{{to_mm<72>(77.98), to_mm<72>(220.6), Center, "Ch3 Atten x23 WhiteSmallKnob", ""}, 0.0f},
		Davies1900hBlackKnob{{to_mm<72>(27.38), to_mm<72>(296.15), Center, "Ch4 x23 WhiteMediumKnob", ""}, 0.5f},
		Knob9mm{{to_mm<72>(77.98), to_mm<72>(296.15), Center, "Ch4 Atten x23 WhiteSmallKnob", ""}, 0.0f},
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
		RedGreenBlueLight{{to_mm<72>(77.97), to_mm<72>(97.3), Center, "Ch1 Atten x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(150.01), to_mm<72>(88.37), Center, "Ch1 x23 YellowLight", ""}},
		RedGreenBlueLight{{to_mm<72>(77.97), to_mm<72>(172.84), Center, "Ch2 Atten x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(150.01), to_mm<72>(163.91), Center, "Ch2 x23 YellowLight", ""}},
		RedGreenBlueLight{{to_mm<72>(77.97), to_mm<72>(248.38), Center, "Ch3 Atten x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(150.01), to_mm<72>(239.45), Center, "Ch3 x23 YellowLight", ""}},
		RedGreenBlueLight{{to_mm<72>(77.97), to_mm<72>(323.93), Center, "Ch4 Atten x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(150.01), to_mm<72>(315.0), Center, "Ch4 x23 YellowLight", ""}},
}};

    enum class Elem {
        Ch1_X23_WhitemediumknobKnob,
        Ch1_Atten_X23_WhitesmallknobKnob,
        Ch2_X23_WhitemediumknobKnob,
        Ch2_Atten_X23_WhitesmallknobKnob,
        Ch3_X23_WhitemediumknobKnob,
        Ch3_Atten_X23_WhitesmallknobKnob,
        Ch4_X23_WhitemediumknobKnob,
        Ch4_Atten_X23_WhitesmallknobKnob,
        Ch1_In,
        Ch1_Out,
        Ch1_CvIn,
        Ch2_In,
        Ch2_Out,
        Ch2_CvIn,
        Ch3_In,
        Ch3_Out,
        Ch3_CvIn,
        Ch4_In,
        Ch4_Out,
        Ch4_CvIn,
        Ch1_Atten_X23_GreenlightLight,
        Ch1_X23_YellowlightLight,
        Ch2_Atten_X23_GreenlightLight,
        Ch2_X23_YellowlightLight,
        Ch3_Atten_X23_GreenlightLight,
        Ch3_X23_YellowlightLight,
        Ch4_Atten_X23_GreenlightLight,
        Ch4_X23_YellowlightLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1_X23_Whitemediumknob, 
        KnobCh1_Atten_X23_Whitesmallknob, 
        KnobCh2_X23_Whitemediumknob, 
        KnobCh2_Atten_X23_Whitesmallknob, 
        KnobCh3_X23_Whitemediumknob, 
        KnobCh3_Atten_X23_Whitesmallknob, 
        KnobCh4_X23_Whitemediumknob, 
        KnobCh4_Atten_X23_Whitesmallknob, 
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
        LedCh1_Atten_X23_Greenlight, 
        LedCh1_X23_Yellowlight, 
        LedCh2_Atten_X23_Greenlight, 
        LedCh2_X23_Yellowlight, 
        LedCh3_Atten_X23_Greenlight, 
        LedCh3_X23_Yellowlight, 
        LedCh4_Atten_X23_Greenlight, 
        LedCh4_X23_Yellowlight, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
