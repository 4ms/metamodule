#pragma once
#include "console/pr_dbg.hh"
#include "patch/patch.hh"
#include "util/aligned_allocator.hh"
#include <span>

namespace MetaModule
{

template<size_t NumCores>
struct CableCache {
	CableCache() = default;

	void clear() {
		for (auto &out : _cables) {
			out.clear();
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

		uint16_t outmodule = out.module_id;
		_cables[out_core_id].push_back({{outmodule, out.jack_id}, {in.module_id, in.jack_id}});

		pr_dbg("Cable[%u]: m%u j%u -> m%u j%u\n", out_core_id, out.module_id, out.jack_id, in.module_id, in.jack_id);
	}

	//
	// struct TaggedJack : Jack {
	// 	static constexpr unsigned tag_bit_shift = sizeof(module_id) * 8 - 1;
	// 	static constexpr uint16_t tag = 1 << tag_bit_shift;

	// 	void set_tag() {
	// 		module_id |= tag;
	// 	}
	// 	bool is_tagged() const {
	// 		return module_id & tag;
	// 	}
	// 	uint16_t module_id_only() const {
	// 		return module_id & ~tag;
	// 	}
	// };
	using TaggedJack = Jack;

	struct SingleCable {
		TaggedJack out;
		Jack in;
	};

	// organized by out
	std::array<std::vector<SingleCable>, NumCores> _cables;
};
} // namespace MetaModule
