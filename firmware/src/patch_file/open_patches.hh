#pragma once

#include "patch_data.hh"
#include "patch_file/patch_location.hh"
#include <list>

namespace MetaModule
{

struct OpenPatch {
	PatchLocHash loc_hash{};
	PatchLocation loc{};
	PatchData patch{};
	unsigned modification_count = 0;
};

struct OpenPatchList {
	// using PatchIt = std::list<OpenPatch>::iterator;
	// std::optional<PatchIt>

	PatchData *find(PatchLocHash hash) {
		if (auto it = std::ranges::find(list, hash, &OpenPatch::loc_hash); it != list.end()) {
			// return std::make_optional(it);
			return &(it->patch);
		}
		// return std::nullopt;
		return nullptr;
	}

	PatchData &emplace_back(PatchLocation const &loc) {
		return list.emplace_back(PatchLocHash{loc}, loc, PatchData{}, 0).patch;
	}

	void remove(PatchLocHash hash) {
		std::ranges::remove(list, hash, &OpenPatch::loc_hash);
	}

	void remove_last() {
		list.pop_back();
	}

private:
	std::list<OpenPatch> list;
};

} // namespace MetaModule
