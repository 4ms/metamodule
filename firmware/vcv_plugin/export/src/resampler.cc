#include "medium/debug_raw.h"
#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <span>
#include <speex/speex_resampler.h>
#include <vector>

struct SpeexResamplerChan {
	bool flush{true};
	uint8_t input_stride = 1;
	uint8_t output_stride = 1;

	float ratio = 1;
	float fractional_pos{};
	float xm1{};
	float x0{};
	float x1{};
	float x2{};
};

struct SpeexResamplerState_ {
	static constexpr size_t MAX_RESAMPLER_CHANNELS = 16;

	std::array<SpeexResamplerChan, MAX_RESAMPLER_CHANNELS> chans;
	size_t num_chans = 0;
};

extern "C" {
int speex_resampler_process_float(SpeexResamplerState *st,
								  spx_uint32_t channel_index,
								  const float *in,
								  spx_uint32_t *in_len,
								  float *out,
								  spx_uint32_t *out_len) {

	if (channel_index >= st->num_chans)
		return RESAMPLER_ERR_INVALID_ARG;

	SpeexResamplerChan &stc = st->chans[channel_index];

	uint32_t in_size = *in_len * stc.input_stride;
	uint32_t out_size = *out_len * stc.output_stride;

	if (stc.ratio == 1.f) {
		//copy
		uint32_t len = std::min(*in_len, *out_len);
		std::memcpy(out, in, len);
		*in_len = len;
		*out_len = len;
		return 0;
	}

	uint32_t inpos = 0;

	auto get_next_in = [&](float &next) {
		if (inpos < in_size) {
			next = in[inpos];
			inpos += stc.input_stride;
		}
	};

	if (stc.flush && in_size >= 3) {
		stc.flush = false;
		stc.xm1 = 0;
		get_next_in(stc.x0);
		get_next_in(stc.x1);
		get_next_in(stc.x2);
		stc.fractional_pos = 0.0;
	}

	uint32_t outpos = 0;

	while (outpos < out_size && inpos < in_size) {

		// Optimize for resample rates >= 2
		if (stc.fractional_pos >= 2.f && (inpos + 2) <= in_size) {
			stc.fractional_pos = stc.fractional_pos - 2.f;

			// shift samples back two
			// and read a new sample
			stc.xm1 = stc.x1;
			stc.x0 = stc.x2;
			get_next_in(stc.x1);
			get_next_in(stc.x2);
		}

		// Optimize for resample rates >= 1
		if (stc.fractional_pos >= 1.f && (inpos + 1) <= in_size) {
			stc.fractional_pos = stc.fractional_pos - 1.f;

			// shift samples back one
			// and read a new sample
			stc.xm1 = stc.x0;
			stc.x0 = stc.x1;
			stc.x1 = stc.x2;
			get_next_in(stc.x2);
		}

		// calculate coefficients
		float a = (3 * (stc.x0 - stc.x1) - stc.xm1 + stc.x2) / 2;
		float b = 2 * stc.x1 + stc.xm1 - (5 * stc.x0 + stc.x2) / 2;
		float c = (stc.x1 - stc.xm1) / 2;

		// calculate as many fractionally placed output points as we need
		while (stc.fractional_pos < 1.f && outpos < out_size) {
			out[outpos] = (((a * stc.fractional_pos) + b) * stc.fractional_pos + c) * stc.fractional_pos + stc.x0;
			outpos += stc.output_stride;

			stc.fractional_pos += stc.ratio;
		}
	}

	*out_len = outpos / stc.output_stride;
	*in_len = inpos / stc.output_stride;

	return 0;
}

SpeexResamplerState *
speex_resampler_init(spx_uint32_t nb_channels, spx_uint32_t in_rate, spx_uint32_t out_rate, int quality, int *err) {

	if (nb_channels >= SpeexResamplerState::MAX_RESAMPLER_CHANNELS) {
		*err = RESAMPLER_ERR_INVALID_ARG;
		nb_channels = SpeexResamplerState::MAX_RESAMPLER_CHANNELS;
	} else {
		*err = 0;
	}

	auto st = new SpeexResamplerState;

	st->num_chans = nb_channels;
	for (auto i = 0u; i < st->num_chans; i++) {
		auto &stc = st->chans[i];
		stc.flush = true;
		stc.ratio = (float)in_rate / (float)out_rate;
	}
	return st;
}

void speex_resampler_destroy(SpeexResamplerState *st) {
	if (st) {
		delete st;
	}
}

void speex_resampler_set_input_stride(SpeexResamplerState *st, spx_uint32_t stride) {
	if (st) {
		for (auto i = 0u; i < st->num_chans; i++) {
			auto &stc = st->chans[i];
			stc.input_stride = stride;
		}
	}
}

void speex_resampler_set_output_stride(SpeexResamplerState *st, spx_uint32_t stride) {
	if (st) {
		for (auto i = 0u; i < st->num_chans; i++) {
			auto &stc = st->chans[i];
			stc.output_stride = stride;
		}
	}
}
}
