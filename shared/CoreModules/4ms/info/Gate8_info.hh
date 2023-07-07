#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct Gate8Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Gate8"};
    static constexpr std::string_view description{"8 Step Gate Sequencer"};
    static constexpr uint32_t width_hp = 8;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Gate8-artwork.svg"};

    static constexpr std::array<Element, 12> Elements{{
		GateJackInput4ms{to_mm<72>(32.07), to_mm<72>(262.57), "Clock", ""},
		GateJackInput4ms{to_mm<72>(83.61), to_mm<72>(262.57), "Reset", ""},
		GateJackOutput4ms{to_mm<72>(32.07), to_mm<72>(310.16), "End", ""},
		GateJackOutput4ms{to_mm<72>(83.61), to_mm<72>(310.16), "Out", ""},
		LatchingButtonMonoLight{to_mm<72>(31.96), to_mm<72>(45.78), "Step 1", ""},
		LatchingButtonMonoLight{to_mm<72>(83.49), to_mm<72>(45.78), "Step 2", ""},
		LatchingButtonMonoLight{to_mm<72>(31.96), to_mm<72>(88.3), "Step 3", ""},
		LatchingButtonMonoLight{to_mm<72>(83.49), to_mm<72>(88.3), "Step 4", ""},
		LatchingButtonMonoLight{to_mm<72>(31.96), to_mm<72>(130.82), "Step 5", ""},
		LatchingButtonMonoLight{to_mm<72>(83.49), to_mm<72>(130.82), "Step 6", ""},
		LatchingButtonMonoLight{to_mm<72>(31.96), to_mm<72>(173.25), "Step 7", ""},
		LatchingButtonMonoLight{to_mm<72>(83.49), to_mm<72>(173.34), "Step 8", ""},
}};

    enum class Elem {
        ClockIn,
        ResetIn,
        EndOut,
        Out,
        Step1Button,
        Step2Button,
        Step3Button,
        Step4Button,
        Step5Button,
        Step6Button,
        Step7Button,
        Step8Button,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    
    enum {
        SwitchStep_1 = 0,
        SwitchStep_2 = 1,
        SwitchStep_3 = 2,
        SwitchStep_4 = 3,
        SwitchStep_5 = 4,
        SwitchStep_6 = 5,
        SwitchStep_7 = 6,
        SwitchStep_8 = 7,
        NumSwitches,
    };
    
    enum {
        InputClock = 0,
        InputReset = 1,
        NumInJacks,
    };
    
    enum {
        OutputEnd = 0,
        OutputOut = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
