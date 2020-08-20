#pragma once
#include "audio_processor.hh"

struct BitCrusher : public AudioProcessor {
	virtual float update(float in) { return 0;}
	virtual void set_samplerate(float sr) {}
	virtual void set_param(int param_id, float val) {}
};

