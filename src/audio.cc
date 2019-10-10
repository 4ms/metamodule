#include "audio.hh"
extern "C" {
#include "codec_i2sx2.h"
}


void Audio::process(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize]) {
	int i=0;
	for (Frame in_ : in) {
		out[i++] = in_;
	} 
}

Audio::Audio() {
	init_audio_DMA(48000, (int32_t*)tx_buf, (int32_t*)rx_buf, kBlockSize);
}

//void Audio::register_callback(void callbackfunc(Frame *in, Frame *out)) {
void Audio::register_callback(void callbackfunc(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize])) {
//	set_audio_callback(reinterpret_cast<void (*)(int32_t*, int32_t*)>(callbackfunc));
	set_audio_callback((void (*)(int32_t*, int32_t*))(callbackfunc));
}
