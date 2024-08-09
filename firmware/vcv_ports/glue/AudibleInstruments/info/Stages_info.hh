#pragma once
#include "CoreModules/AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct StagesInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Stages"};
    static constexpr std::string_view description{"Segment Generator"};
    static constexpr uint32_t width_hp = 14;
    static constexpr std::string_view svg_filename{"res/modules/Stages_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Stages.png"};

    using enum Coords;

    static constexpr std::array<Element, 48> Elements{{
		Trimpot{{to_mm<72>(19.38), to_mm<72>(48.44), Center, "Ch1 Shape", ""}, 0.0f},
		Trimpot{{to_mm<72>(51.8), to_mm<72>(48.44), Center, "Ch2 Shape", ""}, 0.0f},
		Trimpot{{to_mm<72>(84.23), to_mm<72>(48.44), Center, "Ch3 Shape", ""}, 0.0f},
		Trimpot{{to_mm<72>(116.72), to_mm<72>(48.44), Center, "Ch4 Shape", ""}, 0.0f},
		Trimpot{{to_mm<72>(149.15), to_mm<72>(48.44), Center, "Ch5 Shape", ""}, 0.0f},
		Trimpot{{to_mm<72>(181.58), to_mm<72>(48.44), Center, "Ch6 Shape", ""}, 0.0f},
		SmallButton{{to_mm<72>(19.38), to_mm<72>(99.32), Center, "Ch1 Type", ""}},
		SmallButton{{to_mm<72>(51.81), to_mm<72>(99.32), Center, "Ch2 Type", ""}},
		SmallButton{{to_mm<72>(84.24), to_mm<72>(99.32), Center, "Ch3 Type", ""}},
		SmallButton{{to_mm<72>(116.73), to_mm<72>(99.32), Center, "Ch4 Type", ""}},
		SmallButton{{to_mm<72>(149.16), to_mm<72>(99.32), Center, "Ch5 Type", ""}},
		SmallButton{{to_mm<72>(181.59), to_mm<72>(99.32), Center, "Ch6 Type", ""}},
		GreenHandleSlider{{to_mm<72>(19.325), to_mm<72>(160.22), Center, "Ch1 Level Slider", ""}, 0.5f},
		GreenHandleSlider{{to_mm<72>(51.795), to_mm<72>(160.22), Center, "Ch2 Level Slider", ""}, 0.5f},
		GreenHandleSlider{{to_mm<72>(84.265), to_mm<72>(160.22), Center, "Ch3 Level Slider", ""}, 0.5f},
		GreenHandleSlider{{to_mm<72>(116.675), to_mm<72>(160.22), Center, "Ch4 Level Slider", ""}, 0.5f},
		GreenHandleSlider{{to_mm<72>(149.135), to_mm<72>(160.22), Center, "Ch5 Level Slider", ""}, 0.5f},
		GreenHandleSlider{{to_mm<72>(181.605), to_mm<72>(160.22), Center, "Ch6 Level Slider", ""}, 0.5f},
		AnalogJackInput4ms{{to_mm<72>(19.39), to_mm<72>(232.12), Center, "Ch1 Level CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(51.82), to_mm<72>(232.12), Center, "Ch2 Level CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(84.25), to_mm<72>(232.12), Center, "Ch3 Level CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(116.74), to_mm<72>(232.12), Center, "Ch4 Level CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(149.17), to_mm<72>(232.12), Center, "Ch5 Level CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(181.6), to_mm<72>(232.12), Center, "Ch6 Level CV", ""}},
		GateJackInput4ms{{to_mm<72>(19.39), to_mm<72>(273.5), Center, "Ch1 Gate In", ""}},
		GateJackInput4ms{{to_mm<72>(51.82), to_mm<72>(273.5), Center, "Ch2 Gate In", ""}},
		GateJackInput4ms{{to_mm<72>(84.25), to_mm<72>(273.5), Center, "Ch3 Gate In", ""}},
		GateJackInput4ms{{to_mm<72>(116.74), to_mm<72>(273.5), Center, "Ch4 Gate In", ""}},
		GateJackInput4ms{{to_mm<72>(149.17), to_mm<72>(273.5), Center, "Ch5 Gate In", ""}},
		GateJackInput4ms{{to_mm<72>(181.6), to_mm<72>(273.5), Center, "Ch6 Gate In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(19.39), to_mm<72>(314.89), Center, "Ch1 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(51.82), to_mm<72>(314.89), Center, "Ch2 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(84.25), to_mm<72>(314.89), Center, "Ch3 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(116.74), to_mm<72>(314.89), Center, "Ch4 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(149.17), to_mm<72>(314.89), Center, "Ch5 Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(181.6), to_mm<72>(314.89), Center, "Ch6 Out", ""}},
		GreenRedLight{{to_mm<72>(19.33), to_mm<72>(80.26), Center, "Ch1 Type Light", ""}},
		GreenRedLight{{to_mm<72>(51.82), to_mm<72>(80.19), Center, "Ch2 Type Light", ""}},
		GreenRedLight{{to_mm<72>(84.25), to_mm<72>(80.19), Center, "Ch3 Type Light", ""}},
		GreenRedLight{{to_mm<72>(116.68), to_mm<72>(80.19), Center, "Ch4 Type Light", ""}},
		GreenRedLight{{to_mm<72>(149.17), to_mm<72>(80.19), Center, "Ch5 Type Light", ""}},
		GreenRedLight{{to_mm<72>(181.6), to_mm<72>(80.19), Center, "Ch6 Type Light", ""}},
		GreenLight{{to_mm<72>(10.88), to_mm<72>(296.89), Center, "Ch1 Light", ""}},
		GreenLight{{to_mm<72>(43.31), to_mm<72>(296.89), Center, "Ch2 Light", ""}},
		GreenLight{{to_mm<72>(75.74), to_mm<72>(296.89), Center, "Ch3 Light", ""}},
		GreenLight{{to_mm<72>(108.23), to_mm<72>(296.89), Center, "Ch4 Light", ""}},
		GreenLight{{to_mm<72>(140.66), to_mm<72>(296.89), Center, "Ch5 Light", ""}},
		GreenLight{{to_mm<72>(173.09), to_mm<72>(296.89), Center, "Ch6 Light", ""}},
}};

    enum class Elem {
        Ch1ShapeKnob,
        Ch2ShapeKnob,
        Ch3ShapeKnob,
        Ch4ShapeKnob,
        Ch5ShapeKnob,
        Ch6ShapeKnob,
        Ch1TypeButton,
        Ch2TypeButton,
        Ch3TypeButton,
        Ch4TypeButton,
        Ch5TypeButton,
        Ch6TypeButton,
        Ch1LevelSlider,
        Ch2LevelSlider,
        Ch3LevelSlider,
        Ch4LevelSlider,
        Ch5LevelSlider,
        Ch6LevelSlider,
        Ch1LevelCvIn,
        Ch2LevelCvIn,
        Ch3LevelCvIn,
        Ch4LevelCvIn,
        Ch5LevelCvIn,
        Ch6LevelCvIn,
        Ch1GateIn,
        Ch2GateIn,
        Ch3GateIn,
        Ch4GateIn,
        Ch5GateIn,
        Ch6GateIn,
        Ch1Out,
        Ch2Out,
        Ch3Out,
        Ch4Out,
        Ch5Out,
        Ch6Out,
        Ch1TypeLight,
        Ch2TypeLight,
        Ch3TypeLight,
        Ch4TypeLight,
        Ch5TypeLight,
        Ch6TypeLight,
        Ch1Light,
        Ch2Light,
        Ch3Light,
        Ch4Light,
        Ch5Light,
        Ch6Light,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1_Shape, 
        KnobCh2_Shape, 
        KnobCh3_Shape, 
        KnobCh4_Shape, 
        KnobCh5_Shape, 
        KnobCh6_Shape, 
        KnobCh1_Level_Slider, 
        KnobCh2_Level_Slider, 
        KnobCh3_Level_Slider, 
        KnobCh4_Level_Slider, 
        KnobCh5_Level_Slider, 
        KnobCh6_Level_Slider, 
        NumKnobs,
    };
    
    enum {
        SwitchCh1_Type, 
        SwitchCh2_Type, 
        SwitchCh3_Type, 
        SwitchCh4_Type, 
        SwitchCh5_Type, 
        SwitchCh6_Type, 
        NumSwitches,
    };
    
    enum {
        InputCh1_Level_Cv, 
        InputCh2_Level_Cv, 
        InputCh3_Level_Cv, 
        InputCh4_Level_Cv, 
        InputCh5_Level_Cv, 
        InputCh6_Level_Cv, 
        InputCh1_Gate_In, 
        InputCh2_Gate_In, 
        InputCh3_Gate_In, 
        InputCh4_Gate_In, 
        InputCh5_Gate_In, 
        InputCh6_Gate_In, 
        NumInJacks,
    };
    
    enum {
        OutputCh1_Out, 
        OutputCh2_Out, 
        OutputCh3_Out, 
        OutputCh4_Out, 
        OutputCh5_Out, 
        OutputCh6_Out, 
        NumOutJacks,
    };
    
    enum {
        LedCh1_Type_Light, 
        LedCh2_Type_Light, 
        LedCh3_Type_Light, 
        LedCh4_Type_Light, 
        LedCh5_Type_Light, 
        LedCh6_Type_Light, 
        LedCh1_Light, 
        LedCh2_Light, 
        LedCh3_Light, 
        LedCh4_Light, 
        LedCh5_Light, 
        LedCh6_Light, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
