#pragma once
#include <cstdint>

struct PanelDef {
	static constexpr uint32_t NumAudioIn = 2;
	static constexpr uint32_t NumAudioOut = 2;
	static constexpr uint32_t NumDACOut = 2;
	static constexpr uint32_t NumPot = 8;
	static constexpr uint32_t NumCVIn = 4;
	static constexpr uint32_t NumGateIn = 3;
	static constexpr uint32_t NumGateOut = 1;
	static constexpr uint32_t NumMetaCV = 1;
	static constexpr uint32_t NumRgbButton = 2;
};
