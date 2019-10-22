#include "audio.hh"
extern "C" {
#include "codec_i2sx2.h"
#include "codec_i2c.h"
}

//Todo: 24-bit audio
//Todo: 96kHz


TriangleOscillator triosc{0X100000};

void Audio::process(Block& in, Block& out) {
	int i=0;
	// for (Frame in_ : in) {
	// 	out[i++] = in_;
	// } 
	// for (Frame& out_ : out) {
	// 	out_.l = (i++) << 8;
	// 	out_.r = (i++) << 8;
	// } 
		// uint32_t top = out_.l & 0x00FF0000;
		// uint32_t bot = out_.l & 0x0000FFFF;
		// out_.r = (top >> 16) | (bot << 16);
//		out_.r = (out_.l > 0x7FFFF) ? -32768 : 32767;

	for (Frame& out_ : out) {
		out_.l = (int16_t)(triosc.Process() >> 16) - 0x8000;
		uint32_t vca = (in[i].r * out_.l);
		out_.r = vca >> 16;
		i++;
	} 
}

Audio::Audio() {
	codec_init(kSampleRate);
	init_audio_DMA(kSampleRate, (int16_t*)tx_buf_, (int16_t*)rx_buf_, kDMABlockSize * sizeof(Frame));
}

void Audio::start() {
	start_audio();
}

void Audio::register_callback(void callbackfunc(Block& in, Block& out)) {
	//	set_audio_callback(reinterpret_cast<void (*)(int32_t*, int32_t*)>(callbackfunc));
	set_audio_callback((void (*)(int32_t*, int32_t*))(callbackfunc));
}