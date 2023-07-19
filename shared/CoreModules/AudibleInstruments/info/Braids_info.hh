#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{

struct BraidsInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Braids"};
	static constexpr std::string_view description{"Macro Oscillator"};
	static constexpr uint32_t width_hp = 16;
	static constexpr std::string_view svg_filename{"res/modules/AudibleInstruments/Braids.svg"};

    using enum Coords;

	static constexpr std::array<Element, 14> Elements{{
		Rogan2PSWhite{to_mm(19), to_mm(138), Center, "Fine", "Fine Freq"},
		Rogan2PSWhite{to_mm(97), to_mm(138), Center, "Coarse", "Coarse Freq"},
		Rogan2PSWhite{to_mm(176), to_mm(138), Center, "FM", "" },
		Rogan2PSGreen{to_mm(19), to_mm(217), Center, "Timbre", ""},
		Rogan2PSGreen{to_mm(97), to_mm(217), Center, "Modulation", ""},
		Rogan2PSRed{to_mm(176), to_mm(217), Center, "Color", ""},
		Rogan2SGray{to_mm(176), to_mm(59), Center, "Model", ""},
		PJ301MPortIn{to_mm(10), to_mm(316), Center, "Trigger", ""},
		PJ301MPortIn{to_mm(47), to_mm(316), Center, "Pitch", "Pitch (1V/oct)"},
		PJ301MPortIn{to_mm(84), to_mm(316), Center, "FM", ""},
		PJ301MPortIn{to_mm(122), to_mm(316), Center, "Timbre", ""},
		PJ301MPortIn{to_mm(160), to_mm(316), Center, "Color", ""},
		PJ301MPortOut{to_mm(205), to_mm(316), Center, "Out", ""},
		BraidsDisplay148x56{to_mm(14), to_mm(53), Center, "", ""},
	}};
};
} // namespace MetaModule
