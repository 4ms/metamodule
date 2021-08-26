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
	static constexpr uint32_t NumMetaRgbButton = 0;

	static constexpr int NumKnobs = NumPot;
	static constexpr int NumOutJacks = NumAudioIn + NumCVIn + NumGateIn;
	static constexpr int NumInJacks = NumAudioOut + NumDACOut + NumGateOut;
	// User-facing out jacks, like "Audio Out 3", is an input jack as seen by other virtual modules
	static constexpr int NumUserFacingOutJacks = NumInJacks;
	// User-facing in jacks, like "Audio In 1", is an output jack as seen by other virtual modules
	static constexpr int NumUserFacingInJacks = NumOutJacks;
};
