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
	current_fx[LEFT] = AudioProcessorList::FX[0];
	current_fx[RIGHT] = AudioProcessorList::FX[0];
	register_callback(Audio::process);
}

void Audio::process(AudioStreamBlock &in, AudioStreamBlock &out)
{
	const float scaling = static_cast<float>(in.begin()->MaxValue);
	instance->params.update();
	current_fx[LEFT]->set_param(0, instance->params.freq[0]);
	current_fx[LEFT]->set_param(1, instance->params.res[0]);
	current_fx[RIGHT]->set_param(0, instance->params.freq[1]);
	current_fx[RIGHT]->set_param(1, instance->params.res[1]);

	auto in_ = in.begin();
	for (auto &out_ : out) {
		out_.l = scaling * current_fx[LEFT]->update(in_->l / scaling); // * cf + next_fx[LEFT]->update(in_->l) * (1.0F-cf);
		out_.r = scaling * current_fx[RIGHT]->update(in_->r / scaling);
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
