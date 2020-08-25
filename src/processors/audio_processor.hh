#pragma once

struct AudioProcessor {
	virtual float update(float in) = 0;
	virtual void set_samplerate(float sr) = 0;
	virtual void set_param(int param_id, float val) = 0;
	//virtual ~AudioProcessor() = 0;
};
