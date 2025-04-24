#pragma once
#include "conf/patch_conf.hh"
#include "console/pr_dbg.hh"
#include "patch/patch.hh"
#include "util/aligned_allocator.hh"
#include <span>

namespace MetaModule
{

template<size_t NumCores>
struct CableCache {
	CableCache() = default;

	struct CableIn {
		uint16_t jack_id;
		uint16_t out_cache_idx : 15;
		uint16_t out_core_id : 1;
		// uint32_t out_core_id;
	};

	void clear() {
		for (auto &out : outvals)
			out.clear();
		for (auto &out : outjacks)
			out.clear();
		for (auto &in : ins)
			in.clear();
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
			// Find which core the module belongs to
			auto out_core_id = find_core(cable.out.module_id, module_cores);

			if (out_core_id == NumCores)
				continue; //error: bad module_id in the cable

			auto &outjack = outjacks[out_core_id].emplace_back();
			outvals[out_core_id].push_back(0);
			outjack.module_id = cable.out.module_id;
			outjack.jack_id = cable.out.jack_id;

			printf("CableCache::build(): cable m:%u j:%u c:%u ", cable.out.module_id, cable.out.jack_id, out_core_id);

			for (auto &in : cable.ins) {
				if (in.module_id < ins.size()) {
					// Tag output jacks if one or more inputs is on another core
					auto in_core_id = find_core(in.module_id, module_cores);
					if (in_core_id != out_core_id) {
						outjack.set_tag();
						printf("(tag) ");
					}
					printf("-> m:%u j:%u c:%u [%u %zu]",
						   in.module_id,
						   in.jack_id,
						   in_core_id,
						   out_core_id,
						   outvals[out_core_id].size() - 1);
					CableIn c;
					c.jack_id = in.jack_id;
					c.out_cache_idx = outvals[out_core_id].size() - 1;
					c.out_core_id = out_core_id;
					ins[in.module_id].push_back(c);
				}
			}

			printf("\n");
		}
		printf("Built %zu cables -> %zu\n", cables.size(), outjacks.size());
	}

	template<typename SpanT>
	void add(Jack in, Jack out, std::array<SpanT, NumCores> const &module_cores) {
		// Find which core the module belongs to
		auto out_core_id = find_core(out.module_id, module_cores);
		if (out_core_id == NumCores)
			return;
		auto in_core_id = find_core(in.module_id, module_cores);
		if (in_core_id == NumCores)
			return;

		outvals[out_core_id].push_back(0);
		outjacks[out_core_id].push_back({out.module_id, out.jack_id});

		// Tag output jacks if one or more inputs is on another core
		if (in_core_id != out_core_id) {
			outjacks[out_core_id][outjacks[out_core_id].size() - 1].set_tag();
		}

		CableIn c;
		c.jack_id = in.jack_id;
		c.out_cache_idx = outvals[out_core_id].size() - 1;
		c.out_core_id = out_core_id;
		ins[in.module_id].push_back(c);

		printf("Add cables -> %zu/%zu\n", outjacks[0].size(), outjacks[1].size());
	}

	// ins[N] are the cables connected to module id N
	std::array<std::vector<CableIn>, MAX_MODULES_IN_PATCH> ins;

	struct TaggedJack : Jack {
		static constexpr unsigned tag_bit_shift = sizeof(module_id) * 8 - 1;
		static constexpr uint16_t tag = 1 << tag_bit_shift;

		void set_tag() {
			// module_id |= tag;
		}
		bool is_tagged() const {
			return false;
			// return module_id & tag;
		}
		uint16_t module_id_only() const {
			return module_id;
			// return module_id & ~tag;
		}
	};

	// Struct of arrays:
	std::array<std::vector<float, AlignedAllocator<float, 64>>, NumCores> outvals;
	std::array<std::vector<TaggedJack, AlignedAllocator<TaggedJack, 64>>, NumCores> outjacks;
};
} // namespace MetaModule
