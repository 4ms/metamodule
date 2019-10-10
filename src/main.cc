#include <stm32f7xx.h>
#include "system.hh"
#include "ui.hh"

System system;
Ui ui;

void audio_loop(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize]) {
// void audio_loop(Frame *in, Frame *out) {
	ui.params.update();
	ui.audio.process(in, out);
}

void main() {
	ui.audio.register_callback(audio_loop);

	while (1) {
		ui.params.read();
	}
}

