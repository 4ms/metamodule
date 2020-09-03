#pragma once
#include "processors/audio_processor.hh"

class FXList {
public:
	FXList();

	AudioProcessor *operator[](unsigned int fxnum);

private:
	AudioProcessor *fxList[5];
	static constexpr int NumFX = sizeof(fxList) / sizeof(fxList[0]);
};

