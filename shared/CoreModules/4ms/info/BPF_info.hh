#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct BPFInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"BPF"};
    static constexpr std::string_view description{"Band-Pass Filter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/BPF-artwork.svg"};

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.53), "Cutoff", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.22), "Q", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(214.97), "CV", ""},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(264.07), "Input", ""},
		AnalogJackOutput4ms{to_mm<72>(28.63), to_mm<72>(312.29), "Out", ""},
		LatchingButtonMonoLight{to_mm<72>(28.65), to_mm<72>(166.04), "Mode", ""},
}};

    enum class Elem {
        CutoffKnob,
        QKnob,
        CvIn,
        InputIn,
        OutOut,
        ModeButton,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobCutoff = 0,
        KnobQ = 1,
    };
    
    enum {
        SwitchMode = 0,
    };
    
    enum {
        InputCv = 0,
        InputInput = 1,
    };
    
    enum {
        OutputOut = 0,
    };
    
};
} // namespace MetaModule
