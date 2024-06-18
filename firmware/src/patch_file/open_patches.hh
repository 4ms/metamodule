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
			pr_dbg("range found\n");
			return &(*it);
		}
		return nullptr;
	}

	Volume get_vol(std::string_view filename) const {
		if (!list.empty()) {

			auto it = std::ranges::find_if(list, [&filename](auto &entry) { return entry.loc.filename == filename; });
			if (it != list.end()) {
				return it->loc.vol;
			}
		}

		return Volume::RamDisk;
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

	bool remove_oldest_unmodified() {
		auto oldest_unmod = std::ranges::find_if(list, [](auto &entry) { return entry.modification_count == 0; });
		if (oldest_unmod == list.end()) {
			return false;
		} else {
			list.erase(oldest_unmod);
			return true;
		}
	}

	void remove_last() {
		list.pop_back();
	}

	auto begin() {
		return list.begin();
	}
	auto end() {
		return list.end();
	}
	auto begin() const {
		return list.cbegin();
	}
	auto end() const {
		return list.cend();
	}
	auto size() const {
		return list.size();
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
