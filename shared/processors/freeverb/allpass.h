#pragma once
#include "sys/alloc_buffer.hh"
#include "util/interp_array.hh"
#include "util/math.hh"
#include <array>

template<unsigned long MAX_LENGTH>
class AllPass {
public:
	AllPass()
	{
		for (unsigned long i = 0; i < MAX_LENGTH; i++) {
			(*buffer)[i] = 0;
		}
	}

	void setLength(unsigned long length)
	{
		while (length >= MAX_LENGTH)
			length -= MAX_LENGTH;

		if (length == last_requested_length)
			return;

		last_requested_length = length;

		if (is_fading) {
			queued_fade_length = length;
			fade_is_queued = true;
			return;
		}

		_start_fade(length);
	}

	bool is_crossfading()
	{
		return is_fading;
	}

private:
	void _start_fade(unsigned long length)
	{
		if (length > write_idx)
			fade_idx = write_idx + MAX_LENGTH - length;
		else
			fade_idx = write_idx - length;

		fade_phase = 0.0f;
		is_fading = true;
	}

	void _update_fade()
	{
		fade_phase += fade_speed;
		if (fade_phase >= 1.0f) {
			read_idx = fade_idx;
			if (fade_is_queued) {
				_start_fade(queued_fade_length);
				fade_is_queued = false;
			} else {
				is_fading = false;
			}
		}
	}

public:
	float process(float input)
	{
		float bufout = 0;

		if (is_fading) {
			bufout = MathTools::interpolate((*buffer)[read_idx], (*buffer)[fade_idx], fade_phase);
			_update_fade();
		} else {
			bufout = (*buffer)[read_idx];
		}

		(*buffer)[write_idx] = input + (bufout * feedback);

		if (++write_idx >= MAX_LENGTH)
			write_idx = 0;

		if (++read_idx >= MAX_LENGTH)
			read_idx = 0;

		if (++fade_idx >= MAX_LENGTH)
			fade_idx = 0;

		float output = -input + bufout;
		return output;
	}

	void setFeedback(float val)
	{
		feedback = val;
	}

	void setFadeSpeed(float val)
	{
		fade_speed = MathTools::constrain(val, 0.0000001f, 1.0f);
	}

private:
	using BufferType = BigAlloc<std::array<float, MAX_LENGTH>>;
	BufferType *buffer = new BufferType;
	float feedback = 0;

	unsigned long read_idx = 0;
	unsigned long write_idx = 0;
	unsigned long fade_idx = 0;
	unsigned long last_requested_length = 0;
	unsigned long queued_fade_length = 0;
	bool fade_is_queued = false;
	bool is_fading = false;
	float fade_phase = 0;
	float fade_speed = 0.001f;
};
