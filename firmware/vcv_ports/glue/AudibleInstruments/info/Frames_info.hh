#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct FramesInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Frames"};
    static constexpr std::string_view description{"Keyframe Mixer"};
    static constexpr uint32_t width_hp = 18;
    static constexpr std::string_view svg_filename{"res/modules/Frames_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Frames.png"};

    using enum Coords;

    static constexpr std::array<Element, 26> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(32.16), to_mm<72>(68.49), Center, "Ch1 x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(96.96), to_mm<72>(68.49), Center, "Ch2 x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(161.76), to_mm<72>(68.49), Center, "Ch3 x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(226.56), to_mm<72>(68.49), Center, "Ch4 x23 WhiteMediumKnob", ""}, 0.5f},
		OrangeButton{{to_mm<72>(32.16), to_mm<72>(131.5), Center, "Add", ""}},
		OrangeButton{{to_mm<72>(32.16), to_mm<72>(178.27), Center, "Del", ""}},
		DaviesLargeKnob{{to_mm<72>(129.36), to_mm<72>(154.88), Center, "Frame x23 WhiteLargeKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(219.36), to_mm<72>(154.88), Center, "Modulation x23 WhiteMediumKnob", ""}, 0.5f},
		Toggle2posHoriz{{to_mm<72>(26.77), to_mm<72>(235.875), Center, " x31 0V Offset x40 On x40 Off", ""}},
		AnalogJackInput4ms{{to_mm<72>(26.77), to_mm<72>(273.67), Center, "All", ""}},
		AnalogJackInput4ms{{to_mm<72>(68.17), to_mm<72>(273.67), Center, "Ch1 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(109.57), to_mm<72>(273.67), Center, "Ch2 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(150.97), to_mm<72>(273.67), Center, "Ch3 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(192.37), to_mm<72>(273.67), Center, "Ch4 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(233.77), to_mm<72>(273.67), Center, "Frame CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(26.77), to_mm<72>(315.07), Center, "Mix", ""}},
		AnalogJackOutput4ms{{to_mm<72>(68.17), to_mm<72>(315.07), Center, "Ch1 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(109.57), to_mm<72>(315.07), Center, "Ch2 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(150.97), to_mm<72>(315.07), Center, "Ch3 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(192.37), to_mm<72>(315.07), Center, "Ch4 Out", ""}},
		GateJackOutput4ms{{to_mm<72>(233.77), to_mm<72>(315.07), Center, "Fr Step", ""}},
		RedGreenBlueLight{{to_mm<72>(32.16), to_mm<72>(100.88), Center, "Ch1 x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(96.96), to_mm<72>(100.88), Center, "Ch2 x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(161.76), to_mm<72>(100.88), Center, "Ch3 x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(226.56), to_mm<72>(100.88), Center, "Ch4 x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(64.56), to_mm<72>(154.89), Center, "AddDel x23 GreenLight", ""}},
}};

    enum class Elem {
        Ch1_X23_WhitemediumknobKnob,
        Ch2_X23_WhitemediumknobKnob,
        Ch3_X23_WhitemediumknobKnob,
        Ch4_X23_WhitemediumknobKnob,
        AddButton,
        DelButton,
        Frame_X23_WhitelargeknobKnob,
        Modulation_X23_WhitemediumknobKnob,
        _X31_0V_Offset_X40_On_X40_OffSwitch,
        AllIn,
        Ch1_In,
        Ch2_In,
        Ch3_In,
        Ch4_In,
        Frame_CvIn,
        MixOut,
        Ch1_Out,
        Ch2_Out,
        Ch3_Out,
        Ch4_Out,
        Fr_StepOut,
        Ch1_X23_GreenlightLight,
        Ch2_X23_GreenlightLight,
        Ch3_X23_GreenlightLight,
        Ch4_X23_GreenlightLight,
        Adddel_X23_GreenlightLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1_X23_Whitemediumknob, 
        KnobCh2_X23_Whitemediumknob, 
        KnobCh3_X23_Whitemediumknob, 
        KnobCh4_X23_Whitemediumknob, 
        KnobFrame_X23_Whitelargeknob, 
        KnobModulation_X23_Whitemediumknob, 
        NumKnobs,
    };
    
    enum {
        SwitchAdd, 
        SwitchDel, 
        Switch_X31_0V_Offset_X40_On_X40_Off, 
        NumSwitches,
    };
    
    enum {
        InputAll, 
        InputCh1_In, 
        InputCh2_In, 
        InputCh3_In, 
        InputCh4_In, 
        InputFrame_Cv, 
        NumInJacks,
    };
    
    enum {
        OutputMix, 
        OutputCh1_Out, 
        OutputCh2_Out, 
        OutputCh3_Out, 
        OutputCh4_Out, 
        OutputFr_Step, 
        NumOutJacks,
    };
    
    enum {
        LedCh1_X23_Greenlight, 
        LedCh2_X23_Greenlight, 
        LedCh3_X23_Greenlight, 
        LedCh4_X23_Greenlight, 
        LedAdddel_X23_Greenlight, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
