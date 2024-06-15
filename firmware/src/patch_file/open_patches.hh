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
		if (list.empty())
			return nullptr;

		if (auto it = std::ranges::find(list, hash, &OpenPatch::loc_hash); it != list.end()) {
			return &(*it);
		}
		return nullptr;
	}

	OpenPatch *emplace_back(PatchLocation const &loc) {
		auto &openpatch = list.emplace_back(loc);
		dump();
		return &openpatch;
	}

	bool remove(PatchLocHash hash) {
		auto num_erased = std::erase_if(list, [=](auto &e) { return e.loc_hash == hash; });
		dump();
		return num_erased > 0;
	}

	void remove_last() {
		list.pop_back();
	}

private:
	void dump() {
		unsigned i = 0;
		size_t total_size = 0;

		pr_dbg("________\n");
		for (auto &p : list) {
			auto sz = p.patch.patch_size();
			total_size += sz;
			pr_dbg("[%d] %d:%s: %s #%d [%zu B]\n",
				   i++,
				   p.loc.vol,
				   p.loc.filename.c_str(),
				   p.patch.patch_name.c_str(),
				   p.modification_count,
				   sz);
		}
		pr_dbg("TOTAL: %zu\n", total_size);
		pr_dbg("________\n");
	}

private:
	std::list<OpenPatch> list;
};

} // namespace MetaModule
