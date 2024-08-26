/*
 * resample.c - Hermetian resampling algorithm, optimized for speed (not code size or readability!)
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

#include "circular_buffer.hh"
#include <algorithm>
#include <span>

namespace SamplerKit
{

static void wait_memory_ready() {
	// Memory::wait_until_ready();
}

template<int32_t BlockAlign>
static inline void inc_play_addr(CircularBuffer *buf, bool reverse) {
	if (!reverse) {
		buf->out += BlockAlign;

		// This will not work if buf->max==0xFFFFFFFF, but luckily this is never the case with the STS!
		if (buf->out >= buf->max) {
			buf->wrapping = 0;
			buf->out -= buf->size;
		}
	} else {
		if ((buf->out - buf->min) < BlockAlign) {
			buf->out += buf->size - BlockAlign;
			buf->wrapping = 1;
		} else
			buf->out -= BlockAlign;
	}
}

enum class WavChan { Left, Right, Average, Mono };

// Reads signed 16-bit and returns signed 24-bit stored in an int32_t
template<WavChan Chan>
inline int32_t get_sample(uint32_t addr) {
	wait_memory_ready();

	int16_t r;

	if constexpr (Chan == WavChan::Left || Chan == WavChan::Mono) {
		r = *((int16_t *)addr);
		return ((int32_t)r) * 256;

	} else if constexpr (Chan == WavChan::Right) {
		r = *((int16_t *)(addr + 2));
		return ((int32_t)r) * 256;

	} else {
		// Average:
		uint32_t rd = (*((uint32_t *)addr));
		int16_t a = (rd >> 16);
		int16_t b = (rd & 0x0000FFFF);
		int32_t t = a + b;
		return t * 128; //*256 and averaged is /2
	}
}

// TODO: get rid of block_align and use Chan:
// Average => 4
// Left/Right => 4
// Mono => 2
// template<Chan chan>
// void resample_read(
// 	float rs, CircularBuffer *buf, std::span<int32_t> outbuf, uint32_t block_align, bool rev, bool flush) {
// 	uint32_t buff_len = outbuf.size();
// 	_resample_read<chan>(rs, buf, buff_len, block_align, outbuf.data(), rev, flush);
// }

template<WavChan Chan>
void resample_read(float rs, CircularBuffer *buf, std::span<int32_t> outbuf, bool rev, bool flush) {
	static float fractional_pos = 0;
	static float xm1, x0, x1, x2;
	float a, b, c;
	uint32_t outpos;
	float t_out;

	uint32_t buff_len = outbuf.size();
	int32_t *out = outbuf.data();
	constexpr uint32_t BlockAlign = (Chan == WavChan::Mono) ? 2 : 4;

	if (rs == 1.f) {
		for (outpos = 0; outpos < buff_len; outpos++) {
			inc_play_addr<BlockAlign>(buf, rev);
			out[outpos] = get_sample<Chan>(buf->out);
		}
		return;
	}

	// fill the resampling buffer with three points
	if (flush) {
		inc_play_addr<BlockAlign>(buf, rev);
		x0 = get_sample<Chan>(buf->out);

		inc_play_addr<BlockAlign>(buf, rev);
		x1 = get_sample<Chan>(buf->out);

		inc_play_addr<BlockAlign>(buf, rev);
		x2 = get_sample<Chan>(buf->out);

		fractional_pos = 0.0;
	}

	outpos = 0;
	while (outpos < buff_len) {
		// Optimize for resample rates >= 4
		if (fractional_pos >= 4.f) {
			fractional_pos = fractional_pos - 4.f;

			// shift samples back one
			// and read a new sample
			inc_play_addr<BlockAlign>(buf, rev);
			xm1 = get_sample<Chan>(buf->out);

			inc_play_addr<BlockAlign>(buf, rev);
			x0 = get_sample<Chan>(buf->out);

			inc_play_addr<BlockAlign>(buf, rev);
			x1 = get_sample<Chan>(buf->out);

			inc_play_addr<BlockAlign>(buf, rev);
			x2 = get_sample<Chan>(buf->out);
		}
		// Optimize for resample rates >= 3
		if (fractional_pos >= 3.f) {
			fractional_pos = fractional_pos - 3.f;

			// shift samples back one
			// and read a new sample
			xm1 = x2;

			inc_play_addr<BlockAlign>(buf, rev);
			x0 = get_sample<Chan>(buf->out);

			inc_play_addr<BlockAlign>(buf, rev);
			x1 = get_sample<Chan>(buf->out);

			inc_play_addr<BlockAlign>(buf, rev);
			x2 = get_sample<Chan>(buf->out);
		}
		// Optimize for resample rates >= 2
		if (fractional_pos >= 2.f) {
			fractional_pos = fractional_pos - 2.f;

			// shift samples back one
			// and read a new sample
			xm1 = x1;
			x0 = x2;

			inc_play_addr<BlockAlign>(buf, rev);
			x1 = get_sample<Chan>(buf->out);

			inc_play_addr<BlockAlign>(buf, rev);
			x2 = get_sample<Chan>(buf->out);
		}
		// Optimize for resample rates >= 1
		if (fractional_pos >= 1.f) {
			fractional_pos = fractional_pos - 1.f;

			// shift samples back one
			// and read a new sample
			xm1 = x0;
			x0 = x1;
			x1 = x2;

			inc_play_addr<BlockAlign>(buf, rev);
			x2 = get_sample<Chan>(buf->out);
		}

		// calculate coefficients
		a = (3 * (x0 - x1) - xm1 + x2) / 2;
		b = 2 * x1 + xm1 - (5 * x0 + x2) / 2;
		c = (x1 - xm1) / 2;

		// calculate as many fractionally placed output points as we need
		while (fractional_pos < 1.f && outpos < buff_len) {
			t_out = (((a * fractional_pos) + b) * fractional_pos + c) * fractional_pos + x0;
			out[outpos++] = (int32_t)(std::clamp(t_out, -32768.f * 256.f, 32767.f * 256.f));

			fractional_pos += rs;
		}
	}
}

} // namespace SamplerKit
