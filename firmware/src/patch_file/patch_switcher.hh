#pragma once
#include "gui/pages/missing_plugin_scan.hh"
#include "patch_file/reload_patch.hh"
#include "patch_play/patch_playloader.hh"
#include "src/misc/lv_timer.h"

namespace MetaModule
{

struct PatchSwitcher {
	// // Pending:
	// enum Result { Idle, Pending, Sucess, Failure };

	// // Switches to a patch.
	// // Handles all cases of patch's state: open/closed, un/modified via disk/wifi, un/modified in ram, missing plugins or not, is already playing or not, is being viewed or not.
	// Result process_jump_to_patch(PatchLocation patch_loc,
	// 							 ReloadPatch &patchloader,
	// 							 PatchPlayLoader &patch_playloader,
	// 							 MissingPluginAutoload &missing_plugins) {

	// 	return Pending;
	// }
	ReloadPatch &patchloader;
	PatchPlayLoader &patch_playloader;
	MissingPluginScanner &missing_plugins;
	Callback cb;

	PatchSwitcher(ReloadPatch &patchloader, PatchPlayLoader &patch_playloader, MissingPluginScanner &missing_plugins)
		: patchloader{patchloader}
		, patch_playloader{patch_playloader}
		, missing_plugins{missing_plugins} {
	}

	Result jump_to_patch(PatchLocation patch_loc, Callback &&success) {
		cb = std::move(success);

		if (patchloader.needs_reloading(patch_loc)) {
			auto result = patchloader.reload_patch_file(patch_loc, [] { lv_timer_handler(); });
			if (!result.success) {
				return result;
			}
		}
		auto &patches = patchloader.patches;
		patches.start_viewing(patch_loc);

		// If patch is unmodifed in RAM, then check for missing plugins
		if (patches.get_view_patch_modification_count() == 0) {
			missing_plugins.start(patches.get_view_patch(), lv_group_get_default(), [=, this](bool did_reload) {
				// If we loaded new plugins AND the patch was already playing, then reload patch into the player
				if (did_reload && patch_playloader.is_view_patch_playing())
					patch_playloader.request_load_view_patch();
				cb();
			});

		} else {
			// Otherwise the patch has unsaved changes so just view it, don't reload/load anything
			success();
		}
		return {.success = true};
	}
};

} // namespace MetaModule
