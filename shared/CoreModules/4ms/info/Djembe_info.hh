#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct DjembeInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Djembe"};
    static constexpr std::string_view description{"Djembe Drum Voice"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Djembe_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/Djembe.png"};

    using enum Coords;

    static constexpr std::array<Element, 10> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(31.96), to_mm<72>(57.97), Center, "Pitch", ""}},
		Davies1900hBlackKnob{{to_mm<72>(83.49), to_mm<72>(57.97), Center, "Sharpness", ""}},
		Davies1900hBlackKnob{{to_mm<72>(31.96), to_mm<72>(119.21), Center, "Hit", ""}},
		Davies1900hBlackKnob{{to_mm<72>(83.49), to_mm<72>(119.21), Center, "Strike Amt", ""}},
		AnalogJackInput4ms{{to_mm<72>(32.13), to_mm<72>(214.66), Center, "Pitch CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(83.32), to_mm<72>(214.66), Center, "Sharp CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(32.13), to_mm<72>(263.38), Center, "Hit CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(83.32), to_mm<72>(263.38), Center, "Strike CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(32.13), to_mm<72>(312.1), Center, "Trigger", ""}},
		AnalogJackOutput4ms{{to_mm<72>(83.32), to_mm<72>(312.1), Center, "Out", ""}},
}};

    enum class Elem {
        PitchKnob,
        SharpnessKnob,
        HitKnob,
        StrikeAmtKnob,
        PitchCvIn,
        SharpCvIn,
        HitCvIn,
        StrikeCvIn,
        TriggerIn,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobPitch = 0,
        KnobSharpness = 1,
        KnobHit = 2,
        KnobStrike_Amt = 3,
        NumKnobs,
    };
    
    
    enum {
        InputPitch_Cv = 0,
        InputSharp_Cv = 1,
        InputHit_Cv = 2,
        InputStrike_Cv = 3,
        InputTrigger = 4,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
