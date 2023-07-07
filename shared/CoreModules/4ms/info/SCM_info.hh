#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct SCMInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"SCM"};
    static constexpr std::string_view description{"Shuffling Clock Multiplier"};
    static constexpr uint32_t width_hp = 12;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/SCM-artwork.svg"};

    static constexpr std::array<Element, 33> Elements{{
		Davies1900hBlackKnob{to_mm<72>(147.99), to_mm<72>(54.12), "Rotate", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(147.99), to_mm<72>(104.09), "Slip", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(147.99), to_mm<72>(154.07), "Shuffle", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(147.99), to_mm<72>(204.04), "Skip", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(147.99), to_mm<72>(254.01), "PW", "", 0, 0, 1, 0.5f},
		GateJackInput4ms{to_mm<72>(46.48), to_mm<72>(56.3), "Clk In", ""},
		GateJackInput4ms{to_mm<72>(81.45), to_mm<72>(55.11), "Resync", ""},
		AnalogJackInput4ms{to_mm<72>(81.45), to_mm<72>(90.12), "Rotate Jack", ""},
		AnalogJackInput4ms{to_mm<72>(81.45), to_mm<72>(126.12), "Slip Jack", ""},
		AnalogJackInput4ms{to_mm<72>(81.45), to_mm<72>(162.12), "Shuffle Jack", ""},
		AnalogJackInput4ms{to_mm<72>(81.45), to_mm<72>(198.12), "Skip Jack", ""},
		AnalogJackInput4ms{to_mm<72>(81.45), to_mm<72>(234.12), "PW Jack", ""},
		GateJackInput4ms{to_mm<72>(81.45), to_mm<72>(270.12), "4x Fast Jack", ""},
		GateJackInput4ms{to_mm<72>(81.45), to_mm<72>(306.12), "Mute Jack", ""},
		GateJackOutput4ms{to_mm<72>(46.48), to_mm<72>(87.91), "x1", ""},
		GateJackOutput4ms{to_mm<72>(46.48), to_mm<72>(119.52), "x2", ""},
		GateJackOutput4ms{to_mm<72>(46.48), to_mm<72>(151.13), "S3", ""},
		GateJackOutput4ms{to_mm<72>(46.48), to_mm<72>(182.73), "S4", ""},
		GateJackOutput4ms{to_mm<72>(46.48), to_mm<72>(214.34), "S5", ""},
		GateJackOutput4ms{to_mm<72>(46.48), to_mm<72>(245.95), "S6", ""},
		GateJackOutput4ms{to_mm<72>(46.48), to_mm<72>(277.56), "S8", ""},
		GateJackOutput4ms{to_mm<72>(46.48), to_mm<72>(309.17), "x8", ""},
		RedGreenBlueLight{to_mm<72>(17.3), to_mm<72>(56.3), "LED in", ""},
		RedGreenBlueLight{to_mm<72>(17.3), to_mm<72>(87.91), "LED x1", ""},
		RedGreenBlueLight{to_mm<72>(17.3), to_mm<72>(119.52), "LED x2", ""},
		RedGreenBlueLight{to_mm<72>(17.3), to_mm<72>(151.13), "LED S3", ""},
		RedGreenBlueLight{to_mm<72>(17.3), to_mm<72>(182.73), "LED S4", ""},
		RedGreenBlueLight{to_mm<72>(17.3), to_mm<72>(214.34), "LED S5", ""},
		RedGreenBlueLight{to_mm<72>(17.3), to_mm<72>(245.95), "LED S6", ""},
		RedGreenBlueLight{to_mm<72>(17.3), to_mm<72>(277.56), "LED S8", ""},
		RedGreenBlueLight{to_mm<72>(17.3), to_mm<72>(309.17), "LED x8", ""},
		LatchingButtonMonoLight{to_mm<72>(148.84), to_mm<72>(291.85), "4x Fast", ""},
		LatchingButtonMonoLight{to_mm<72>(148.84), to_mm<72>(325.47), "Mute", ""},
}};

    enum class Elem {
        RotateKnob,
        SlipKnob,
        ShuffleKnob,
        SkipKnob,
        PwKnob,
        ClkIn,
        ResyncIn,
        RotateJackIn,
        SlipJackIn,
        ShuffleJackIn,
        SkipJackIn,
        PwJackIn,
        _4XFastJackIn,
        MuteJackIn,
        X1Out,
        X2Out,
        S3Out,
        S4Out,
        S5Out,
        S6Out,
        S8Out,
        X8Out,
        LedInLight,
        LedX1Light,
        LedX2Light,
        LedS3Light,
        LedS4Light,
        LedS5Light,
        LedS6Light,
        LedS8Light,
        LedX8Light,
        _4XFastButton,
        MuteButton,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobRotate = 0,
        KnobSlip = 1,
        KnobShuffle = 2,
        KnobSkip = 3,
        KnobPw = 4,
        NumKnobs,
    };
    
    enum {
        Switch_4X_Fast = 0,
        SwitchMute = 1,
        NumSwitches,
    };
    
    enum {
        InputClk_In = 0,
        InputResync = 1,
        InputRotate_Jack = 2,
        InputSlip_Jack = 3,
        InputShuffle_Jack = 4,
        InputSkip_Jack = 5,
        InputPw_Jack = 6,
        Input_4X_Fast_Jack = 7,
        InputMute_Jack = 8,
        NumInJacks,
    };
    
    enum {
        OutputX1 = 0,
        OutputX2 = 1,
        OutputS3 = 2,
        OutputS4 = 3,
        OutputS5 = 4,
        OutputS6 = 5,
        OutputS8 = 6,
        OutputX8 = 7,
        NumOutJacks,
    };
    
    enum {
        LedLed_In = 0,
        LedLed_X1 = 1,
        LedLed_X2 = 2,
        LedLed_S3 = 3,
        LedLed_S4 = 4,
        LedLed_S5 = 5,
        LedLed_S6 = 6,
        LedLed_S8 = 7,
        LedLed_X8 = 8,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
