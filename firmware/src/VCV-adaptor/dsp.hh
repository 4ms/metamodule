#pragma once
#include <algorithm>
#include <cstddef>
#include <cstring>

namespace rack::dsp
{
template<size_t CHANNELS, typename T = float>
struct Frame {
	T samples[CHANNELS];
};

template<typename T, size_t S>
struct DoubleRingBuffer {
	size_t start{0};
	size_t end{0};
	T data[2 * S];

	void push(T t) {
		size_t i = end % S;
		data[i] = t;
		data[i + S] = t;
		end++;
	}
	T shift() {
		size_t i = start % S;
		T t = data[i];
		start++;
		return t;
	}
	void clear() {
		start = end;
	}
	bool empty() const {
		return start >= end;
	}
	bool full() const {
		return end - start >= S;
	}
	size_t size() const {
		return end - start;
	}
	size_t capacity() const {
		return S - size();
	}
	/** Returns a pointer to S consecutive elements for appending.
	If any data is appended, you must call endIncr afterwards.
	Pointer is invalidated when any other method is called.
	*/
	T *endData() {
		size_t i = end % S;
		return &data[i];
	}
	void endIncr(size_t n) {
		size_t i = end % S;
		size_t e1 = i + n;
		size_t e2 = (e1 < S) ? e1 : S;
		// Copy data forward
		std::memcpy(&data[S + i], &data[i], sizeof(T) * (e2 - i));

		if (e1 > S) {
			// Copy data backward from the doubled block to the main block
			std::memcpy(data, &data[S], sizeof(T) * (e1 - S));
		}
		end += n;
	}
	/** Returns a pointer to S consecutive elements for consumption
	If any data is consumed, call startIncr afterwards.
	*/
	const T *startData() const {
		size_t i = start % S;
		return &data[i];
	}
	void startIncr(size_t n) {
		start += n;
	}
};

// Mock-up: just copies from in to out, no conversion
template<int MAX_CHANNELS>
struct SampleRateConverter {

	void setRates(unsigned, float) {
	}

	void process(const float *in, int inStride, int *inFrames, float *out, int outStride, int *outFrames) {
		int frames = std::min(*inFrames, *outFrames);
		for (int i = 0; i < frames; i++) {
			for (int c = 0; c < MAX_CHANNELS; c++) {
				out[outStride * i + c] = in[inStride * i + c];
			}
		}
		*inFrames = frames;
		*outFrames = frames;
	}

	void process(const Frame<MAX_CHANNELS> *in, int *inFrames, Frame<MAX_CHANNELS> *out, int *outFrames) {
		process((const float *)in, MAX_CHANNELS, inFrames, (float *)out, MAX_CHANNELS, outFrames);
	}
};
} // namespace rack::dsp
