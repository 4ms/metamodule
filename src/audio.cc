#include "audio.hh"
extern "C" {
#include "codec_i2sx2.h"
#include "codec_i2c.h"
}

//Todo: 24-bit audio

TriangleOscillator triosc{0X100000};
//Todo: compare with Buffer<Frame, kBlockSize>
void Audio::process(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize]) {
	int i=0;
	// for (Frame in_ : in) {
	// 	out[i++] = in_;
	// } 
	// for (Frame& out_ : out) {
	// 	out_.l = (i++) << 8;
	// 	out_.r = (i++) << 8;
	// } 
	for (Frame& out_ : out) {
		out_.l = (int32_t)(triosc.Process() >> 16) - 0x8000;

		// uint32_t top = out_.l & 0x00FF0000;
		// uint32_t bot = out_.l & 0x0000FFFF;
		// out_.r = (top >> 16) | (bot << 16);

//		out_.r = (out_.l > 0x7FFFF) ? -32768 : 32767;

		out_.r = in[i++].r;
	} 
}

Audio::Audio() {
	codec_init(kSampleRate);
	init_audio_DMA(kSampleRate, (int16_t*)tx_buf, (int16_t*)rx_buf, kDMABlockSize * sizeof(Frame));
}

void Audio::start() {
	start_audio();
}

//void Audio::register_callback(void callbackfunc(Frame *in, Frame *out)) {
void Audio::register_callback(void callbackfunc(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize])) {
//	set_audio_callback(reinterpret_cast<void (*)(int32_t*, int32_t*)>(callbackfunc));
	set_audio_callback((void (*)(int32_t*, int32_t*))(callbackfunc));
}