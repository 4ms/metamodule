#include "audio.hh"
#include "math.hh"
extern "C" {
#include "codec_i2c.h"
#include "codec_i2sx2.h"
#include "i2c.h"
}

Audio::Audio(Params &p)
	: params(p)
{
	instance = this;
	current_fx[LEFT] = AudioProcessorList::FX_left[0];
	current_fx[RIGHT] = AudioProcessorList::FX_right[0];
	register_callback(Audio::process);
}

void Audio::process(AudioStreamBlock &in, AudioStreamBlock &out)
{
	instance->params.update();
	instance->check_fx_change();
	current_fx[LEFT]->set_param(0, instance->params.freq[0]);
	current_fx[LEFT]->set_param(1, instance->params.res[0]);
	current_fx[RIGHT]->set_param(0, instance->params.freq[1]);
	current_fx[RIGHT]->set_param(1, instance->params.res[1]);

	auto in_ = in.begin();
	for (auto &out_ : out) {
		auto scaled_in = AudioFrame::scaleInput(in_->l);
		auto unscaled_out = current_fx[LEFT]->update(scaled_in);
		out_.l = AudioFrame::scaleOutput(unscaled_out);

		scaled_in = AudioFrame::scaleInput(in_->r);
		unscaled_out = current_fx[RIGHT]->update(scaled_in);
		out_.r = AudioFrame::scaleOutput(unscaled_out);

		in_++;
	}
}

void Audio::start()
{
	//Todo: Use c++ library for audio I2S/SAI from touch-sense project
	i2c_init();
	codec_init(kSampleRate);
	init_audio_DMA(kSampleRate,
				   reinterpret_cast<int16_t *>(tx_buf_.data()),
				   reinterpret_cast<int16_t *>(rx_buf_.data()),
				   kAudioStreamDMABlockSize * sizeof(AudioFrame));
	start_audio();
}

void Audio::register_callback(void callbackfunc(AudioStreamBlock &in, AudioStreamBlock &out))
{
	//Todo: Use c++ library for audio I2S/SAI from touch-sense project
	set_audio_callback((void (*)(int32_t *, int32_t *))(callbackfunc));
}
