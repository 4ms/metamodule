#include "doctest.h"
#include "dsp/stream_resampler.hh"

TEST_CASE("Mono resampler sawtooth with 8 samples") {
	std::array<float, 8> in{0, 1, 2, 3, 4, 5, 6, 7};

	unsigned pos = 0;
	auto get_input = [&] {
		auto next = in[pos];
		pos++;
		if (pos >= in.size())
			pos = 0;
		return next;
	};

	SUBCASE("resampler at 1") {
		MetaModule::StreamResampler res{1};

		CHECK(res.process_mono(get_input) == 0);
		CHECK(res.process_mono(get_input) == 1);
		CHECK(res.process_mono(get_input) == 2);
		CHECK(res.process_mono(get_input) == 3);
		CHECK(res.process_mono(get_input) == 4);
		CHECK(res.process_mono(get_input) == 5);
		CHECK(res.process_mono(get_input) == 6);
		CHECK(res.process_mono(get_input) == 7);
		CHECK(res.process_mono(get_input) == doctest::Approx(0));
	}

	SUBCASE("upsample by 2") {
		MetaModule::StreamResampler res{1};
		res.set_sample_rate_in_out(24000, 48000);

		CHECK(res.process_mono(get_input) == doctest::Approx(0));
		CHECK(res.process_mono(get_input) == doctest::Approx(0.4375)); // why?
		CHECK(res.process_mono(get_input) == doctest::Approx(1.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(1.5));
		CHECK(res.process_mono(get_input) == doctest::Approx(2.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(2.5));
		CHECK(res.process_mono(get_input) == doctest::Approx(3.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(3.5));
		CHECK(res.process_mono(get_input) == doctest::Approx(4.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(4.5));
		CHECK(res.process_mono(get_input) == doctest::Approx(5.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(5.5));
		CHECK(res.process_mono(get_input) == doctest::Approx(6.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(7.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(7.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(3.5));
		CHECK(res.process_mono(get_input) == doctest::Approx(0.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(0.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(1.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(1.5));
		CHECK(res.process_mono(get_input) == doctest::Approx(2.0));
	}

	SUBCASE("upsample by 1.33") {
		MetaModule::StreamResampler res{1};
		res.set_sample_rate_in_out(36000, 48000);

		CHECK(res.process_mono(get_input) == doctest::Approx(0.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(0.726562).epsilon(0.01));
		CHECK(res.process_mono(get_input) == doctest::Approx(1.5));
		CHECK(res.process_mono(get_input) == doctest::Approx(2.25));
		CHECK(res.process_mono(get_input) == doctest::Approx(3.00));
		CHECK(res.process_mono(get_input) == doctest::Approx(3.75));
		CHECK(res.process_mono(get_input) == doctest::Approx(4.50));
		CHECK(res.process_mono(get_input) == doctest::Approx(5.25));
		CHECK(res.process_mono(get_input) == doctest::Approx(6.00));
		CHECK(res.process_mono(get_input) == doctest::Approx(7.3125));
		CHECK(res.process_mono(get_input) == doctest::Approx(3.50));
		CHECK(res.process_mono(get_input) == doctest::Approx(-0.31250));
		CHECK(res.process_mono(get_input) == doctest::Approx(1.00));
		CHECK(res.process_mono(get_input) == doctest::Approx(1.75));
		CHECK(res.process_mono(get_input) == doctest::Approx(2.50));
		CHECK(res.process_mono(get_input) == doctest::Approx(3.25));
	}

	SUBCASE("downsample by 2") {
		MetaModule::StreamResampler res{1};
		res.set_sample_rate_in_out(48000, 24000);

		CHECK(res.process_mono(get_input) == doctest::Approx(0));
		CHECK(res.process_mono(get_input) == doctest::Approx(2));
		CHECK(res.process_mono(get_input) == doctest::Approx(4));
		CHECK(res.process_mono(get_input) == doctest::Approx(6));

		CHECK(res.process_mono(get_input) == doctest::Approx(0));
		CHECK(res.process_mono(get_input) == doctest::Approx(2));
		CHECK(res.process_mono(get_input) == doctest::Approx(4));
		CHECK(res.process_mono(get_input) == doctest::Approx(6));

		CHECK(res.process_mono(get_input) == doctest::Approx(0));
		CHECK(res.process_mono(get_input) == doctest::Approx(2));
		CHECK(res.process_mono(get_input) == doctest::Approx(4));
		CHECK(res.process_mono(get_input) == doctest::Approx(6));
	}

	SUBCASE("downsample by 1.333") {
		MetaModule::StreamResampler res{1};
		res.set_sample_rate_in_out(48000, 36000);

		CHECK(res.process_mono(get_input) == doctest::Approx(0));
		CHECK(res.process_mono(get_input) == doctest::Approx(1.33333));
		CHECK(res.process_mono(get_input) == doctest::Approx(2.66666));
		CHECK(res.process_mono(get_input) == doctest::Approx(4.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(5.33333));
		CHECK(res.process_mono(get_input) == doctest::Approx(7.25926).epsilon(0.01));

		CHECK(res.process_mono(get_input) == doctest::Approx(0).epsilon(0.001));
		CHECK(res.process_mono(get_input) == doctest::Approx(1.33333));
		CHECK(res.process_mono(get_input) == doctest::Approx(2.66666));
		CHECK(res.process_mono(get_input) == doctest::Approx(4.0));
		CHECK(res.process_mono(get_input) == doctest::Approx(5.33333));
		CHECK(res.process_mono(get_input) == doctest::Approx(7.25926).epsilon(0.01));
	}

	SUBCASE("downsample by 6") {
		MetaModule::StreamResampler res{1};
		res.set_sample_rate_in_out(48000, 8000);

		// goes backwards every other sample (aliasing)
		CHECK(res.process_mono(get_input) == doctest::Approx(0));
		CHECK(res.process_mono(get_input) == doctest::Approx(6));
		CHECK(res.process_mono(get_input) == doctest::Approx(4));
		CHECK(res.process_mono(get_input) == doctest::Approx(2));

		CHECK(res.process_mono(get_input) == doctest::Approx(0));
		CHECK(res.process_mono(get_input) == doctest::Approx(6));
		CHECK(res.process_mono(get_input) == doctest::Approx(4));
		CHECK(res.process_mono(get_input) == doctest::Approx(2));
	}

	SUBCASE("downsample by 3.33333") {
		MetaModule::StreamResampler res{1};
		res.set_sample_rate_in_out(48000, 14400);

		CHECK(res.process_mono(get_input) == doctest::Approx(0));
		CHECK(res.process_mono(get_input) == doctest::Approx(3.333333));
		CHECK(res.process_mono(get_input) == doctest::Approx(7.25926));
		CHECK(res.process_mono(get_input) == doctest::Approx(2.000000));
		CHECK(res.process_mono(get_input) == doctest::Approx(5.333333));
		CHECK(res.process_mono(get_input) == doctest::Approx(0.370369));
		CHECK(res.process_mono(get_input) == doctest::Approx(4.000000));
		CHECK(res.process_mono(get_input) == doctest::Approx(4.962965));
		CHECK(res.process_mono(get_input) == doctest::Approx(2.66667));
		CHECK(res.process_mono(get_input) == doctest::Approx(6.000000));
		CHECK(res.process_mono(get_input) == doctest::Approx(1.333333));
		CHECK(res.process_mono(get_input) == doctest::Approx(4.66667));
	}
}

TEST_CASE("Stereo resampler sawtooth with 8 samples") {
	std::array<float, 8> inL{0, 1, 2, 3, 4, 5, 6, 7};
	std::array<float, 8> inR{16, 15.5, 15, 14.5, 14, 13.5, 13, 12.5};

	std::array<float, 16> in;
	for (auto i = 0u; i < inL.size(); i++) {
		in[i * 2] = inL[i];
		in[i * 2 + 1] = inR[i];
	}

	unsigned pos = 0;
	auto get_input = [&] {
		auto next = in[pos];
		pos++;
		if (pos >= in.size())
			pos = 0;
		return next;
	};

	SUBCASE("resampler at 1") {
		MetaModule::StreamResampler res{2};

		std::array<float, 2> out;

		for (auto i = 0; i < 16; i++) {
			res.process(get_input, out);
			CHECK(out[0] == inL[i % 8]);
			CHECK(out[1] == inR[i % 8]);
		}
	}

	SUBCASE("upsample 0.5") {
		MetaModule::StreamResampler res{2};
		res.set_sample_rate_in_out(24000, 48000);

		std::array<float, 2> out;
		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(0.0));
		CHECK(out[1] == doctest::Approx(16.0));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(0.4375));
		CHECK(out[1] == doctest::Approx(16.781250));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(1.0));
		CHECK(out[1] == doctest::Approx(15.50));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(1.5));
		CHECK(out[1] == doctest::Approx(15.25));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(2.0));
		CHECK(out[1] == doctest::Approx(15.00));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(2.5));
		CHECK(out[1] == doctest::Approx(14.75));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(3.0));
		CHECK(out[1] == doctest::Approx(14.50));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(3.5));
		CHECK(out[1] == doctest::Approx(14.25));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(4.0));
		CHECK(out[1] == doctest::Approx(14.00));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(4.5));
		CHECK(out[1] == doctest::Approx(13.75));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(5.0));
		CHECK(out[1] == doctest::Approx(13.50));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(5.5));
		CHECK(out[1] == doctest::Approx(13.25));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(6.0));
		CHECK(out[1] == doctest::Approx(13.00));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(7.0));
		CHECK(out[1] == doctest::Approx(12.50));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(7.0));
		CHECK(out[1] == doctest::Approx(12.50));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(3.5));
		CHECK(out[1] == doctest::Approx(14.25));

		res.process(get_input, out);
		CHECK(out[0] == doctest::Approx(0));
		CHECK(out[1] == doctest::Approx(16.0));

		// for (auto i = 0; i < 16; i++) {
		// 	res.process(get_input, out);
		// 	printf("%f\t%f\n", out[0], out[1]);
		// }
	}
}
