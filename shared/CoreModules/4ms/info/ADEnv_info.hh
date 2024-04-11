#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ADEnvInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"ADEnv"};
    static constexpr std::string_view description{"Attack Decay Envelope"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/ADEnv_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/ADEnv.png"};

    using enum Coords;

    static constexpr std::array<Element, 12> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(31.85), to_mm<72>(47.96), Center, "Attack", ""}},
		Davies1900hBlackKnob{{to_mm<72>(83.49), to_mm<72>(47.96), Center, "Decay", ""}},
		Davies1900hBlackKnob{{to_mm<72>(31.96), to_mm<72>(104.94), Center, "A Shape", ""}},
		Davies1900hBlackKnob{{to_mm<72>(83.49), to_mm<72>(104.94), Center, "D Shape", ""}},
		GateJackInput4ms{{to_mm<72>(32.1), to_mm<72>(167.36), Center, "Gate", ""}},
		AnalogJackInput4ms{{to_mm<72>(83.63), to_mm<72>(167.36), Center, "Decay CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(32.1), to_mm<72>(214.57), Center, "Attack CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(83.63), to_mm<72>(214.57), Center, "D Shape CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(32.1), to_mm<72>(263.64), Center, "A Shape CV", ""}},
		GateJackOutput4ms{{to_mm<72>(83.63), to_mm<72>(263.67), Center, "EOD", ""}},
		GateJackOutput4ms{{to_mm<72>(32.1), to_mm<72>(311.23), Center, "EOA", ""}},
		AnalogJackOutput4ms{{to_mm<72>(83.63), to_mm<72>(311.26), Center, "Out", ""}},
}};

    enum class Elem {
        AttackKnob,
        DecayKnob,
        AShapeKnob,
        DShapeKnob,
        GateIn,
        DecayCvIn,
        AttackCvIn,
        DShapeCvIn,
        AShapeCvIn,
        EodOut,
        EoaOut,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobAttack = 0,
        KnobDecay = 1,
        KnobA_Shape = 2,
        KnobD_Shape = 3,
        NumKnobs,
    };
    
    
    enum {
        InputGate = 0,
        InputDecay_Cv = 1,
        InputAttack_Cv = 2,
        InputD_Shape_Cv = 3,
        InputA_Shape_Cv = 4,
        NumInJacks,
    };
    
    enum {
        OutputEod = 0,
        OutputEoa = 1,
        OutputOut = 2,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
