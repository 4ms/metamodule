#pragma once
#include "patch/module_type_slug.hh"
#include <cstdint>
#include <span>
#include <string_view>

namespace MetaModule
{

// Identifies a patch's modules and their order: FNV-1a (32-bit) over each
// module slug followed by '\n'. The VCV Hub computes the same hash over the
// patch it sends, to know if per-module loads belong to the patch in the rack.
inline uint32_t patch_fingerprint(std::span<const BrandModuleSlug> slugs) {
	uint32_t hash = 2166136261u;

	auto add = [&hash](char c) {
		hash ^= static_cast<uint8_t>(c);
		hash *= 16777619u;
	};

	for (auto const &slug : slugs) {
		for (char c : std::string_view{slug})
			add(c);
		add('\n');
	}

	return hash;
}

} // namespace MetaModule
