#pragma once
#include "CoreModules/AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct VeilsInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Veils"};
    static constexpr std::string_view description{"Quad VCA"};
    static constexpr uint32_t width_hp = 34;
    static constexpr std::string_view svg_filename{"res/modules/Veils_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Veils.png"};

    using enum Coords;

    static constexpr std::array<Element, 24> Elements{{
		WhiteMediumKnob{{to_mm<72>(27.26), to_mm<72>(69.39), Center, "Ch1 Gain", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(27.26), to_mm<72>(144.94), Center, "Ch2 Gain", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(27.26), to_mm<72>(220.48), Center, "Ch3 Gain", ""}, 0.5f},
		WhiteMediumKnob{{to_mm<72>(27.26), to_mm<72>(296.02), Center, "Ch4 Gain", ""}, 0.5f},
		Trimpot{{to_mm<72>(77.86), to_mm<72>(62.31), Center, "Ch1 Response", ""}, 0.0f},
		Trimpot{{to_mm<72>(77.86), to_mm<72>(137.85), Center, "Ch2 Response", ""}, 0.0f},
		Trimpot{{to_mm<72>(77.86), to_mm<72>(213.39), Center, "Ch3 Response", ""}, 0.0f},
		Trimpot{{to_mm<72>(77.86), to_mm<72>(288.94), Center, "Ch4 Response", ""}, 0.0f},
		AnalogJackInput4ms{{to_mm<72>(117.32), to_mm<72>(50.54), Center, "Ch1 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.32), to_mm<72>(126.09), Center, "Ch2 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.32), to_mm<72>(201.63), Center, "Ch3 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.32), to_mm<72>(277.17), Center, "Ch4 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.32), to_mm<72>(88.24), Center, "Ch1 CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.32), to_mm<72>(163.79), Center, "Ch2 CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.32), to_mm<72>(239.33), Center, "Ch3 CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.32), to_mm<72>(314.87), Center, "Ch4 CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(149.89), to_mm<72>(50.54), Center, "Ch1 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(149.89), to_mm<72>(126.09), Center, "Ch2 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(149.89), to_mm<72>(201.63), Center, "Ch3 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(149.89), to_mm<72>(277.17), Center, "Ch4 Out", ""}},
		GreenRedLight{{to_mm<72>(149.89), to_mm<72>(88.24), Center, "Ch1", ""}},
		GreenRedLight{{to_mm<72>(149.89), to_mm<72>(163.79), Center, "Ch2", ""}},
		GreenRedLight{{to_mm<72>(149.89), to_mm<72>(239.33), Center, "Ch3", ""}},
		GreenRedLight{{to_mm<72>(149.89), to_mm<72>(314.87), Center, "Ch4", ""}},
}};

    enum class Elem {
        Ch1GainKnob,
        Ch2GainKnob,
        Ch3GainKnob,
        Ch4GainKnob,
        Ch1ResponseKnob,
        Ch2ResponseKnob,
        Ch3ResponseKnob,
        Ch4ResponseKnob,
        Ch1In,
        Ch2In,
        Ch3In,
        Ch4In,
        Ch1CvIn,
        Ch2CvIn,
        Ch3CvIn,
        Ch4CvIn,
        Ch1Out,
        Ch2Out,
        Ch3Out,
        Ch4Out,
        Ch1Light,
        Ch2Light,
        Ch3Light,
        Ch4Light,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1_Gain, 
        KnobCh2_Gain, 
        KnobCh3_Gain, 
        KnobCh4_Gain, 
        KnobCh1_Response, 
        KnobCh2_Response, 
        KnobCh3_Response, 
        KnobCh4_Response, 
        NumKnobs,
    };
    
    
    enum {
        InputCh1_In, 
        InputCh2_In, 
        InputCh3_In, 
        InputCh4_In, 
        InputCh1_Cv, 
        InputCh2_Cv, 
        InputCh3_Cv, 
        InputCh4_Cv, 
        NumInJacks,
    };
    
    enum {
        OutputCh1_Out, 
        OutputCh2_Out, 
        OutputCh3_Out, 
        OutputCh4_Out, 
        NumOutJacks,
    };
    
    enum {
        LedCh1, 
        LedCh2, 
        LedCh3, 
        LedCh4, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
