#include "patch/patch.hh"
#include <vector>

//TODO: move this to patch.hh?
struct PatchData {
	std::vector<ModuleTypeSlug> module_slugs;
	std::vector<InternalCable> int_cables;
	std::vector<MappedInputJack> mapped_ins;
	std::vector<MappedOutputJack> mapped_outs;
	std::vector<StaticParam> static_knobs;
	std::vector<MappedKnob> mapped_knobs;
};
