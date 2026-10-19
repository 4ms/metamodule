#pragma once
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

// Stands in for MP1's AudioStream (audio/audio.cc) until it's ported: called once per audio block
// from the codec's DMA interrupt, it answers the patch loader's requests to stop and start audio
// (the GUI waits for these before it loads or changes a patch), but doesn't play the patch.
class AudioStandIn {
public:
	AudioStandIn(PatchPlayLoader &loader)
		: loader{loader} {
	}

	// Same handshake as AudioStream::handle_fade_inout(), without the fade
	void process() {
		if (loader.should_fade_down_audio()) {
			loader.notify_audio_is_muted();

		} else if (loader.should_fade_up_audio()) {
			loader.notify_audio_not_muted();
			loader.notify_audio_done_starting();
		}
	}

private:
	PatchPlayLoader &loader;
};

} // namespace MetaModule
