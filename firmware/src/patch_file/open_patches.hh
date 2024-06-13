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

	//TODO: return an optional iterator?

	OpenPatch *find(PatchLocHash hash) {
		dump("find");
		if (list.empty())
			return nullptr;

		if (auto it = std::ranges::find(list, hash, &OpenPatch::loc_hash); it != list.end()) {
			return &(*it);
		}
		return nullptr;
	}

	OpenPatch *emplace_back(PatchLocation const &loc) {
		auto &openpatch = list.emplace_back(loc);
		dump("emplace_back");
		return &openpatch;
	}

	bool remove(PatchLocHash hash) {
		auto num_erased = std::erase_if(list, [=](auto &e) { return e.loc_hash == hash; });
		dump("Remove");
		return num_erased > 0;
	}

	void remove_last() {
		list.pop_back();
	}

	void dump(std::string_view header) {
		unsigned i = 0;
		pr_dbg("%s: \n", header.data());
		for (auto &p : list) {
			pr_dbg("[%d] %d:%s: %s #%d\n",
				   i++,
				   p.loc.vol,
				   p.loc.filename.c_str(),
				   p.patch.patch_name.c_str(),
				   p.modification_count);
		}
	}

private:
	std::list<OpenPatch> list;
};

} // namespace MetaModule
