#include "audio.hh"
extern "C" {
#include "i2c.h"
#include "codec_i2sx2.h"
#include "codec_i2c.h"
}
//Todo: 24-bit audio
//Todo: 96kHz

void Audio::process(Params &params, Block& in, Block& out) {
	//VCA:
	auto in_ = in.begin();
	for (auto & out_ : out) {
		out_.l = params.freq[0] * in_->l;
		out_.r = params.freq[1] * in_->r;
		in_++;
	}
}

void Audio::start() {
	i2c_init();
	codec_init(kSampleRate);
	init_audio_DMA(kSampleRate, reinterpret_cast<int16_t *>(tx_buf_.data()), reinterpret_cast<int16_t *>(rx_buf_.data()), kDMABlockSize * sizeof(Frame));
	start_audio();
}

void Audio::register_callback(void callbackfunc(Block& in, Block& out)) {
	//	set_audio_callback(reinterpret_cast<void (*)(int32_t*, int32_t*)>(callbackfunc));
	set_audio_callback((void (*)(int32_t*, int32_t*))(callbackfunc));
}
