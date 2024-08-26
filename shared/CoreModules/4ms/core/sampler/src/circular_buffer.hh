/*
 * circular_buffer.h - routines for handling circular buffers
 *
 * Author: Dan Green (danngreen1@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * See http://creativecommons.org/licenses/MIT/ for more information.
 *
 * -----------------------------------------------------------------------------
 */
#pragma once
#include <cstdint>
#include <span>

namespace SamplerKit
{

struct CircularBuffer {
	uintptr_t in;
	uintptr_t out;
	uintptr_t min;
	uintptr_t max;
	intptr_t size; // should always be max-min
	bool wrapping;

	CircularBuffer() {
		init();
	}
	void init() {
		wrapping = 0;
		in = min;
		out = min;
	}

	void wait_memory_ready() {
	}

	// FIXME: For all the memory IO, we could use memcpy to save some cycles
	//  - Is it worth it? Memory IO is not the bottleneck (SD card IO is)
	//  - We'd need to write new under/overflow checks

	uint32_t memory_read16(std::span<int16_t> rd_buff, bool decrement) {
		return memory_read16(rd_buff.data(), rd_buff.size(), decrement);
	}

	// Read num_samples from the out ptr, and put them in rd_buff
	// Pad rd_buff with 0's if we underflow our CircularBuffer
	uint32_t memory_read16(int16_t *rd_buff, uint32_t num_samples, bool decrement) {
		uint32_t num_underflowed = 0;
		for (uint32_t i = 0; i < num_samples; i++) {

			if (out == in)
				num_underflowed = 1;
			else if (num_underflowed)
				num_underflowed++;

			if (num_underflowed)
				rd_buff[i] = 0;
			else {
				wait_memory_ready();
				rd_buff[i] = *reinterpret_cast<int16_t *>(out);
			}

			offset_out_address(2, decrement);
			out = (out & 0xFFFFFFFE);
		}
		return num_underflowed;
	}

	uint32_t memory_read24(uint8_t *rd_buff, uint32_t num_samples, bool decrement) {
		uint32_t i;
		uint32_t num_bytes = num_samples * 3;

		for (i = 0; i < num_bytes; i++) {
			wait_memory_ready();
			rd_buff[i] = *reinterpret_cast<int8_t *>(out);
			offset_out_address(1, decrement);
		}
		return 0; // does not check for overflow
	}

	// Grab 16-bit ints and write them into b as 16-bit ints
	// num_words should be the number of 32-bit words to read from wr_buff (bytes>>2)
	uint32_t memory_write_16as16(uint32_t *wr_buff, uint32_t num_words, bool decrement) {
		uint32_t i;
		uint8_t start_polarity, end_polarity, start_wrap, end_wrap;

		// detect head-crossing:
		start_polarity = (in < out) ? 0 : 1;
		start_wrap = wrapping;

		for (i = 0; i < num_words; i++) {
			wait_memory_ready();
			// *((uint32_t *)in) = wr_buff[i];
			*reinterpret_cast<uint32_t *>(in) = wr_buff[i];
			offset_in_address(4, decrement);
		}

		end_polarity = (in < out) ? 0 : 1;
		end_wrap = wrapping; // 0 or 1

		// start_polarity + end_polarity  is (0/2 if no change, 1 if change)
		// start_wrap + end_wrap is (0/2 if no change, 1 if change)
		// Thus the sum of all four is even unless just polarity or just wrap changes (but not both)

		if ((end_wrap + start_wrap + start_polarity + end_polarity) & 0b01) // if (sum is odd)
			return 1; // warning: in pointer and out pointer crossed
		else
			return 0; // pointers did not cross
	}

	// Convert 24-bit words from wr_buff into 16-bit words, and write to the in ptr
	uint32_t memory_write_24as16(uint8_t *wr_buff, uint32_t num_bytes, bool decrement) {
		uint32_t i;
		uint8_t start_polarity, end_polarity, start_wrap, end_wrap;

		start_polarity = (in < out) ? 0 : 1;
		start_wrap = wrapping;

		for (i = 0; i < num_bytes; i += 3) // must be a multiple of 3!
		{
			wait_memory_ready();
			auto s = (int16_t)(wr_buff[i + 2] << 8 | wr_buff[i + 1]);
			*reinterpret_cast<int16_t *>(in) = s;
			offset_in_address(2, decrement);
		}

		end_polarity = (in < out) ? 0 : 1;
		end_wrap = wrapping; // 0 or 1

		if ((end_wrap + start_wrap + start_polarity + end_polarity) & 0b01)
			return 1; // warning: in pointer and out pointer crossed
		else
			return 0; // pointers did not cross
	}

	// Grab 32-bit words and write them into b as 16-bit values
	uint32_t memory_write_32ias16(uint8_t *wr_buff, uint32_t num_bytes, bool decrement) {
		uint32_t i;
		uint8_t start_polarity, end_polarity, start_wrap, end_wrap;

		start_polarity = (in < out) ? 0 : 1;
		start_wrap = wrapping;

		for (i = 0; i < num_bytes; i += 4) {
			wait_memory_ready();
			auto s = (int16_t)(wr_buff[i + 3] << 8 | wr_buff[i + 2]);
			*reinterpret_cast<int16_t *>(in) = s;
			offset_in_address(2, decrement);
		}

		end_polarity = (in < out) ? 0 : 1;
		end_wrap = wrapping; // 0 or 1

		if ((end_wrap + start_wrap + start_polarity + end_polarity) & 0b01)
			return 1; // warning: in pointer and out pointer crossed
		else
			return 0; // pointers did not cross
	}

	// Grab 32-bit floats and write them into b as 16-bit values
	uint32_t memory_write_32fas16(float *wr_buff, uint32_t num_floats, bool decrement) {
		uint32_t i;
		uint8_t start_polarity, end_polarity, start_wrap, end_wrap;

		start_polarity = (in < out) ? 0 : 1;
		start_wrap = wrapping;

		for (i = 0; i < num_floats; i++) {
			wait_memory_ready();
			int16_t s;
			if (wr_buff[i] >= 1.f)
				s = 32767;
			else if (wr_buff[i] <= -1.F)
				s = -32768;
			else
				s = (int16_t)(wr_buff[i] * 32767.f);

			*reinterpret_cast<int16_t *>(in) = s;

			offset_in_address(2, decrement);
		}

		end_polarity = (in < out) ? 0 : 1;
		end_wrap = wrapping; // 0 or 1

		if ((end_wrap + start_wrap + start_polarity + end_polarity) & 0b01)
			return 1; // warning: in pointer and out pointer crossed
		else
			return 0; // pointers did not cross
	}

	// Grab 8-bit ints from wr_buff and write them into b as 16-bit ints
	uint32_t memory_write_8as16(uint8_t *wr_buff, uint32_t num_bytes, bool decrement) {
		uint32_t i;
		uint8_t start_polarity, end_polarity, start_wrap, end_wrap;

		// setup to detect head-crossing:
		start_polarity = (in < out) ? 0 : 1;
		start_wrap = wrapping;

		for (i = 0; i < num_bytes; i++) {
			wait_memory_ready();
			auto s = ((int16_t)(wr_buff[i]) - 128) * 256;
			*reinterpret_cast<int16_t *>(in) = s;
			offset_in_address(2, decrement);
		}

		end_polarity = (in < out) ? 0 : 1;
		end_wrap = wrapping; // 0 or 1

		if ((end_wrap + start_wrap + start_polarity + end_polarity) & 0b01) // if (sum is odd)
			return 1; // warning: in pointer and out pointer crossed
		else
			return 0; // pointers did not cross
	}

	uint32_t memory_write16(int16_t *wr_buff, uint32_t num_samples, bool decrement) {
		uint32_t i;
		uint32_t heads_crossed = 0;

		in = (in & 0xFFFFFFFE);

		for (i = 0; i < num_samples; i++) {
			wait_memory_ready();
			*reinterpret_cast<int16_t *>(in) = wr_buff[i];
			offset_in_address(2, decrement);

			if (in == out) // don't consider the heads being crossed if they begin at the same place
				heads_crossed = out;
		}

		return heads_crossed;
	}

	uint8_t offset_in_address(uint32_t amt, bool subtract) {
		if (!subtract) {
			if ((max - in) <= amt) // same as "if ((in + amt) >= max)" but doing the math this way avoids
								   // overflow in case max == 0xFFFFFFFF
			{
				in -= size - amt;
				if (wrapping)
					return 1; // warning: already wrapped, and wrapped again!
				wrapping = 1;
			} else
				in += amt;
		} else {
			if ((in - min) < amt) // same as "if (in - amt) < min" but avoids using negative numbers in case amt > in
			{
				in += size - amt;
				if (!wrapping)
					return 1; // warning: already unwrapped!
				wrapping = 0;
			} else
				in -= amt;
		}
		return 0;
	}

	uint8_t offset_out_address(uint32_t amt, bool subtract) {
		if (!subtract) {
			if ((max - out) <= amt) // same as "if (out + amt) > max" but doing the math this way avoids
									// overflow in case max == 0xFFFFFFFF
			{
				out -= size - amt;
				if (!wrapping)
					return 1; // warning: already unwrapped!
				wrapping = 0;
			} else
				out += amt;
		} else {
			if ((out - min) < amt) // same as "if (out - amt) < min" but avoids using negative numbers in case amt > out
			{
				out += size - amt;
				if (wrapping)
					return 1; // warning: already wrapped, and wrapped again!
				wrapping = 1;
			} else
				out -= amt;
		}
		return 0;
	}

	static uint32_t distance_points(uint32_t leader, uint32_t follower, uint32_t size, bool reverse) {
		if (reverse) {
			if (follower >= leader)
				return follower - leader;
			else // wrapping
				return (follower + size) - leader;
		} else {
			if (leader >= follower)
				return leader - follower;
			else // wrapping
				return (leader + size) - follower;
		}
	}

	uint32_t distance(bool reverse) {
		if (reverse) {
			if (out >= in)
				return out - in;
			else // wrapping
				return (out + size) - in;
		} else {
			if (in >= out)
				return in - out;
			else // wrapping
				return (in + size) - out;
		}
	}
};

} // namespace SamplerKit
