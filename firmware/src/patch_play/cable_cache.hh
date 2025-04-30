#pragma once
#include "console/pr_dbg.hh"
#include "patch/patch.hh"
#include "util/fixed_vector.hh"
#include <span>

namespace MetaModule
{

template<size_t NumCores>
struct CableCache {
	CableCache() = default;

	void clear() {
		for (auto &cable : samecore_cables) {
			cable.clear();
		}
		for (auto &cable : diffcore_cables) {
			cable.clear();
		}
	}

	template<typename SpanT>
	unsigned find_core(uint16_t module_id, std::array<SpanT, NumCores> const &module_cores) {
		for (auto i = 0u; auto &modules : module_cores) {
			if (std::ranges::find(modules, module_id) != modules.end()) {
				return i;
			}
			i++;
		}
		return NumCores;
	}

	template<typename SpanT>
	void build(std::span<const InternalCable> cables, std::array<SpanT, NumCores> const &module_cores) {
		clear();

		for (auto const &cable : cables) {
			for (auto const &in : cable.ins) {
				add(in, cable.out, module_cores);
			}
		}
	}

	template<typename SpanT>
	void add(Jack in, Jack out, std::array<SpanT, NumCores> const &module_cores) {
		auto out_core_id = find_core(out.module_id, module_cores);
		if (out_core_id == NumCores)
			return;

		auto in_core_id = find_core(in.module_id, module_cores);
		if (in_core_id == NumCores)
			return;

		auto &_cables = (in_core_id == out_core_id) ? samecore_cables : diffcore_cables;

		bool added = false;
		if (auto found = std::ranges::find(_cables[out_core_id], out, &SingleCable::out);
			found != _cables[out_core_id].end())
		{
			added = found->ins.push_back(in);
		}

		if (!added) {
			_cables[out_core_id].push_back({.out = out});
			_cables[out_core_id][_cables[out_core_id].size() - 1].ins.push_back(in);
		}

		pr_trace("Cable[%u]: m%u j%u -> m%u j%u\n", out_core_id, out.module_id, out.jack_id, in.module_id, in.jack_id);
	}

	struct SingleCable {
		Jack out;
		FixedVector<Jack, 4> ins;
	};

	// organized by out
	std::array<std::vector<SingleCable>, NumCores> diffcore_cables;
	std::array<std::vector<SingleCable>, NumCores> samecore_cables;
};
} // namespace MetaModule
