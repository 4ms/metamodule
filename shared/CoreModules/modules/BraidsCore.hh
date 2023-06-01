#pragma once
#include "info/Braids_info.hh"
// #define VCVRACK
#include "platform_module.hh"

//
#include "braids/macro_oscillator.h"
#include "braids/signature_waveshaper.h"
#include "braids/vco_jitter_source.h"

struct BraidsCore : PlatformModule<MetaModule::BraidsInfo, BraidsCore> {
	braids::MacroOscillator osc;
	braids::SettingsData settings;
	braids::VcoJitterSource jitter_source;
	braids::SignatureWaveshaper ws;

	rack::dsp::SampleRateConverter<1> src;
	rack::dsp::DoubleRingBuffer<rack::dsp::Frame<1>, 256> outputBuffer;
	bool lastTrig = false;
	bool lowCpu = false;

	BraidsCore() {
		std::memset(&osc, 0, sizeof(osc));
		osc.Init();
		std::memset(&jitter_source, 0, sizeof(jitter_source));
		jitter_source.Init();
		std::memset(&ws, 0, sizeof(ws));
		ws.Init(0x0000);
		std::memset(&settings, 0, sizeof(settings));

		// List of supported settings
		settings.meta_modulation = 0;
		settings.vco_drift = 0;
		settings.signature = 0;
	}

	void process(const ProcessArgs &args) override {
		using namespace rack::math;
		using namespace rack::dsp;

		// Trigger
		bool trig = inputs[TRIG_INPUT].getVoltage() >= 1.0;
		if (!lastTrig && trig) {
			osc.Strike();
		}
		lastTrig = trig;

		// Render frames
		if (outputBuffer.empty()) {
			float fm = params[FM_PARAM].getValue() * inputs[FM_INPUT].getVoltage();

			// Set shape
			int shape = std::round(params[SHAPE_PARAM].getValue() * braids::MACRO_OSC_SHAPE_LAST_ACCESSIBLE_FROM_META);
			if (settings.meta_modulation) {
				shape += std::round(fm / 10.0 * braids::MACRO_OSC_SHAPE_LAST_ACCESSIBLE_FROM_META);
			}
			settings.shape = clamp(shape, 0, braids::MACRO_OSC_SHAPE_LAST_ACCESSIBLE_FROM_META);

			// Setup oscillator from settings
			osc.set_shape((braids::MacroOscillatorShape)settings.shape);

			// Set timbre/modulation
			float timbre = params[TIMBRE_PARAM].getValue() +
						   params[MODULATION_PARAM].getValue() * inputs[TIMBRE_INPUT].getVoltage() / 5.0;
			float modulation = params[COLOR_PARAM].getValue() + inputs[COLOR_INPUT].getVoltage() / 5.0;
			int16_t param1 = rescale(clamp(timbre, 0.0f, 1.0f), 0.0f, 1.0f, 0, INT16_MAX);
			int16_t param2 = rescale(clamp(modulation, 0.0f, 1.0f), 0.0f, 1.0f, 0, INT16_MAX);
			osc.set_parameters(param1, param2);

			// Set pitch
			float pitchV = inputs[PITCH_INPUT].getVoltage() + params[COARSE_PARAM].getValue() +
						   params[FINE_PARAM].getValue() / 12.0;
			if (!settings.meta_modulation)
				pitchV += fm;
			if (lowCpu)
				pitchV += std::log2(96000.f * args.sampleTime);
			int32_t pitch = (pitchV * 12.0 + 60) * 128;
			pitch += jitter_source.Render(settings.vco_drift);
			pitch = clamp(pitch, 0, 16383);
			osc.set_pitch(pitch);

			// TODO: add a sync input buffer (must be sample rate converted)
			uint8_t sync_buffer[24] = {};

			int16_t render_buffer[24];
			osc.Render(sync_buffer, render_buffer, 24);

			// Signature waveshaping, decimation (not yet supported), and bit reduction (not yet supported)
			uint16_t signature = settings.signature * settings.signature * 4095;
			for (size_t i = 0; i < 24; i++) {
				const int16_t bit_mask = 0xffff;
				int16_t sample = render_buffer[i] & bit_mask;
				int16_t warped = ws.Transform(sample);
				render_buffer[i] = stmlib::Mix(sample, warped, signature);
			}

			if (lowCpu) {
				for (int i = 0; i < 24; i++) {
					rack::dsp::Frame<1> f;
					f.samples[0] = render_buffer[i] / 32768.0;
					outputBuffer.push(f);
				}
			} else {
				// Sample rate convert
				rack::dsp::Frame<1> in[24];
				for (int i = 0; i < 24; i++) {
					in[i].samples[0] = render_buffer[i] / 32768.0;
				}
				src.setRates(96000, args.sampleRate);

				int inLen = 24;
				int outLen = outputBuffer.capacity();
				src.process(in, &inLen, outputBuffer.endData(), &outLen);
				outputBuffer.endIncr(outLen);
			}
		}

		// Output
		if (!outputBuffer.empty()) {
			rack::dsp::Frame<1> f = outputBuffer.shift();
			outputs[OUT_OUTPUT].setVoltage(5.0 * f.samples[0]);
		}
	}
};
