#pragma once
#include "sys/alloc_buffer.hh"
#include "util/interp_array.hh"
#include "util/math.hh"
#include <array>

// Todo: How to allow usage of different types of buffers? Pass reference? CRTP for read/write functions?
template<typename DataType, unsigned long MAX_LENGTH>
class FadeLoop {
public:
	FadeLoop()
	{
		for (unsigned long i = 0; i < MAX_LENGTH; i++) {
			(*buffer)[i] = 0;
		}
	}

	DataType read()
	{
		DataType bufout;

		if (is_fading) {
			bufout = MathTools::interpolate((*buffer)[read_idx], (*buffer)[fade_idx], fade_phase);
			_update_fade();
			if (++fade_idx >= MAX_LENGTH)
				fade_idx = 0;
		} else {
			bufout = (*buffer)[read_idx];
		}
		if (++read_idx >= MAX_LENGTH)
			read_idx = 0;
		return bufout;
	}

	void write(DataType val)
	{
		(*buffer)[write_idx] = val;
		if (++write_idx >= MAX_LENGTH)
			write_idx = 0;
	}

	void set_fade_speed(float val)
	{
		fade_speed = MathTools::constrain(val, 0.0000001f, 1.0f);
	}

	void change_delay(unsigned long length)
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

private:
	using BufferType = BigAlloc<std::array<DataType, MAX_LENGTH>>;
	BufferType *buffer = new BufferType;

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

