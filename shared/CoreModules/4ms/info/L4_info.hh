#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct L4Info : ModuleInfoBase {
    static constexpr std::string_view slug{"L4"};
    static constexpr std::string_view description{"Listen Four"};
    static constexpr uint32_t width_hp = 10;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/L4-artwork.svg"};

    static constexpr std::array<Element, 24> Elements{{
		Knob9mm{to_mm<72>(62.33), to_mm<72>(46.17), "Pan 1", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(111.89), to_mm<72>(59.09), "Level 1", "", 0, 0, 1, 0.875f},
		Knob9mm{to_mm<72>(62.33), to_mm<72>(103.86), "Pan 2", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(111.89), to_mm<72>(116.69), "Level 2", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(111.89), to_mm<72>(174.29), "Level 3", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(111.89), to_mm<72>(232.15), "Level 4", "", 0, 0, 1, 0.875f},
		Knob9mm{to_mm<72>(23.27), to_mm<72>(318.85), "Headphone Level", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(71.7), to_mm<72>(302.94), "Main Level", "", 0, 0, 1, 0.875f},
		AnalogJackInput4ms{to_mm<72>(23.31), to_mm<72>(46.17), "In 1", ""},
		AnalogJackInput4ms{to_mm<72>(23.31), to_mm<72>(103.92), "In 2", ""},
		AnalogJackInput4ms{to_mm<72>(23.31), to_mm<72>(161.52), "In 3 L", ""},
		AnalogJackInput4ms{to_mm<72>(62.91), to_mm<72>(161.52), "In 3 R", ""},
		AnalogJackInput4ms{to_mm<72>(23.31), to_mm<72>(219.12), "In 4 L", ""},
		AnalogJackInput4ms{to_mm<72>(62.91), to_mm<72>(219.12), "In 4 R", ""},
		AnalogJackOutput4ms{to_mm<72>(23.64), to_mm<72>(266.4), "Headphone Out", ""},
		AnalogJackOutput4ms{to_mm<72>(122.02), to_mm<72>(282.83), "Out Left", ""},
		AnalogJackOutput4ms{to_mm<72>(122.02), to_mm<72>(326.07), "Out Right", ""},
		RedGreenBlueLight{to_mm<72>(87.38), to_mm<72>(46.17), "Level 1 LED", ""},
		RedGreenBlueLight{to_mm<72>(87.38), to_mm<72>(105.8), "Level 2 LED", ""},
		RedGreenBlueLight{to_mm<72>(87.38), to_mm<72>(163.03), "Level 3 LED", ""},
		RedGreenBlueLight{to_mm<72>(87.38), to_mm<72>(221.73), "Level 4 LED", ""},
		RedGreenBlueLight{to_mm<72>(98.07), to_mm<72>(284.23), "Out L LED", ""},
		RedGreenBlueLight{to_mm<72>(98.07), to_mm<72>(316.53), "Out R LED", ""},
		Toggle2posHoriz{to_mm<72>(67.265), to_mm<72>(258.19), "Mod. | Line", ""},
}};

    enum class Elem {
        Pan1Knob,
        Level1Knob,
        Pan2Knob,
        Level2Knob,
        Level3Knob,
        Level4Knob,
        HeadphoneLevelKnob,
        MainLevelKnob,
        In1In,
        In2In,
        In3LIn,
        In3RIn,
        In4LIn,
        In4RIn,
        HeadphoneOut,
        OutLeftOut,
        OutRightOut,
        Level1LedLight,
        Level2LedLight,
        Level3LedLight,
        Level4LedLight,
        OutLLedLight,
        OutRLedLight,
        Mod__OR_LineSwitch,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobPan_1 = 0,
        KnobLevel_1 = 1,
        KnobPan_2 = 2,
        KnobLevel_2 = 3,
        KnobLevel_3 = 4,
        KnobLevel_4 = 5,
        KnobHeadphone_Level = 6,
        KnobMain_Level = 7,
        NumKnobs,
    };
    
    enum {
        SwitchMod___OR__Line = 0,
        NumSwitches,
    };
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
        InputIn_3_L = 2,
        InputIn_3_R = 3,
        InputIn_4_L = 4,
        InputIn_4_R = 5,
        NumInJacks,
    };
    
    enum {
        OutputHeadphone_Out = 0,
        OutputOut_Left = 1,
        OutputOut_Right = 2,
        NumOutJacks,
    };
    
    enum {
        LedLevel_1_Led = 0,
        LedLevel_2_Led = 1,
        LedLevel_3_Led = 2,
        LedLevel_4_Led = 3,
        LedOut_L_Led = 4,
        LedOut_R_Led = 5,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
