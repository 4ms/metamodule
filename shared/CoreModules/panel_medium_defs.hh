#pragma once
#include <cstdint>

struct PanelDef {
	static constexpr uint32_t NumAudioIn = 6;
	static constexpr uint32_t NumAudioOut = 8;
	static constexpr uint32_t NumDACOut = 0;
	static constexpr uint32_t NumPot = 12;
	static constexpr uint32_t NumCVIn = 0;
	static constexpr uint32_t NumGateIn = 2;
	static constexpr uint32_t NumGateOut = 2;
	static constexpr uint32_t NumMetaCV = 1;
	static constexpr uint32_t NumRgbButton = 0;
	static constexpr uint32_t NumMetaRgbButton = 1;
};
