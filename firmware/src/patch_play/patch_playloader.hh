#pragma once
#include "delay.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/patch_location.hh"
#include "yaml_to_patch.hh"
#include <string_view>

namespace MetaModule
{

struct PatchLoader {

	static PatchData parse(FileStorageProxy &storage, std::string_view patchname, Volume patch_vol) {
		PatchLocation initial_patch_loc{patchname, patch_vol};

		PatchData patch;
		patch.blank_patch("default");

		uint32_t tries = 10000;
		while (--tries) {
			if (storage.request_load_patch(initial_patch_loc))
				break;
		}
		if (tries == 0) {
			pr_err("ERROR: sending request to load initial patch timed out.\n");
			return patch;
		}

		tries = 2000;
		while (--tries) {
			auto message = storage.get_message();

			if (message.message_type == FileStorageProxy::LoadFileOK) {
				auto raw_patch_file = storage.get_patch_data(message.bytes_read);
				if (!yaml_raw_to_patch(raw_patch_file, patch)) {
					pr_err("ERROR: initial patch '%s' could not be parsedu\n", patchname.data());
				}

				break;
			}
			if (message.message_type == FileStorageProxy::LoadFileFailed) {
				pr_err("ERROR: initial patch '%s' failed to load from vol %u\n", patchname.data(), patch_vol);
				break;
			}

			delay_ms(1);
		}

		if (tries == 0) {
			pr_err("ERROR: timed out while waiting for response to request to load initial patch.\n");
			return patch;
		}

		return patch;
	}
};

} // namespace MetaModule
