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
		WhiteMediumKnob{{to_mm<72>(32.16), to_mm<72>(68.49), Center, "Ch1", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(96.96), to_mm<72>(68.49), Center, "Ch2", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(161.76), to_mm<72>(68.49), Center, "Ch3", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(226.56), to_mm<72>(68.49), Center, "Ch4", ""}, 0.5f},
		OrangeButton{{to_mm<72>(32.16), to_mm<72>(131.5), Center, "Add", ""}},
		OrangeButton{{to_mm<72>(32.16), to_mm<72>(178.27), Center, "Del", ""}},
		WhiteLargeKnob{{to_mm<72>(129.36), to_mm<72>(154.88), Center, "Frame", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(219.36), to_mm<72>(154.88), Center, "Modulation", ""}, 0.5f},
		Toggle2posHoriz{{to_mm<72>(26.77), to_mm<72>(235.875), Center, "10V Offset", ""}, {"On", "Off"}},
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
		GreenLight{{to_mm<72>(32.16), to_mm<72>(100.88), Center, "Ch1", ""}},
		GreenLight{{to_mm<72>(96.96), to_mm<72>(100.88), Center, "Ch2", ""}},
		GreenLight{{to_mm<72>(161.76), to_mm<72>(100.88), Center, "Ch3", ""}},
		GreenLight{{to_mm<72>(226.56), to_mm<72>(100.88), Center, "Ch4", ""}},
		GreenLight{{to_mm<72>(64.56), to_mm<72>(154.89), Center, "AddDel", ""}},
}};

    enum class Elem {
        Ch1Knob,
        Ch2Knob,
        Ch3Knob,
        Ch4Knob,
        AddButton,
        DelButton,
        FrameKnob,
        ModulationKnob,
        _10VOffsetSwitch,
        AllIn,
        Ch1In,
        Ch2In,
        Ch3In,
        Ch4In,
        FrameCvIn,
        MixOut,
        Ch1Out,
        Ch2Out,
        Ch3Out,
        Ch4Out,
        FrStepOut,
        Ch1Light,
        Ch2Light,
        Ch3Light,
        Ch4Light,
        AdddelLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1, 
        KnobCh2, 
        KnobCh3, 
        KnobCh4, 
        KnobFrame, 
        KnobModulation, 
        NumKnobs,
    };
    
    enum {
        SwitchAdd, 
        SwitchDel, 
        Switch_10V_Offset, 
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
        LedCh1, 
        LedCh2, 
        LedCh3, 
        LedCh4, 
        LedAdddel, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
