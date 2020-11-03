#pragma once
#include "processors/audio_processor.hh"
#include "processors/bit_crush.h"
#include "processors/karplus.h"
#include "processors/lpf.h"
#include "processors/lpg.h"
#include "processors/reverb.h"
#include "processors/vca.h"
#include "processors/wavefold.h"

class FXList {
public:
	FXList();
	AudioProcessor *operator[](unsigned int fxnum);
	static constexpr int NumFX = 5;

private:
	AudioProcessor *fxList[NumFX];

	// LowPassFilter fx1;
	// VCA fx2;
	// Karplus fx3;
	// WaveFolder fx4;
	// BitCrusher fx5;
	 

public:
	using const_fxlist_iterator = AudioProcessor *;
	const const_fxlist_iterator begin() const { return fxList[0]; }
	const const_fxlist_iterator end() const { return fxList[NumFX - 1]; }
};

