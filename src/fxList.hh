#pragma once
#include "processors/audio_processor.hh"

class FXList {
public:
	FXList();
	AudioProcessor *operator[](unsigned int fxnum);
	static constexpr int NumFX = 5;

private:
	AudioProcessor *fxList[NumFX];

public:
	using const_fxlist_iterator = AudioProcessor *;
	const const_fxlist_iterator begin() const { return fxList[0]; }
	const const_fxlist_iterator end() const { return fxList[NumFX - 1]; }
};

