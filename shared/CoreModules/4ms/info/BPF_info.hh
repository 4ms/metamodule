#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct BPFInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"BPF"};
    static constexpr std::string_view description{"Band-Pass Filter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/BPF-artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.53), Center, "Cutoff", ""},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.22), Center, "Q", ""},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(214.97), Center, "CV", ""},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(264.07), Center, "Input", ""},
		AnalogJackOutput4ms{to_mm<72>(28.63), to_mm<72>(312.29), Center, "Out", ""},
		LatchingButtonMonoLight{to_mm<72>(28.65), to_mm<72>(166.04), Center, "Mode", ""},
}};

    enum class Elem {
        CutoffKnob,
        QKnob,
        CvIn,
        InputIn,
        Out,
        ModeButton,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCutoff = 0,
        KnobQ = 1,
        NumKnobs,
    };
    
    enum {
        SwitchMode = 0,
        NumSwitches,
    };
    
    enum {
        InputCv = 0,
        InputInput = 1,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
