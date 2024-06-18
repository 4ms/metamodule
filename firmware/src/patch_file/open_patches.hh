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
		return &openpatch;
	}

	bool remove(PatchLocHash hash) {
		auto num_erased = std::erase_if(list, [=](auto &e) { return e.loc_hash == hash; });
		return num_erased > 0;
	}

	void remove(std::list<OpenPatch>::iterator item) {
		list.erase(item);
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
	void dump_open_patches() {
		unsigned i = 0;
		size_t total_size = 0;

		for (auto &p : list) {
			auto sz = patch_size(p.patch);
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
	}

	static size_t patch_size(PatchData const &p) {
		auto sz = sizeof(PatchData);
		sz += p.module_slugs.size() * sizeof(BrandModuleSlug);

		sz += p.int_cables.size() * sizeof(InternalCable);
		for (auto const &cable : p.int_cables)
			sz += cable.ins.size() * sizeof(Jack);

		sz += p.mapped_ins.size() * sizeof(MappedInputJack);
		for (auto const &in : p.mapped_ins)
			sz += in.ins.size() * sizeof(Jack);

		sz += p.mapped_outs.size() * sizeof(MappedOutputJack);

		sz += p.static_knobs.size() * sizeof(StaticParam);

		sz += p.knob_sets.size() * sizeof(MappedKnobSet);
		for (auto const &knob_set : p.knob_sets)
			sz += knob_set.set.size() * sizeof(MappedKnob);

		sz += p.module_states.size() * sizeof(ModuleInitState);
		for (auto const &state : p.module_states)
			sz += state.state_data.size() * sizeof(char);

		sz += p.midi_maps.set.size() * sizeof(MappedKnob);

		return sz;
	}

private:
	std::list<OpenPatch> list;
};

} // namespace MetaModule
