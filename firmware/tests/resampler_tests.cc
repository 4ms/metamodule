#include "doctest.h"
#include "speex/speex_resampler.h"
#include <array>
#include <cmath>
#include <cstdio>
#include <vector>

template<size_t CHANNELS, typename T = float>
struct Frame {
	T samples[CHANNELS];
};

TEST_CASE("Resample triangle single channel (not a test, can write to file)") {

	int err = 0;
	unsigned num_chan = 1;
	unsigned in_rate = 32000;
	unsigned out_rate = 48000;
	unsigned quality = 5;
	auto sts = speex_resampler_init(num_chan, in_rate, out_rate, quality, &err);
	speex_resampler_set_input_stride(sts, 1);
	speex_resampler_set_output_stride(sts, 1);

	uint32_t in_len = 120;
	uint32_t out_len = 120;

	std::vector<float> in_buf(in_len);
	std::vector<float> out_buf(out_len);

	uint32_t ctr = 0;

	for (auto &in : in_buf) {
		// Triangle wave:
		in = (float)ctr / (float)(UINT32_MAX) * 10.f;
		if (in > 5.f)
			in = 10.f - in;
		ctr += 0x1000'0000;
	}
	for (auto &out : out_buf) {
		out = 0;
	}

	uint32_t in_len1 = in_len / 4;
	uint32_t out_len1 = out_len / 4;
	uint32_t in_pos = 0;
	uint32_t out_pos = 0;
	for (auto i = 0; i < 4; i++) {
		speex_resampler_process_float(sts, 0, in_buf.data() + in_pos, &in_len1, out_buf.data() + out_pos, &out_len1);

		in_pos += in_len1;
		out_pos += out_len1;
	}

#ifdef TEST_RESAMPLE_WRITE_TO_FILE
	FILE *fptr = fopen("rs.csv", "w");

	fprintf(fptr, ",\nin, ");
	for (auto in : in_buf) {
		fprintf(fptr, "%.1f, ", in);
	}
	fprintf(fptr, "\nout, ");
	for (auto out : out_buf) {
		fprintf(fptr, "%.1f, ", out);
	}
	fprintf(fptr, "\n");
#endif

	// speex_resampler_destroy(sts);
}

TEST_CASE("Resample triangle/sine two channel (not a test, can write to file)") {

	int err = 0;
	unsigned num_chan = 2;
	unsigned in_rate = 32000;
	unsigned out_rate = 48000;
	unsigned quality = 5;
	auto sts = speex_resampler_init(num_chan, in_rate, out_rate, quality, &err);
	speex_resampler_set_input_stride(sts, num_chan);
	speex_resampler_set_output_stride(sts, num_chan);

	constexpr uint32_t in_len = 512;
	constexpr uint32_t out_len = 512;

	std::array<Frame<2>, in_len> in_buf{};
	std::array<Frame<2>, out_len> out_buf{};

	uint32_t ctr = 0;
	float ph = 0.f;

	for (auto &in : in_buf) {
		// Triangle wave:
		in.samples[0] = (float)ctr / (float)(UINT32_MAX) * 10.f;
		if (in.samples[0] > 5.f)
			in.samples[0] = 10.f - in.samples[0];
		ctr += 0x0400'0000;

		in.samples[1] = 5.f * std::sin(ph);
		ph += 0.1f;
	}
	for (auto &out : out_buf) {
		out.samples[0] = 0;
		out.samples[1] = 0;
	}

	uint32_t in_pos = 0;
	uint32_t out_pos = 0;

	for (auto i = 0; i < 4; i++) {
		uint32_t in_len1 = 0;
		uint32_t out_len1 = 0;
		for (auto chan = 0u; chan < num_chan; chan++) {
			in_len1 = 32;
			out_len1 = 32;
			speex_resampler_process_float(
				sts, chan, &(in_buf[in_pos].samples[chan]), &in_len1, &(out_buf[out_pos].samples[chan]), &out_len1);
		}

		in_pos += in_len1;
		out_pos += out_len1;
	}

#ifdef TEST_RESAMPLE_WRITE_TO_FILE
	FILE *fptr = fopen("rs2.csv", "w");

	fprintf(fptr, ",\nin1, ");
	for (auto in : in_buf) {
		fprintf(fptr, "%.1f, ", in.samples[0]);
	}
	fprintf(fptr, ",\nin2, ");
	for (auto in : in_buf) {
		fprintf(fptr, "%.1f, ", in.samples[1]);
	}

	fprintf(fptr, "\nout1, ");
	for (auto out : out_buf) {
		fprintf(fptr, "%.1f, ", out.samples[0]);
	}
	fprintf(fptr, "\nout2, ");
	for (auto out : out_buf) {
		fprintf(fptr, "%.1f, ", out.samples[1]);
	}
	fprintf(fptr, "\n");
#endif

	speex_resampler_destroy(sts);
}
