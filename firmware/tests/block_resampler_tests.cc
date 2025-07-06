#include "doctest.h"
#include "dsp/block_resampler.hh"

TEST_CASE("Mono resampler sawtooth with 8 samples") {
	std::array<float, 8> in{0, 1, 2, 3, 4, 5, 6, 7};
	std::array<float, 32> out{};

	SUBCASE("resampler at 1") {
		MetaModule::BlockResampler res{1};

		CHECK(res.process(0, in, out) == 8);

		CHECK(out[0] == 0);
		CHECK(out[1] == 1);
		CHECK(out[2] == 2);
		CHECK(out[3] == 3);
		CHECK(out[4] == 4);
		CHECK(out[5] == 5);
		CHECK(out[6] == 6);
		CHECK(out[7] == 7);
	}

	SUBCASE("upsample by 2") {
		MetaModule::BlockResampler res{1};
		res.set_samplerate_in_out(24000, 48000);

		// First time:
		// 8 input samples, drop 2 => 6 input samples * 2 = 12 output samples
		CHECK(res.process(0, in, out) == 12);

		CHECK(out[0] == doctest::Approx(0));
		CHECK(out[1] == doctest::Approx(0.4375)); // 0.5 would be more accurate
		CHECK(out[2] == doctest::Approx(1.0));
		CHECK(out[3] == doctest::Approx(1.5));
		CHECK(out[4] == doctest::Approx(2.0));
		CHECK(out[5] == doctest::Approx(2.5));
		CHECK(out[6] == doctest::Approx(3.0));
		CHECK(out[7] == doctest::Approx(3.5));
		CHECK(out[8] == doctest::Approx(4.0));
		CHECK(out[9] == doctest::Approx(4.5));
		CHECK(out[10] == doctest::Approx(5.0));
		CHECK(out[11] == doctest::Approx(5.5));

		// Subsequent times: 8 => 16
		CHECK(res.process(0, in, out) == 16);

		CHECK(out[0] == doctest::Approx(6.0));
		CHECK(out[1] == doctest::Approx(7.0));
		CHECK(out[2] == doctest::Approx(7.0)); // note: does not reach 8.0
		CHECK(out[3] == doctest::Approx(3.5));
		CHECK(out[4] == doctest::Approx(0.0)); // note: output lags by 4 samples
		CHECK(out[5] == doctest::Approx(0.0)); // ???: 0.5 would be more accurate
		CHECK(out[6] == doctest::Approx(1.0));
		CHECK(out[7] == doctest::Approx(1.5));
		CHECK(out[8] == doctest::Approx(2.0));
		CHECK(out[9] == doctest::Approx(2.5));
		CHECK(out[10] == doctest::Approx(3.0));
		CHECK(out[11] == doctest::Approx(3.5));
		CHECK(out[12] == doctest::Approx(4.0));
		CHECK(out[13] == doctest::Approx(4.5));
		CHECK(out[14] == doctest::Approx(5.0));
		CHECK(out[15] == doctest::Approx(5.5));
	}

	SUBCASE("downsample by 1.333") {
		MetaModule::BlockResampler res{1};
		res.set_samplerate_in_out(48000, 36000);

		// First time:
		// 8 input samples, drop 2 => 6 input samples / 1.3333 => 4 or 5 outputs
		CHECK(res.process(0, in, out) == 5);

		CHECK(out[0] == doctest::Approx(0));
		CHECK(out[1] == doctest::Approx(1.33333));
		CHECK(out[2] == doctest::Approx(2.66666));
		CHECK(out[3] == doctest::Approx(4.0));
		CHECK(out[4] == doctest::Approx(5.33333));

		// Subsequent times:
		// 8 input samples, drop 0 => 8 input samples / 1.3333 => 6 outputs
		CHECK(res.process(0, in, out) == 6);

		CHECK(out[0] == doctest::Approx(7.25926).epsilon(0.01));
		CHECK(out[1] == doctest::Approx(0).epsilon(0.001));
		CHECK(out[2] == doctest::Approx(1.33333));
		CHECK(out[3] == doctest::Approx(2.66666));
		CHECK(out[4] == doctest::Approx(4.0));
		CHECK(out[5] == doctest::Approx(5.33333));
	}

	SUBCASE("downsample by 6") {
		MetaModule::BlockResampler res{1};
		res.set_samplerate_in_out(48000, 8000);

		// outputs total 8 samples for 6*8=48 input samples:

		// First time:
		// 8 input frames, drop 2 => 6 input frames /6 = 1 output frame
		CHECK(res.process(0, in, out) == 1);
		CHECK(out[0] == doctest::Approx(0));

		// Subsequent times:
		// 8 input frames, drop none => 8 input frames /6 = 1 or 2 output frames
		CHECK(res.process(0, in, out) == 2);
		CHECK(out[0] == doctest::Approx(6));
		CHECK(out[1] == doctest::Approx(4));

		CHECK(res.process(0, in, out) == 1);
		CHECK(out[0] == doctest::Approx(2));

		CHECK(res.process(0, in, out) == 1);
		CHECK(out[0] == doctest::Approx(0));

		CHECK(res.process(0, in, out) == 2);
		CHECK(out[0] == doctest::Approx(6));
		CHECK(out[1] == doctest::Approx(4));

		CHECK(res.process(0, in, out) == 1);
		CHECK(out[0] == doctest::Approx(2));
	}
}

TEST_CASE("Stereo resampler sawtooth with 8 samples") {
	std::array<float, 8> inL{0, 1, 2, 3, 4, 5, 6, 7};
	std::array<float, 8> inR{16, 15.5, 15, 14.5, 14, 13.5, 13, 12.5};

	// create interleaved
	std::array<float, 16> in;
	for (auto i = 0u; i < inL.size(); i++) {
		in[i * 2] = inL[i];
		in[i * 2 + 1] = inR[i];
	}

	SUBCASE("resampler at 1") {
		MetaModule::BlockResampler res{2};

		std::array<float, 16> out;

		CHECK(res.process(0, in, out) == 16);
		CHECK(res.process(1, in, out) == 16);

		for (auto i = 0; i < 16; i++) {
			CHECK(out[i] == in[i]);
		}
	}

	SUBCASE("upsample 0.5") {
		MetaModule::BlockResampler res{2};
		res.set_samplerate_in_out(24000, 48000);

		std::array<float, 32> out;

		// 8 input frames, drop first 2 => 12 output frames => 24 output samples
		CHECK(res.process(0, in, out) == 24);
		CHECK(res.process(1, in, out) == 24);

		CHECK(out[0] == doctest::Approx(0.0));
		CHECK(out[1] == doctest::Approx(16.0));
		CHECK(out[2] == doctest::Approx(0.4375));
		CHECK(out[3] == doctest::Approx(16.781250));
		CHECK(out[4] == doctest::Approx(1.0));
		CHECK(out[5] == doctest::Approx(15.50));
		CHECK(out[6] == doctest::Approx(1.5));
		CHECK(out[7] == doctest::Approx(15.25));
		CHECK(out[8] == doctest::Approx(2.0));
		CHECK(out[9] == doctest::Approx(15.00));
		CHECK(out[10] == doctest::Approx(2.5));
		CHECK(out[11] == doctest::Approx(14.75));
		CHECK(out[12] == doctest::Approx(3.0));
		CHECK(out[13] == doctest::Approx(14.50));
		CHECK(out[14] == doctest::Approx(3.5));
		CHECK(out[15] == doctest::Approx(14.25));
		CHECK(out[16] == doctest::Approx(4.0));
		CHECK(out[17] == doctest::Approx(14.00));
		CHECK(out[18] == doctest::Approx(4.5));
		CHECK(out[19] == doctest::Approx(13.75));
		CHECK(out[20] == doctest::Approx(5.0));
		CHECK(out[21] == doctest::Approx(13.50));
		CHECK(out[22] == doctest::Approx(5.5));
		CHECK(out[23] == doctest::Approx(13.25));

		// 8 input frames, drop none => 16 output frames => 32 output samples
		CHECK(res.process(0, in, out) == 32);
		CHECK(res.process(1, in, out) == 32);

		CHECK(out[0] == doctest::Approx(6.0));
		CHECK(out[1] == doctest::Approx(13.00));
		CHECK(out[2] == doctest::Approx(7.0));
		CHECK(out[3] == doctest::Approx(12.50));
		CHECK(out[4] == doctest::Approx(7.0));
		CHECK(out[5] == doctest::Approx(12.50));
		CHECK(out[6] == doctest::Approx(3.5));
		CHECK(out[7] == doctest::Approx(14.25));
		CHECK(out[8] == doctest::Approx(0));
		CHECK(out[9] == doctest::Approx(16.0));
		//etc..
	}
}

TEST_CASE("ResamplingInterleavedBuffer") {

	MetaModule::ResamplingInterleavedBuffer<2, 32, 4> res;

	std::array<float, 8> inL{0, 1, 2, 3, 4, 5, 6, 7};
	std::array<float, 8> inR{16, 15.5, 15, 14.5, 14, 13.5, 13, 12.5};

	// create interleaved
	std::array<float, 16> in;
	for (auto i = 0u; i < inL.size(); i++) {
		in[i * 2] = inL[i];
		in[i * 2 + 1] = inR[i];
	}

	SUBCASE("1:1 ratio") {
		res.set_samplerate_in_out(48000, 48000);
		auto out = res.process_block(2, in);
		unsigned i = 0;
		for (auto o : out) {
			CHECK(o == in[i++]);
		}
	}

	SUBCASE("upsample 0.5") {
		res.set_samplerate_in_out(24000, 48000);

		auto out = res.process_block(2, in);
		CHECK(out.size() == 24);

		CHECK(out[0] == doctest::Approx(0.0));
		CHECK(out[1] == doctest::Approx(16.0));
		CHECK(out[2] == doctest::Approx(0.4375));
		CHECK(out[3] == doctest::Approx(16.781250));
		CHECK(out[4] == doctest::Approx(1.0));
		CHECK(out[5] == doctest::Approx(15.50));
		CHECK(out[6] == doctest::Approx(1.5));
		CHECK(out[7] == doctest::Approx(15.25));
		CHECK(out[8] == doctest::Approx(2.0));
		CHECK(out[9] == doctest::Approx(15.00));
		CHECK(out[10] == doctest::Approx(2.5));
		CHECK(out[11] == doctest::Approx(14.75));
		CHECK(out[12] == doctest::Approx(3.0));
		CHECK(out[13] == doctest::Approx(14.50));
		CHECK(out[14] == doctest::Approx(3.5));
		CHECK(out[15] == doctest::Approx(14.25));
		CHECK(out[16] == doctest::Approx(4.0));
		CHECK(out[17] == doctest::Approx(14.00));
		CHECK(out[18] == doctest::Approx(4.5));
		CHECK(out[19] == doctest::Approx(13.75));
		CHECK(out[20] == doctest::Approx(5.0));
		CHECK(out[21] == doctest::Approx(13.50));
		CHECK(out[22] == doctest::Approx(5.5));
		CHECK(out[23] == doctest::Approx(13.25));

		out = res.process_block(2, in);
		CHECK(out.size() == 32);

		CHECK(out[0] == doctest::Approx(6.0));
		CHECK(out[1] == doctest::Approx(13.00));
		CHECK(out[2] == doctest::Approx(7.0));
		CHECK(out[3] == doctest::Approx(12.50));
		CHECK(out[4] == doctest::Approx(7.0));
		CHECK(out[5] == doctest::Approx(12.50));
		CHECK(out[6] == doctest::Approx(3.5));
		CHECK(out[7] == doctest::Approx(14.25));
		CHECK(out[8] == doctest::Approx(0));
		CHECK(out[9] == doctest::Approx(16.0));
		//etc..
	}
}
