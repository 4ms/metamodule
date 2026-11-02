#pragma once
#include "patch_file/open_patch_manager.hh"
#include "patch_play/live_overhead.hh"
#include "patch_play/patch_playloader.hh"
#include "wifi/live_detail_request.hh"
#include "wifi/wifi_live_block.hh"
#include <algorithm>

namespace MetaModule
{

// Publishes the playing patch's live loads for the Wi-Fi interface (M4),
// and turns per-module measurement on while a Wi-Fi client asks for it.
class WifiLivePublisher {
public:
	static constexpr uint32_t UpdateIntervalMs = 250;

	WifiLivePublisher(OpenPatchManager &patches, PatchPlayLoader &playloader)
		: patches{patches}
		, playloader{playloader} {
	}

	// nullptr: no Wi-Fi (e.g. simulator)
	void set_block(WifiLiveBlock *wifi_block) {
		block = wifi_block;
	}

	void update(uint32_t now_ms) {
		if (!block || (now_ms - last_update_ms) < UpdateIntervalMs)
			return;
		last_update_ms = now_ms;

		// Per-module loads are only measured from the next audio block on after turning detail on
		bool was_detailed = playloader.is_live_load_detailed();
		playloader.set_live_load_detail_remote(detail_request.update(block->detail_requests(), now_ms));

		WifiLiveData data{};
		auto *patch = patches.get_playing_patch();
		data.playing = patch && playloader.is_playing();

		if (patch) {
			data.patch_name = patch->patch_name;

			auto live = playloader.get_live_load();
			data.overhead = live_overhead(live, patch->module_cores).total_tenths();
			data.modules_valid = live.valid && was_detailed && playloader.is_live_load_detailed();

			auto num = std::min<size_t>(patch->module_slugs.size(), data.modules.size());
			data.num_modules = static_cast<uint16_t>(num);
			std::copy_n(live.modules.begin(), std::min(num, live.modules.size()), data.modules.begin());
		}

		block->publish(data);
	}

private:
	OpenPatchManager &patches;
	PatchPlayLoader &playloader;
	WifiLiveBlock *block = nullptr;
	LiveDetailRequest detail_request;
	uint32_t last_update_ms = 0;
};

} // namespace MetaModule
