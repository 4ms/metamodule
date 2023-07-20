#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct StMixInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"StMix"};
    static constexpr std::string_view description{"Stereo Mixer"};
    static constexpr uint32_t width_hp = 18;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/StMix-artwork.svg"};

    static constexpr std::array<Element, 18> Elements{{
		Davies1900hBlackKnob{to_mm<72>(35.29), to_mm<72>(58.14), "Level 1", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(98.25), to_mm<72>(58.14), "Level 2", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(161.2), to_mm<72>(58.14), "Level 3", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(224.16), to_mm<72>(58.14), "Level 4", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(35.29), to_mm<72>(150.52), "Pan 1", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(98.25), to_mm<72>(150.3), "Pan 2", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(161.1), to_mm<72>(150.46), "Pan 3", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(224.16), to_mm<72>(150.3), "Pan 4", "", 0, 0, 1, 0.5f},
		AnalogJackInput4ms{to_mm<72>(34.91), to_mm<72>(222.82), "In 1 L", ""},
		AnalogJackInput4ms{to_mm<72>(34.91), to_mm<72>(271.92), "In 1 R", ""},
		AnalogJackInput4ms{to_mm<72>(97.94), to_mm<72>(222.82), "In 2 L", ""},
		AnalogJackInput4ms{to_mm<72>(97.94), to_mm<72>(271.92), "In 2 R", ""},
		AnalogJackInput4ms{to_mm<72>(160.97), to_mm<72>(222.82), "In 3 L", ""},
		AnalogJackInput4ms{to_mm<72>(160.97), to_mm<72>(271.92), "In 3 R", ""},
		AnalogJackInput4ms{to_mm<72>(224.01), to_mm<72>(222.82), "In 4 L", ""},
		AnalogJackInput4ms{to_mm<72>(224.01), to_mm<72>(271.92), "In 4 R", ""},
		AnalogJackOutput4ms{to_mm<72>(138.46), to_mm<72>(322.31), "L", ""},
		AnalogJackOutput4ms{to_mm<72>(206.48), to_mm<72>(322.31), "R", ""},
}};

    enum class Elem {
        Level1Knob,
        Level2Knob,
        Level3Knob,
        Level4Knob,
        Pan1Knob,
        Pan2Knob,
        Pan3Knob,
        Pan4Knob,
        In1LIn,
        In1RIn,
        In2LIn,
        In2RIn,
        In3LIn,
        In3RIn,
        In4LIn,
        In4RIn,
        LOut,
        ROut,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobLevel_1 = 0,
        KnobLevel_2 = 1,
        KnobLevel_3 = 2,
        KnobLevel_4 = 3,
        KnobPan_1 = 4,
        KnobPan_2 = 5,
        KnobPan_3 = 6,
        KnobPan_4 = 7,
        NumKnobs,
    };
    
    
    enum {
        InputIn_1_L = 0,
        InputIn_1_R = 1,
        InputIn_2_L = 2,
        InputIn_2_R = 3,
        InputIn_3_L = 4,
        InputIn_3_R = 5,
        InputIn_4_L = 6,
        InputIn_4_R = 7,
        NumInJacks,
    };
    
    enum {
        OutputL = 0,
        OutputR = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
