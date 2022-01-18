#pragma once
#include "patch/patch.hh"
#include <vector>

//72B = 6 vec * 12B ea (data, sz, cap)
struct PatchData {
	std::vector<ModuleTypeSlug> module_slugs;  //32B
	std::vector<InternalCable> int_cables;	   //16B
	std::vector<MappedInputJack> mapped_ins;   //16B
	std::vector<MappedOutputJack> mapped_outs; //8B
	std::vector<StaticParam> static_knobs;	   //8B
	std::vector<MappedKnob> mapped_knobs;	   //16B
};
