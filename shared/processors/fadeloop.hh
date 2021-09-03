#pragma once
#include "sys/alloc_buffer.hh"
// #include "util/big_buffer.hh"
#include "util/math.hh"
#include <array>

template<typename BufferType>
class FadeLoopExt {
protected:
	BufferType &buffer;
	using DataType = typename std::remove_reference_t<decltype(buffer[0])>;
	static constexpr unsigned long MAX_LENGTH = sizeof(BufferType) / sizeof(DataType);

public:
	FadeLoopExt(BufferType &buff)
		: buffer{buff}
	{
		for (unsigned long i = 0; i < MAX_LENGTH; i++) {
			buffer[i] = 0;
		}
	}

	// Shortcut to do a read() and a write()
	// Only useful if the value to write doesn't depend on what's read
	DataType process(DataType val_to_write)
	{
		auto read_val = read();
		write(val_to_write);
		return read_val;
	}

	DataType read()
	{
		DataType bufout;

		if (is_fading) {
			bufout = MathTools::interpolate(buffer[read_idx], buffer[fade_idx], fade_phase);
			_update_fade();
			if (++fade_idx >= MAX_LENGTH)
				fade_idx = 0;
		} else {
			bufout = buffer[read_idx];
		}
		if (++read_idx >= MAX_LENGTH)
			read_idx = 0;
		return bufout;
	}

	void write(DataType val)
	{
		buffer[write_idx] = val;
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

// FadeLoop is a simple wrapper for FadeLoopExt,
// where the buffer is std::array, allocated in the "big" heap
template<typename DataType, unsigned long MAX_LENGTH>
struct FadeLoop {
	using BufferType = std::array<DataType, MAX_LENGTH>;

	FadeLoop()
		: buf{new BigAlloc<BufferType>}
		, fadeloop{*buf}
	{}

	DataType process(DataType val_to_write)
	{
		return fadeloop.process(val_to_write);
	}
	DataType read()
	{
		return fadeloop.read();
	}
	void write(DataType val)
	{
		fadeloop.write(val);
	}
	void set_fade_speed(float val)
	{
		fadeloop.set_fade_speed(val);
	}
	void change_delay(unsigned long length)
	{
		fadeloop.change_delay(length);
	}
	bool is_crossfading()
	{
		return fadeloop.is_crossfading();
	}

	~FadeLoop()
	{
		delete buf;
	}

	BigAlloc<BufferType> *buf;
	FadeLoopExt<BufferType> fadeloop;
};

//TODO get this working, so it deletes
template<typename DataType, unsigned long MAX_LENGTH>
struct FadeLoop2 : FadeLoopExt<std::array<DataType, MAX_LENGTH>> {
	FadeLoop2()
		: FadeLoopExt<std::array<DataType, MAX_LENGTH>>{
			  *(std::make_unique<BigAlloc<std::array<DataType, MAX_LENGTH>>>())}
	{}
};
