#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct SequantInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Sequant"};
    static constexpr std::string_view description{"2 Ch. 8 Step Sequencer w/ Quantizer"};
    static constexpr uint32_t width_hp = 17;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Sequant-artwork.svg"};

    static constexpr std::array<Element, 44> Elements{{
		Knob9mm{to_mm<72>(64.34), to_mm<72>(46.59), "Tempo", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(102.55), to_mm<72>(46.59), "Delay", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(140.76), to_mm<72>(46.59), "Gate", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(178.96), to_mm<72>(46.59), "Slew", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(22.96), to_mm<72>(99.16), "Step 1-1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(51.3), to_mm<72>(99.16), "Step 2-1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(79.65), to_mm<72>(99.16), "Step 3-1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(108.0), to_mm<72>(99.16), "Step 4-1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(136.44), to_mm<72>(99.16), "Step 5-1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(164.79), to_mm<72>(99.16), "Step 6-1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(193.13), to_mm<72>(99.16), "Step 7-1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(221.48), to_mm<72>(99.16), "Step 8-1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(22.96), to_mm<72>(137.36), "Step 1-2", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(51.3), to_mm<72>(137.36), "Step 2-2", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(79.65), to_mm<72>(137.36), "Step 3-2", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(108.0), to_mm<72>(137.36), "Step 4-2", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(136.44), to_mm<72>(137.36), "Step 5-2", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(164.79), to_mm<72>(137.36), "Step 6-2", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(193.13), to_mm<72>(137.36), "Step 7-2", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(221.48), to_mm<72>(137.36), "Step 8-2", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(31.99), to_mm<72>(170.27), "Scale", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(212.77), to_mm<72>(170.27), "Chance", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(31.99), to_mm<72>(211.46), "Root", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(212.77), to_mm<72>(211.46), "Repeat", "", 0, 0, 1, 0.0f},
		GateJackInput4ms{to_mm<72>(31.99), to_mm<72>(263.37), "Clock", ""},
		GateJackInput4ms{to_mm<72>(77.19), to_mm<72>(263.37), "Start/Reset", ""},
		GateJackInput4ms{to_mm<72>(122.38), to_mm<72>(263.37), "Stop", ""},
		AnalogJackInput4ms{to_mm<72>(167.58), to_mm<72>(263.37), "Gate In", ""},
		AnalogJackInput4ms{to_mm<72>(212.77), to_mm<72>(263.37), "Repeat CV", ""},
		GateJackOutput4ms{to_mm<72>(31.99), to_mm<72>(310.96), "Clock Out", ""},
		GateJackOutput4ms{to_mm<72>(77.19), to_mm<72>(310.96), "Start/End", ""},
		GateJackOutput4ms{to_mm<72>(122.25), to_mm<72>(310.96), "Gate Out", ""},
		AnalogJackOutput4ms{to_mm<72>(167.58), to_mm<72>(310.96), "Out 1", ""},
		AnalogJackOutput4ms{to_mm<72>(212.77), to_mm<72>(310.96), "Out 2", ""},
		RedGreenBlueLight{to_mm<72>(22.96), to_mm<72>(118.26), "Step 1 LED", ""},
		RedGreenBlueLight{to_mm<72>(51.3), to_mm<72>(118.26), "Step 2 LED", ""},
		RedGreenBlueLight{to_mm<72>(79.65), to_mm<72>(118.26), "Step 3 LED", ""},
		RedGreenBlueLight{to_mm<72>(108.0), to_mm<72>(118.26), "Step 4 LED", ""},
		RedGreenBlueLight{to_mm<72>(136.44), to_mm<72>(118.26), "Step 5 LED", ""},
		RedGreenBlueLight{to_mm<72>(164.79), to_mm<72>(118.26), "Step 6 LED", ""},
		RedGreenBlueLight{to_mm<72>(193.13), to_mm<72>(118.26), "Step 7 LED", ""},
		RedGreenBlueLight{to_mm<72>(221.48), to_mm<72>(118.26), "Step 8 LED", ""},
		MomentaryButtonWhiteLight{to_mm<72>(22.96), to_mm<72>(46.59), "Start/Stop", ""},
		MomentaryButtonWhiteLight{to_mm<72>(221.38), to_mm<72>(46.59), "Select", ""},
}};

    enum class Elem {
        TempoKnob,
        DelayKnob,
        GateKnob,
        SlewKnob,
        Step1N1Knob,
        Step2N1Knob,
        Step3N1Knob,
        Step4N1Knob,
        Step5N1Knob,
        Step6N1Knob,
        Step7N1Knob,
        Step8N1Knob,
        Step1N2Knob,
        Step2N2Knob,
        Step3N2Knob,
        Step4N2Knob,
        Step5N2Knob,
        Step6N2Knob,
        Step7N2Knob,
        Step8N2Knob,
        ScaleKnob,
        ChanceKnob,
        RootKnob,
        RepeatKnob,
        ClockIn,
        Start_ResetIn,
        StopIn,
        GateIn,
        RepeatCvIn,
        ClockOut,
        Start_EndOut,
        GateOut,
        Out1Out,
        Out2Out,
        Step1LedLight,
        Step2LedLight,
        Step3LedLight,
        Step4LedLight,
        Step5LedLight,
        Step6LedLight,
        Step7LedLight,
        Step8LedLight,
        Start_StopButton,
        SelectButton,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobTempo = 0,
        KnobDelay = 1,
        KnobGate = 2,
        KnobSlew = 3,
        KnobStep_1N1 = 4,
        KnobStep_2N1 = 5,
        KnobStep_3N1 = 6,
        KnobStep_4N1 = 7,
        KnobStep_5N1 = 8,
        KnobStep_6N1 = 9,
        KnobStep_7N1 = 10,
        KnobStep_8N1 = 11,
        KnobStep_1N2 = 12,
        KnobStep_2N2 = 13,
        KnobStep_3N2 = 14,
        KnobStep_4N2 = 15,
        KnobStep_5N2 = 16,
        KnobStep_6N2 = 17,
        KnobStep_7N2 = 18,
        KnobStep_8N2 = 19,
        KnobScale = 20,
        KnobChance = 21,
        KnobRoot = 22,
        KnobRepeat = 23,
        NumKnobs,
    };
    
    enum {
        SwitchStart_Stop = 0,
        SwitchSelect = 1,
        NumSwitches,
    };
    
    enum {
        InputClock = 0,
        InputStart_Reset = 1,
        InputStop = 2,
        InputGate_In = 3,
        InputRepeat_Cv = 4,
        NumInJacks,
    };
    
    enum {
        OutputClock_Out = 0,
        OutputStart_End = 1,
        OutputGate_Out = 2,
        OutputOut_1 = 3,
        OutputOut_2 = 4,
        NumOutJacks,
    };
    
    enum {
        LedStep_1_Led = 0,
        LedStep_2_Led = 1,
        LedStep_3_Led = 2,
        LedStep_4_Led = 3,
        LedStep_5_Led = 4,
        LedStep_6_Led = 5,
        LedStep_7_Led = 6,
        LedStep_8_Led = 7,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
