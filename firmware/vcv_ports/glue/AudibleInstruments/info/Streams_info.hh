#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct StreamsInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Streams"};
    static constexpr std::string_view description{"Dual Dynamics Gate"};
    static constexpr uint32_t width_hp = 12;
    static constexpr std::string_view svg_filename{"res/modules/Streams_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Streams.png"};

    using enum Coords;

    static constexpr std::array<Element, 27> Elements{{
		WhiteSmallKnob{{to_mm<72>(31.37), to_mm<72>(59.68), Center, "Ch1 Shape", ""}, 0.5f},
		WhiteSmallKnob{{to_mm<72>(31.37), to_mm<72>(126.3), Center, "Ch1 Mod", ""}, 0.5f},
		RedSmallKnob{{to_mm<72>(31.37), to_mm<72>(192.88), Center, "Ch1 Level Mod", ""}, 0.5f},
		Trimpot{{to_mm<72>(86.24), to_mm<72>(172.19), Center, "Ch1 Response", ""}, 0.0f},
		WhiteSmallKnob{{to_mm<72>(141.12), to_mm<72>(59.68), Center, "Ch2 Shape", ""}, 0.5f},
		WhiteSmallKnob{{to_mm<72>(141.12), to_mm<72>(126.3), Center, "Ch2 Mod", ""}, 0.5f},
		BlueSmallKnob{{to_mm<72>(141.12), to_mm<72>(192.88), Center, "Ch2 Level Mod", ""}, 0.5f},
		Trimpot{{to_mm<72>(86.24), to_mm<72>(213.58), Center, "Ch2 Response", ""}, 0.0f},
		SmallButton{{to_mm<72>(70.06), to_mm<72>(42.59), Center, "Ch1 Function", ""}},
		SmallButton{{to_mm<72>(102.43), to_mm<72>(42.59), Center, "Ch2 Function", ""}},
		SmallButton{{to_mm<72>(86.24), to_mm<72>(132.59), Center, "Meter", ""}},
		GateJackInput4ms{{to_mm<72>(24.11), to_mm<72>(273.87), Center, "Ch1 Excite", ""}},
		GateJackInput4ms{{to_mm<72>(65.52), to_mm<72>(273.87), Center, "Ch1 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(24.11), to_mm<72>(315.28), Center, "Ch1 Level CV", ""}},
		GateJackInput4ms{{to_mm<72>(148.35), to_mm<72>(273.87), Center, "Ch2 Excite", ""}},
		GateJackInput4ms{{to_mm<72>(106.94), to_mm<72>(273.78), Center, "Ch2 In", ""}},
		AnalogJackInput4ms{{to_mm<72>(148.35), to_mm<72>(315.28), Center, "Ch2 Level CV", ""}},
		GateJackOutput4ms{{to_mm<72>(65.52), to_mm<72>(315.28), Center, "Ch1 Out", ""}},
		GateJackOutput4ms{{to_mm<72>(106.94), to_mm<72>(315.28), Center, "Ch2 Out", ""}},
		GreenRedLight{{to_mm<72>(70.06), to_mm<72>(62.38), Center, "Ch1 Func1", ""}},
		GreenRedLight{{to_mm<72>(70.06), to_mm<72>(78.59), Center, "Ch1 Func2", ""}},
		GreenRedLight{{to_mm<72>(70.06), to_mm<72>(94.8), Center, "Ch1 Func3", ""}},
		GreenRedLight{{to_mm<72>(70.06), to_mm<72>(111.02), Center, "Ch1 Func4", ""}},
		GreenRedLight{{to_mm<72>(102.43), to_mm<72>(62.38), Center, "Ch2 Func1", ""}},
		GreenRedLight{{to_mm<72>(102.43), to_mm<72>(78.59), Center, "Ch2 Func2", ""}},
		GreenRedLight{{to_mm<72>(102.43), to_mm<72>(94.8), Center, "Ch2 Func3", ""}},
		GreenRedLight{{to_mm<72>(102.43), to_mm<72>(111.02), Center, "Ch2 Func4", ""}},
}};

    enum class Elem {
        Ch1ShapeKnob,
        Ch1ModKnob,
        Ch1LevelModKnob,
        Ch1ResponseKnob,
        Ch2ShapeKnob,
        Ch2ModKnob,
        Ch2LevelModKnob,
        Ch2ResponseKnob,
        Ch1FunctionButton,
        Ch2FunctionButton,
        MeterButton,
        Ch1ExciteIn,
        Ch1In,
        Ch1LevelCvIn,
        Ch2ExciteIn,
        Ch2In,
        Ch2LevelCvIn,
        Ch1Out,
        Ch2Out,
        Ch1Func1Light,
        Ch1Func2Light,
        Ch1Func3Light,
        Ch1Func4Light,
        Ch2Func1Light,
        Ch2Func2Light,
        Ch2Func3Light,
        Ch2Func4Light,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobCh1_Shape, 
        KnobCh1_Mod, 
        KnobCh1_Level_Mod, 
        KnobCh1_Response, 
        KnobCh2_Shape, 
        KnobCh2_Mod, 
        KnobCh2_Level_Mod, 
        KnobCh2_Response, 
        NumKnobs,
    };
    
    enum {
        SwitchCh1_Function, 
        SwitchCh2_Function, 
        SwitchMeter, 
        NumSwitches,
    };
    
    enum {
        InputCh1_Excite, 
        InputCh1_In, 
        InputCh1_Level_Cv, 
        InputCh2_Excite, 
        InputCh2_In, 
        InputCh2_Level_Cv, 
        NumInJacks,
    };
    
    enum {
        OutputCh1_Out, 
        OutputCh2_Out, 
        NumOutJacks,
    };
    
    enum {
        LedCh1_Func1, 
        LedCh1_Func2, 
        LedCh1_Func3, 
        LedCh1_Func4, 
        LedCh2_Func1, 
        LedCh2_Func2, 
        LedCh2_Func3, 
        LedCh2_Func4, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
