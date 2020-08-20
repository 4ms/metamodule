#pragma once
#include <stdint.h>

struct AudioProcessor {
	virtual float update(float in) = 0;
	virtual void set_samplerate(float sr) = 0;
	virtual void set_param(int param_id, float val) = 0;
};

