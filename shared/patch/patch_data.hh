#pragma once
#include "patch.hh"
#include "util/static_string.hh"
#include <vector>

//72B = 6 vec * 12B ea (data, sz, cap) + patch_name + description
struct PatchData {
	static constexpr size_t DescSize = 255;
	ModuleTypeSlug patch_name{""};
	StaticString<DescSize> description;
	std::vector<ModuleTypeSlug> module_slugs;  //32B
	std::vector<InternalCable> int_cables;	   //16B
	std::vector<MappedInputJack> mapped_ins;   //16B
	std::vector<MappedOutputJack> mapped_outs; //8B
	std::vector<StaticParam> static_knobs;	   //8B
	std::vector<MappedKnob> mapped_knobs;	   //16B
};
