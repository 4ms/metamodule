#pragma once
#include "conf/patch_conf.hh"
#include "patch/patch_data.hh"
#include <span>

namespace MetaModule
{

struct CableCache {
	CableCache() = default;

	struct CableOut {
		float val;
		uint16_t jack_id;
	};

	struct CableIn {
		uint16_t jack_id;
		uint16_t out_module_id;
		uint16_t out_cache_idx;
		//todo: profile using this instead:
		// CableOut *out;
	};

	void clear() {
		for (auto &out : outs)
			out.clear();
		for (auto &in : ins)
			in.clear();
	}

	void build(std::span<const InternalCable> cables) {
		clear();

		for (auto &cable : cables) {
			if (cable.out.module_id >= outs.size())
				continue;

			auto &out = outs[cable.out.module_id];
			auto out_idx = out.size();
			out.push_back({0.f, cable.out.jack_id});

			for (auto &in : cable.ins) {
				if (in.module_id < ins.size()) {
					ins[in.module_id].push_back({in.jack_id, cable.out.module_id, (uint16_t)out_idx});
				}
			}
		}
	}

	void add(Jack injack, Jack outjack) {
		if (injack.module_id < ins.size() && outjack.module_id < outs.size()) {
			auto &out = outs[outjack.module_id];
			auto out_idx = out.size();
			out.emplace_back(0.f, outjack.jack_id);
			ins[injack.module_id].push_back({injack.jack_id, outjack.module_id, (uint16_t)out_idx});
		}
	}

	// outs[N] and ins[N] are the cables connected to module id N
	std::array<std::vector<CableOut>, MAX_MODULES_IN_PATCH> outs;
	std::array<std::vector<CableIn>, MAX_MODULES_IN_PATCH> ins;
};
} // namespace MetaModule
