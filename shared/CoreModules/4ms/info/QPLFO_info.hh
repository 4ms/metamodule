#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct QPLFOInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"QPLFO"};
    static constexpr std::string_view description{"Quad Pingable LFO"};
    static constexpr uint32_t width_hp = 12;
    static constexpr std::string_view svg_filename{"res/modules/QPLFO_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/QPLFO.png"};

    using enum Coords;

    static constexpr std::array<Element, 32> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(114.03), to_mm<72>(59.68), Center, "Skew 1", ""}},
		Davies1900hBlackKnob{{to_mm<72>(114.03), to_mm<72>(135.28), Center, "Skew 2", ""}},
		Davies1900hBlackKnob{{to_mm<72>(114.03), to_mm<72>(210.88), Center, "Skew 3", ""}},
		Davies1900hBlackKnob{{to_mm<72>(114.03), to_mm<72>(286.48), Center, "Skew 4", ""}},
		WhiteMomentary7mm{{to_mm<72>(154.79), to_mm<72>(43.18), Center, "Ping 1", ""}},
		OrangeButton{{to_mm<72>(154.79), to_mm<72>(81.06), Center, "On 1", ""}},
		WhiteMomentary7mm{{to_mm<72>(154.79), to_mm<72>(118.78), Center, "Ping 2", ""}},
		OrangeButton{{to_mm<72>(154.79), to_mm<72>(156.66), Center, "On 2", ""}},
		WhiteMomentary7mm{{to_mm<72>(154.79), to_mm<72>(194.38), Center, "Ping 3", ""}},
		OrangeButton{{to_mm<72>(154.79), to_mm<72>(232.26), Center, "On 3", ""}},
		WhiteMomentary7mm{{to_mm<72>(154.79), to_mm<72>(269.98), Center, "Ping 4", ""}},
		OrangeButton{{to_mm<72>(154.79), to_mm<72>(307.86), Center, "On 4", ""}},
		GateJackInput4ms{{to_mm<72>(22.57), to_mm<72>(42.18), Center, "Ping 1 Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(67.94), to_mm<72>(59.46), Center, "Skew 1 CV", ""}},
		GateJackInput4ms{{to_mm<72>(67.94), to_mm<72>(94.02), Center, "Reset 1", ""}},
		GateJackInput4ms{{to_mm<72>(22.57), to_mm<72>(117.78), Center, "Ping 2 Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(67.94), to_mm<72>(135.06), Center, "Skew 2 Jack", ""}},
		GateJackInput4ms{{to_mm<72>(67.94), to_mm<72>(169.62), Center, "Reset 2", ""}},
		GateJackInput4ms{{to_mm<72>(22.57), to_mm<72>(193.38), Center, "Ping 3 Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(67.94), to_mm<72>(210.66), Center, "Skew 3 Jack", ""}},
		GateJackInput4ms{{to_mm<72>(67.94), to_mm<72>(245.22), Center, "Reset 3", ""}},
		GateJackInput4ms{{to_mm<72>(22.57), to_mm<72>(268.98), Center, "Ping 4 Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(67.94), to_mm<72>(286.26), Center, "Skew 4 Jack", ""}},
		GateJackInput4ms{{to_mm<72>(67.94), to_mm<72>(320.82), Center, "Reset 4", ""}},
		AnalogJackOutput4ms{{to_mm<72>(22.57), to_mm<72>(76.74), Center, "Out 1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(22.57), to_mm<72>(152.34), Center, "Out 2", ""}},
		AnalogJackOutput4ms{{to_mm<72>(22.57), to_mm<72>(227.94), Center, "Out 3", ""}},
		AnalogJackOutput4ms{{to_mm<72>(22.57), to_mm<72>(303.54), Center, "Out 4", ""}},
		RedGreenBlueLight{{to_mm<72>(45.23), to_mm<72>(76.95), Center, "LED 1", ""}},
		RedGreenBlueLight{{to_mm<72>(45.23), to_mm<72>(152.55), Center, "LED 2", ""}},
		RedGreenBlueLight{{to_mm<72>(45.23), to_mm<72>(228.15), Center, "LED 3", ""}},
		RedGreenBlueLight{{to_mm<72>(45.23), to_mm<72>(303.75), Center, "LED 4", ""}},
}};

    enum class Elem {
        Skew1Knob,
        Skew2Knob,
        Skew3Knob,
        Skew4Knob,
        Ping1Button,
        On1Button,
        Ping2Button,
        On2Button,
        Ping3Button,
        On3Button,
        Ping4Button,
        On4Button,
        Ping1JackIn,
        Skew1CvIn,
        Reset1In,
        Ping2JackIn,
        Skew2JackIn,
        Reset2In,
        Ping3JackIn,
        Skew3JackIn,
        Reset3In,
        Ping4JackIn,
        Skew4JackIn,
        Reset4In,
        Out1Out,
        Out2Out,
        Out3Out,
        Out4Out,
        Led1Light,
        Led2Light,
        Led3Light,
        Led4Light,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobSkew_1 = 0,
        KnobSkew_2 = 1,
        KnobSkew_3 = 2,
        KnobSkew_4 = 3,
        NumKnobs,
    };
    
    enum {
        SwitchPing_1 = 0,
        SwitchOn_1 = 1,
        SwitchPing_2 = 2,
        SwitchOn_2 = 3,
        SwitchPing_3 = 4,
        SwitchOn_3 = 5,
        SwitchPing_4 = 6,
        SwitchOn_4 = 7,
        NumSwitches,
    };
    
    enum {
        InputPing_1_Jack = 0,
        InputSkew_1_Cv = 1,
        InputReset_1 = 2,
        InputPing_2_Jack = 3,
        InputSkew_2_Jack = 4,
        InputReset_2 = 5,
        InputPing_3_Jack = 6,
        InputSkew_3_Jack = 7,
        InputReset_3 = 8,
        InputPing_4_Jack = 9,
        InputSkew_4_Jack = 10,
        InputReset_4 = 11,
        NumInJacks,
    };
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
        OutputOut_3 = 2,
        OutputOut_4 = 3,
        NumOutJacks,
    };
    
    enum {
        LedLed_1 = 0,
        LedLed_2 = 1,
        LedLed_3 = 2,
        LedLed_4 = 3,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
