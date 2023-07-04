#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct QCDInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"QCD"};
    static constexpr std::string_view description{"Quad Clock Distributor"};
    static constexpr uint32_t width_hp = 22;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/QCD-artwork.svg"};

    static constexpr std::array<Element, 50> Elements{{
		Knob9mm{to_mm<72>(67.25), to_mm<72>(58.66), "Gate PW Att 1", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(108.76), to_mm<72>(60.04), "Gate PW 1", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(153.48), to_mm<72>(81.3), "Div Mult CV 1", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(202.43), to_mm<72>(85.05), "Div Mult 1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(67.25), to_mm<72>(134.26), "Gate PW Att 2", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(108.76), to_mm<72>(135.64), "Gate PW 2", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(153.48), to_mm<72>(150.39), "Div Mult CV 2", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(202.43), to_mm<72>(154.17), "Div Mult 2", "", 0, 0, 1, 0.25f},
		Knob9mm{to_mm<72>(67.25), to_mm<72>(209.86), "Gate PW Att 3", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(108.76), to_mm<72>(211.24), "Gate PW 3", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(153.48), to_mm<72>(220.06), "Div Mult CV 3", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(202.43), to_mm<72>(223.29), "Div Mult 3", "", 0, 0, 1, 0.875f},
		Knob9mm{to_mm<72>(67.25), to_mm<72>(285.46), "Gate PW Att 4", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(108.76), to_mm<72>(286.84), "Gate PW 4", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(153.48), to_mm<72>(288.47), "Div Mult CV 4", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(202.43), to_mm<72>(292.41), "Div Mult 4", "", 0, 0, 1, 1.0f},
		AnalogJackInput4ms{to_mm<72>(23.39), to_mm<72>(55.0), "Gate PW CV 1", ""},
		AnalogJackInput4ms{to_mm<72>(249.58), to_mm<72>(76.7), "Div Mult CV 1 Jack", ""},
		GateJackInput4ms{to_mm<72>(296.32), to_mm<72>(42.31), "Clk In 1", ""},
		GateJackInput4ms{to_mm<72>(249.58), to_mm<72>(111.26), "Reset 1", ""},
		AnalogJackInput4ms{to_mm<72>(23.39), to_mm<72>(130.6), "Gate PW CV 2", ""},
		AnalogJackInput4ms{to_mm<72>(249.58), to_mm<72>(145.82), "Div Mult CV 2 Jack", ""},
		GateJackInput4ms{to_mm<72>(296.32), to_mm<72>(117.91), "Clk In 2", ""},
		GateJackInput4ms{to_mm<72>(249.58), to_mm<72>(180.38), "Reset 2", ""},
		AnalogJackInput4ms{to_mm<72>(23.39), to_mm<72>(206.2), "Gate PW CV 3", ""},
		AnalogJackInput4ms{to_mm<72>(249.58), to_mm<72>(214.94), "Div Mult CV 3 Jack", ""},
		GateJackInput4ms{to_mm<72>(296.32), to_mm<72>(193.51), "Clk In 3", ""},
		GateJackInput4ms{to_mm<72>(249.58), to_mm<72>(249.5), "Reset 3", ""},
		AnalogJackInput4ms{to_mm<72>(23.39), to_mm<72>(281.8), "Gate PW CV 4", ""},
		AnalogJackInput4ms{to_mm<72>(249.58), to_mm<72>(284.06), "Div Mult CV 4 Jack", ""},
		GateJackInput4ms{to_mm<72>(296.32), to_mm<72>(269.11), "Clk In 4", ""},
		GateJackInput4ms{to_mm<72>(249.58), to_mm<72>(318.62), "Reset 4", ""},
		GateJackOutput4ms{to_mm<72>(245.46), to_mm<72>(42.6), "Tap Out", ""},
		GateJackOutput4ms{to_mm<72>(23.39), to_mm<72>(89.56), "Inv Out 1", ""},
		GateJackOutput4ms{to_mm<72>(296.32), to_mm<72>(76.87), "Out 1", ""},
		GateJackOutput4ms{to_mm<72>(23.39), to_mm<72>(165.16), "Inv Out 2", ""},
		GateJackOutput4ms{to_mm<72>(296.32), to_mm<72>(152.47), "Out 2", ""},
		GateJackOutput4ms{to_mm<72>(23.39), to_mm<72>(240.76), "Inv Out 3", ""},
		GateJackOutput4ms{to_mm<72>(296.32), to_mm<72>(228.07), "Out 3", ""},
		GateJackOutput4ms{to_mm<72>(23.39), to_mm<72>(316.36), "Inv Out 4", ""},
		GateJackOutput4ms{to_mm<72>(296.32), to_mm<72>(303.67), "Out 4", ""},
		RedGreenBlueLight{to_mm<72>(48.06), to_mm<72>(89.91), "Inv LED 1", ""},
		RedGreenBlueLight{to_mm<72>(273.46), to_mm<72>(77.07), "LED 1", ""},
		RedGreenBlueLight{to_mm<72>(48.06), to_mm<72>(165.51), "Inv LED 2", ""},
		RedGreenBlueLight{to_mm<72>(273.46), to_mm<72>(152.67), "LED 2", ""},
		RedGreenBlueLight{to_mm<72>(47.68), to_mm<72>(240.97), "Inv LED 3", ""},
		RedGreenBlueLight{to_mm<72>(273.46), to_mm<72>(228.27), "LED 3", ""},
		RedGreenBlueLight{to_mm<72>(47.87), to_mm<72>(316.71), "Inv LED 4", ""},
		RedGreenBlueLight{to_mm<72>(273.46), to_mm<72>(303.87), "LED 4", ""},
		MomentaryButtonWhiteLight{to_mm<72>(192.73), to_mm<72>(42.56), "Tap Button", ""},
}};

    enum class Elem {
        GatePwAtt1Knob,
        GatePw1Knob,
        DivMultCv1Knob,
        DivMult1Knob,
        GatePwAtt2Knob,
        GatePw2Knob,
        DivMultCv2Knob,
        DivMult2Knob,
        GatePwAtt3Knob,
        GatePw3Knob,
        DivMultCv3Knob,
        DivMult3Knob,
        GatePwAtt4Knob,
        GatePw4Knob,
        DivMultCv4Knob,
        DivMult4Knob,
        GatePwCv1In,
        DivMultCv1JackIn,
        ClkIn1In,
        Reset1In,
        GatePwCv2In,
        DivMultCv2JackIn,
        ClkIn2In,
        Reset2In,
        GatePwCv3In,
        DivMultCv3JackIn,
        ClkIn3In,
        Reset3In,
        GatePwCv4In,
        DivMultCv4JackIn,
        ClkIn4In,
        Reset4In,
        TapOutOut,
        InvOut1Out,
        Out1Out,
        InvOut2Out,
        Out2Out,
        InvOut3Out,
        Out3Out,
        InvOut4Out,
        Out4Out,
        InvLed1Light,
        Led1Light,
        InvLed2Light,
        Led2Light,
        InvLed3Light,
        Led3Light,
        InvLed4Light,
        Led4Light,
        TapButtonButton,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobGate_Pw_Att_1 = 0,
        KnobGate_Pw_1 = 1,
        KnobDiv_Mult_Cv_1 = 2,
        KnobDiv_Mult_1 = 3,
        KnobGate_Pw_Att_2 = 4,
        KnobGate_Pw_2 = 5,
        KnobDiv_Mult_Cv_2 = 6,
        KnobDiv_Mult_2 = 7,
        KnobGate_Pw_Att_3 = 8,
        KnobGate_Pw_3 = 9,
        KnobDiv_Mult_Cv_3 = 10,
        KnobDiv_Mult_3 = 11,
        KnobGate_Pw_Att_4 = 12,
        KnobGate_Pw_4 = 13,
        KnobDiv_Mult_Cv_4 = 14,
        KnobDiv_Mult_4 = 15,
    };
    
    enum {
        SwitchTap_Button = 0,
    };
    
    enum {
        InputGate_Pw_Cv_1 = 0,
        InputDiv_Mult_Cv_1_Jack = 1,
        InputClk_In_1 = 2,
        InputReset_1 = 3,
        InputGate_Pw_Cv_2 = 4,
        InputDiv_Mult_Cv_2_Jack = 5,
        InputClk_In_2 = 6,
        InputReset_2 = 7,
        InputGate_Pw_Cv_3 = 8,
        InputDiv_Mult_Cv_3_Jack = 9,
        InputClk_In_3 = 10,
        InputReset_3 = 11,
        InputGate_Pw_Cv_4 = 12,
        InputDiv_Mult_Cv_4_Jack = 13,
        InputClk_In_4 = 14,
        InputReset_4 = 15,
    };
    
    enum {
        OutputTap_Out = 0,
        OutputInv_Out_1 = 1,
        OutputOut_1 = 2,
        OutputInv_Out_2 = 3,
        OutputOut_2 = 4,
        OutputInv_Out_3 = 5,
        OutputOut_3 = 6,
        OutputInv_Out_4 = 7,
        OutputOut_4 = 8,
    };
    
    enum {
        LedInv_Led_1 = 0,
        LedLed_1 = 1,
        LedInv_Led_2 = 2,
        LedLed_2 = 3,
        LedInv_Led_3 = 4,
        LedLed_3 = 5,
        LedInv_Led_4 = 6,
        LedLed_4 = 7,
    };
};
} // namespace MetaModule
