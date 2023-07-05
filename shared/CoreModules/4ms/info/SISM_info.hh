#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct SISMInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"SISM"};
    static constexpr std::string_view description{"Shifting Inverting Signal Mingler"};
    static constexpr uint32_t width_hp = 12;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/SISM-artwork.svg"};

    static constexpr std::array<Element, 34> Elements{{
		Knob9mm{to_mm<72>(64.25), to_mm<72>(46.64), "Scale 1", "", 0, 0, 1, 1.0f},
		Knob9mm{to_mm<72>(107.45), to_mm<72>(46.64), "Shift 1", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(64.25), to_mm<72>(111.44), "Scale 2", "", 0, 0, 1, 1.0f},
		Knob9mm{to_mm<72>(107.45), to_mm<72>(111.44), "Shift 2", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(64.25), to_mm<72>(176.24), "Scale 3", "", 0, 0, 1, 1.0f},
		Knob9mm{to_mm<72>(107.45), to_mm<72>(176.24), "Shift 3", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(64.25), to_mm<72>(241.04), "Scale 4", "", 0, 0, 1, 1.0f},
		Knob9mm{to_mm<72>(107.45), to_mm<72>(241.04), "Shift 4", "", 0, 0, 1, 0.5f},
		AnalogJackInput4ms{to_mm<72>(21.77), to_mm<72>(52.84), "In 1", ""},
		AnalogJackInput4ms{to_mm<72>(21.77), to_mm<72>(117.64), "In 2", ""},
		AnalogJackInput4ms{to_mm<72>(21.77), to_mm<72>(182.44), "In 3", ""},
		AnalogJackInput4ms{to_mm<72>(21.77), to_mm<72>(247.24), "In 4", ""},
		AnalogJackOutput4ms{to_mm<72>(150.52), to_mm<72>(52.9), "Out 1", ""},
		AnalogJackOutput4ms{to_mm<72>(150.52), to_mm<72>(117.7), "Out 2", ""},
		AnalogJackOutput4ms{to_mm<72>(150.52), to_mm<72>(182.5), "Out 3", ""},
		AnalogJackOutput4ms{to_mm<72>(150.52), to_mm<72>(247.3), "Out 4", ""},
		AnalogJackOutput4ms{to_mm<72>(21.1), to_mm<72>(312.16), "+ Slice", ""},
		AnalogJackOutput4ms{to_mm<72>(64.25), to_mm<72>(312.16), "- Slice", ""},
		AnalogJackOutput4ms{to_mm<72>(107.45), to_mm<72>(312.16), "Mix (SW)", ""},
		AnalogJackOutput4ms{to_mm<72>(150.7), to_mm<72>(312.16), "Mix", ""},
		RedGreenBlueLight{to_mm<72>(146.69), to_mm<72>(29.5), "LED - 1", ""},
		RedGreenBlueLight{to_mm<72>(158.21), to_mm<72>(29.5), "LED + 1", ""},
		RedGreenBlueLight{to_mm<72>(144.99), to_mm<72>(93.58), "LED - 2", ""},
		RedGreenBlueLight{to_mm<72>(156.5), to_mm<72>(93.58), "LED + 2", ""},
		RedGreenBlueLight{to_mm<72>(145.02), to_mm<72>(158.45), "LED - 3", ""},
		RedGreenBlueLight{to_mm<72>(156.54), to_mm<72>(158.45), "LED + 3", ""},
		RedGreenBlueLight{to_mm<72>(145.11), to_mm<72>(223.33), "LED - 4", ""},
		RedGreenBlueLight{to_mm<72>(156.63), to_mm<72>(223.33), "LED + 4", ""},
		RedGreenBlueLight{to_mm<72>(20.92), to_mm<72>(289.03), "LED + Slice", ""},
		RedGreenBlueLight{to_mm<72>(64.26), to_mm<72>(288.6), "LED - Slice", ""},
		RedGreenBlueLight{to_mm<72>(102.32), to_mm<72>(289.18), "LED - Mix (SW)", ""},
		RedGreenBlueLight{to_mm<72>(113.66), to_mm<72>(289.18), "LED + Mix (SW)", ""},
		RedGreenBlueLight{to_mm<72>(145.66), to_mm<72>(289.03), "LED - Mix", ""},
		RedGreenBlueLight{to_mm<72>(157.0), to_mm<72>(289.03), "LED + Mix", ""},
}};

    enum class Elem {
        Scale1Knob,
        Shift1Knob,
        Scale2Knob,
        Shift2Knob,
        Scale3Knob,
        Shift3Knob,
        Scale4Knob,
        Shift4Knob,
        In1In,
        In2In,
        In3In,
        In4In,
        Out1Out,
        Out2Out,
        Out3Out,
        Out4Out,
        PSliceOut,
        NSliceOut,
        Mix_Sw_Out,
        MixOut,
        LedN1Light,
        LedP1Light,
        LedN2Light,
        LedP2Light,
        LedN3Light,
        LedP3Light,
        LedN4Light,
        LedP4Light,
        LedPSliceLight,
        LedNSliceLight,
        LedNMix_Sw_Light,
        LedPMix_Sw_Light,
        LedNMixLight,
        LedPMixLight,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobScale_1 = 0,
        KnobShift_1 = 1,
        KnobScale_2 = 2,
        KnobShift_2 = 3,
        KnobScale_3 = 4,
        KnobShift_3 = 5,
        KnobScale_4 = 6,
        KnobShift_4 = 7,
        NumKnobs,
    };
    
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
        InputIn_3 = 2,
        InputIn_4 = 3,
        NumInJacks,
    };
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
        OutputOut_3 = 2,
        OutputOut_4 = 3,
        OutputP_Slice = 4,
        OutputN_Slice = 5,
        OutputMix__Sw_ = 6,
        OutputMix = 7,
        NumOutJacks,
    };
    
    enum {
        LedLed_N_1 = 0,
        LedLed_P_1 = 1,
        LedLed_N_2 = 2,
        LedLed_P_2 = 3,
        LedLed_N_3 = 4,
        LedLed_P_3 = 5,
        LedLed_N_4 = 6,
        LedLed_P_4 = 7,
        LedLed_P_Slice = 8,
        LedLed_N_Slice = 9,
        LedLed_N_Mix__Sw_ = 10,
        LedLed_P_Mix__Sw_ = 11,
        LedLed_N_Mix = 12,
        LedLed_P_Mix = 13,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
