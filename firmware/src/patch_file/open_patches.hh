#pragma once

#include "console/pr_dbg.hh"
#include "patch_data.hh"
#include "patch_file/patch_location.hh"
#include <list>

namespace MetaModule
{

struct OpenPatch {
	OpenPatch(PatchLocation const &loc)
		: loc_hash{loc}
		, loc{loc} {
	}

	PatchLocHash loc_hash{};
	PatchLocation loc{};
	PatchData patch{};
	unsigned modification_count = 0;
};

struct OpenPatchList {

	PatchData *find(PatchLocHash hash) {
		dump();
		if (auto it = std::ranges::find(list, hash, &OpenPatch::loc_hash); it != list.end()) {
			return &(it->patch);
		}
		return nullptr;
	}

	bool rename_file(PatchLocHash old_loc, std::string_view new_name, Volume new_vol) {
		pr_dbg("rename\n");
		if (auto it = std::ranges::find(list, old_loc, &OpenPatch::loc_hash); it != list.end()) {
			it->loc_hash = PatchLocHash{new_name, new_vol};
			it->loc.filename.copy(new_name);
			it->loc.vol = new_vol;
			dump();
			return true;
		}
		dump();
		return false;
	}

	PatchData *emplace_back(PatchLocation const &loc) {
		auto &openpatch = list.emplace_back(loc);
		pr_dbg("emplace_back\n");
		dump();
		return &openpatch.patch;
	}

	void remove(PatchLocHash hash) {
		list.remove_if([=](auto &e) { return e.loc_hash == hash; });
		pr_dbg("removed\n");
		dump();
	}

	void remove_last() {
		list.pop_back();
	}

	void dump() {
		unsigned i = 0;
		for (auto &p : list) {
			pr_dbg("[%d] %d/%s: %s\n", i++, p.loc.vol, p.loc.filename.c_str(), p.patch.patch_name);
		}
	}

private:
	std::list<OpenPatch> list;
};

} // namespace MetaModule
