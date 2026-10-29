#pragma once
#include "params/encoder_clicks.hh"
#include "params/params_state.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>

namespace MetaModule
{

// Pro: turns the params mapped to the panel encoders (PatchPlayer::step_panel_encoder()), with
// acceleration: a slow turn moves a param SlowStep (of its mapped range) per click, and a fast turn
// up to FastStep per click.
// With no panel encoders (MP1), it's empty and does nothing.
template<unsigned NumEncoders>
class PanelEncoders {
	static constexpr float SlowStep = 0.01f;
	static constexpr float FastStep = 0.05f;

	// Time between clicks of a slow turn and of a fast turn
	static constexpr float SlowClickSec = 0.080f;
	static constexpr float FastClickSec = 0.020f;

	// Frames since each encoder's last click (up to a second). Before the first click, it's long ago.
	static constexpr uint32_t LongAgo = UINT32_MAX / 2;
	std::array<uint32_t, NumEncoders> frames_since_click{};

	// The GUI reads the knobs' changed flags less often than once a block, and each block's flags
	// replace the last's (SyncParams::write_sync()). So a click keeps its encoder's flag set this long.
	static constexpr float ChangedSec = 0.100f;

public:
	PanelEncoders() {
		frames_since_click.fill(LongAgo);
	}

	// Once per param block, with the patch playing.
	// block_frames: the frames since the last block
	void process(EncoderClicks<NumEncoders> const &enc,
				 uint32_t block_frames,
				 uint32_t sample_rate,
				 auto &player,
				 ParamsState &param_state) {
		update(enc, block_frames, sample_rate, param_state, [&player](unsigned i, int clicks, float step) {
			player.step_panel_encoder(i, clicks, step);
		});
	}

	// Once per param block, with no patch playing: the clicks are dropped, but the GUI is told
	void mark_moved(EncoderClicks<NumEncoders> const &enc,
					uint32_t block_frames,
					uint32_t sample_rate,
					ParamsState &param_state) {
		update(enc, block_frames, sample_rate, param_state, [](unsigned, int, float) {});
	}

	static constexpr float step_size(float click_sec) {
		auto speed = std::clamp((SlowClickSec - click_sec) / (SlowClickSec - FastClickSec), 0.f, 1.f);
		return SlowStep + speed * (FastStep - SlowStep);
	}

private:
	void update(EncoderClicks<NumEncoders> const &enc,
				uint32_t block_frames,
				uint32_t sample_rate,
				ParamsState &param_state,
				auto step_encoder) {
		for (unsigned i = 0; i < NumEncoders; i++) {
			auto &frames = frames_since_click[i];
			frames = std::min(frames + block_frames, sample_rate);

			if (int clicks = enc.clicks[i]; clicks != 0) {
				// The block's clicks are spread over the time since the last click
				float click_sec = float(frames) / float(sample_rate) / float(std::abs(clicks));
				frames = 0;

				step_encoder(i, clicks, step_size(click_sec));
			}

			// For the GUI (e.g. turn a knob to map it)
			if (frames < sample_rate * ChangedSec)
				param_state.knobs[i].changed = true;
		}
	}
};

template<>
class PanelEncoders<0> {
public:
	void process(auto const &...) {
	}

	void mark_moved(auto const &...) {
	}
};

} // namespace MetaModule
