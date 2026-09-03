#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

// Measures the modules again and picks a new way to split them between the cores.
// Only meaningful while the patch is playing.
void PatchPlayLoader::recalculate_load_balance() {
	if (!player_.is_loaded)
		return;

	AudioPause pause{*this};

	player_.rebalance_modules(PatchPlayer::Balance::Recalculate);
	copy_load_balance_to_patch();
}

// Puts back a load balance the user had before (Undo), without re-measuring
void PatchPlayLoader::apply_load_balance(std::vector<uint16_t> const &module_cores,
										 std::vector<uint32_t> const &module_loads) {
	if (!player_.is_loaded)
		return;

	AudioPause pause{*this};

	player_.set_load_balance(module_cores, module_loads);
	copy_load_balance_to_patch();
}

// The player works on its own copy of the patch data, so the load balance it
// calculated has to be copied back into the open patch in order to be saved.
void PatchPlayLoader::copy_load_balance_to_patch() {
	auto *patch = patches_.get_playing_patch();
	if (!patch)
		return;

	patch->module_cores = player_.get_module_cores();
	patch->module_loads = player_.get_module_loads();
}

} // namespace MetaModule
