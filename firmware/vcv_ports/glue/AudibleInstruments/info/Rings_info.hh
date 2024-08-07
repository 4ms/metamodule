#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct RingsInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Rings"};
    static constexpr std::string_view description{"Resonance Module"};
    static constexpr uint32_t width_hp = 14;
    static constexpr std::string_view svg_filename{"res/modules/Rings_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Rings.png"};

    using enum Coords;

    static constexpr std::array<Element, 24> Elements{{
		Toggle3posHoriz{{to_mm<72>(21.2), to_mm<72>(45.705), Center, "Polyphony Select Switch", ""}, {"1", "2", "4"}},
		Toggle3posHoriz{{to_mm<72>(179.65), to_mm<72>(45.705), Center, "Resonator Mode Switch", ""}, {"Modal", "Symp", "Mod"}},
		WhiteLargeKnob{{to_mm<72>(53.65), to_mm<72>(94.75), Center, "Frequency", ""}, 0.5f},
		WhiteLargeKnob{{to_mm<72>(147.21), to_mm<72>(94.75), Center, "Structure", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(167.89), to_mm<72>(171.86), Center, "Brightness", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(100.4), to_mm<72>(171.86), Center, "Damping", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(32.92), to_mm<72>(171.86), Center, "Position", ""}, 0.5f},
		WhiteSmallKnob{{to_mm<72>(26.69), to_mm<72>(228.56), Center, "Br Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(63.55), to_mm<72>(228.56), Center, "Frq Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(100.41), to_mm<72>(228.56), Center, "Dmp Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(137.28), to_mm<72>(228.56), Center, "Str Atten", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(174.14), to_mm<72>(228.56), Center, "Pos Atten", ""}, 0.0f},
		AnalogJackInput4ms{{to_mm<72>(26.67), to_mm<72>(273.49), Center, "Brightness CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(63.54), to_mm<72>(273.49), Center, "Frequency CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(100.4), to_mm<72>(273.49), Center, "Damping CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(137.27), to_mm<72>(273.49), Center, "Structure CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(174.13), to_mm<72>(273.49), Center, "Position CV", ""}},
		GateJackOutput4ms{{to_mm<72>(26.67), to_mm<72>(314.88), Center, "Strum", ""}},
		AnalogJackInput4ms{{to_mm<72>(63.54), to_mm<72>(314.88), Center, "V/OCT", ""}},
		AnalogJackInput4ms{{to_mm<72>(100.4), to_mm<72>(314.88), Center, "IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(137.27), to_mm<72>(314.88), Center, "Odd", ""}},
		AnalogJackOutput4ms{{to_mm<72>(174.13), to_mm<72>(314.88), Center, "Even", ""}},
		RedGreenLight{{to_mm<72>(179.65), to_mm<72>(64.0), Center, "Res Mode Light", ""}},
		RedGreenLight{{to_mm<72>(21.2), to_mm<72>(64.0), Center, "Polyphony Light", ""}},
}};

    enum class Elem {
        PolyphonySelectSwitch,
        ResonatorModeSwitch,
        FrequencyKnob,
        StructureKnob,
        BrightnessKnob,
        DampingKnob,
        PositionKnob,
        BrAttenKnob,
        FrqAttenKnob,
        DmpAttenKnob,
        StrAttenKnob,
        PosAttenKnob,
        BrightnessCvIn,
        FrequencyCvIn,
        DampingCvIn,
        StructureCvIn,
        PositionCvIn,
        StrumOut,
        V_OctIn,
        In,
        OddOut,
        EvenOut,
        ResModeLight,
        PolyphonyLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobFrequency, 
        KnobStructure, 
        KnobBrightness, 
        KnobDamping, 
        KnobPosition, 
        KnobBr_Atten, 
        KnobFrq_Atten, 
        KnobDmp_Atten, 
        KnobStr_Atten, 
        KnobPos_Atten, 
        NumKnobs,
    };
    
    enum {
        SwitchPolyphony_Select_Switch, 
        SwitchResonator_Mode_Switch, 
        NumSwitches,
    };
    
    enum {
        InputBrightness_Cv, 
        InputFrequency_Cv, 
        InputDamping_Cv, 
        InputStructure_Cv, 
        InputPosition_Cv, 
        InputV_Oct, 
        InputIn, 
        NumInJacks,
    };
    
    enum {
        OutputStrum, 
        OutputOdd, 
        OutputEven, 
        NumOutJacks,
    };
    
    enum {
        LedRes_Mode_Light, 
        LedPolyphony_Light, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
