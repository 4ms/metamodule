#include "audio.hh"
extern "C" {
#include "codec_i2sx2.h"
#include "codec_i2c.h"
}


void Audio::process(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize]) {
//Todo: compare with Buffer<int32_t, kBlockSize>
	int i=0;
	for (Frame in_ : in) {
		out[i++] = in_;
	} 
}

Audio::Audio() {
	codec_init(kSampleRate);
	init_audio_DMA(kSampleRate, (int32_t*)tx_buf, (int32_t*)rx_buf, kDMABlockSize);
}

void Audio::start() {
	start_audio();
}

//void Audio::register_callback(void callbackfunc(Frame *in, Frame *out)) {
void Audio::register_callback(void callbackfunc(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize])) {
//	set_audio_callback(reinterpret_cast<void (*)(int32_t*, int32_t*)>(callbackfunc));
	set_audio_callback((void (*)(int32_t*, int32_t*))(callbackfunc));
}
