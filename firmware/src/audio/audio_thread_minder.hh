#pragma once
#include "audio/audio.hh"
#include "patch_play/patch_player.hh"

namespace MetaModule
{

struct AudioThreadMinder {
	AudioThreadMinder() = delete;

	static inline AudioStream *_audio_stream = nullptr;
	static inline PatchPlayer *_player = nullptr;

	static void register_audio_stream(AudioStream &audio) {
		_audio_stream = &audio;
	}

	static AudioStream *audio_stream() {
		return _audio_stream;
	}

	static void register_player(PatchPlayer &player) {
		_player = &player;
	}

	static PatchPlayer *player() {
		return _player;
	}
};

} // namespace MetaModule
