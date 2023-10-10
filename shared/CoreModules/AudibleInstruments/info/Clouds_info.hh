#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{

struct CloudsInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Clouds"};
	static constexpr std::string_view description{"Texture Synthesizer"};
	static constexpr uint32_t width_hp = 18;
	static constexpr std::string_view svg_filename{"res/modules/AudibleInstruments/Clouds.svg"};

    using enum Coords;

	static constexpr std::array<Element, 26> Elements{{
		CKD6{to_mm(12), to_mm(43), TopLeft, "Freeze", ""},
		TL1105{to_mm(211), to_mm(50), TopLeft, "Mode", ""},
		TL1105{to_mm(239), to_mm(50), TopLeft, "Load", ""},

		MediumLight<GreenRedLight>{to_mm(82.5), to_mm(53), TopLeft, "Mix", ""},
		MediumLight<GreenRedLight>{to_mm(114.5), to_mm(53), TopLeft, "Pan", ""},
		MediumLight<GreenRedLight>{to_mm(146.0), to_mm(53), TopLeft, "Feedback", ""},
		MediumLight<GreenRedLight>{to_mm(177.5), to_mm(53), TopLeft, "Reverb", ""},

		Rogan3PSRed{to_mm(27), to_mm(93), TopLeft, "Position", ""},
		Rogan3PSGreen{to_mm(108), to_mm(93), TopLeft, "Size", ""},
		Rogan3PSWhite{to_mm(190), to_mm(93), TopLeft, "Pitch", ""},
		Rogan1PSRed{to_mm(14), to_mm(180), TopLeft, "In Gain", ""},
		Rogan1PSRed{to_mm(81), to_mm(180), TopLeft, "Density", ""},
		Rogan1PSGreen{to_mm(146), to_mm(180), TopLeft, "Texture", ""},
		Rogan1PSWhite{to_mm(213), to_mm(180), TopLeft, "Blend", ""},

		PJ301MPortIn{to_mm(15), to_mm(274), TopLeft, "Freeze", ""},
		PJ301MPortIn{to_mm(58), to_mm(274), TopLeft, "Trig", ""},
		PJ301MPortIn{to_mm(101), to_mm(274), TopLeft, "Position", ""},
		PJ301MPortIn{to_mm(144), to_mm(274), TopLeft, "Size", ""},
		PJ301MPortIn{to_mm(188), to_mm(274), TopLeft, "Pitch", ""},
		PJ301MPortIn{to_mm(230), to_mm(274), TopLeft, "Blend", ""},
		PJ301MPortIn{to_mm(15), to_mm(317), TopLeft, "In L", ""},
		PJ301MPortIn{to_mm(58), to_mm(317), TopLeft, "In R", ""},
		PJ301MPortIn{to_mm(101), to_mm(317), TopLeft, "Density", ""},
		PJ301MPortIn{to_mm(144), to_mm(317), TopLeft, "Texture", ""},
		PJ301MPortOut{to_mm(188), to_mm(317), TopLeft, "Out L", ""},
		PJ301MPortOut{to_mm(230), to_mm(317), TopLeft, "Out R", ""},
	}};
};
} // namespace MetaModule
