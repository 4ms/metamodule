#pragma once
#include "CoreModules/moduleFactory.hh"
#include "console/pr_dbg.hh"
#include "glue/AudibleInstruments/info/Blinds_info.hh"
#include "glue/AudibleInstruments/info/Braids_info.hh"
#include "glue/AudibleInstruments/info/Branches_info.hh"
#include "glue/AudibleInstruments/info/Clouds_info.hh"
#include "glue/AudibleInstruments/info/Elements_info.hh"
#include "glue/AudibleInstruments/info/Frames_info.hh"
#include "glue/AudibleInstruments/info/Kinks_info.hh"
#include "glue/AudibleInstruments/info/Links_info.hh"
#include "glue/AudibleInstruments/info/Marbles_info.hh"
#include "glue/AudibleInstruments/info/Plaits_info.hh"
#include "glue/AudibleInstruments/info/Rings_info.hh"
#include "glue/AudibleInstruments/info/Ripples_info.hh"
#include "glue/AudibleInstruments/info/Shades_info.hh"
#include "glue/AudibleInstruments/info/Shelves_info.hh"
#include "glue/AudibleInstruments/info/Stages_info.hh"
#include "glue/AudibleInstruments/info/Streams_info.hh"
#include "glue/AudibleInstruments/info/Tides2_info.hh"
#include "glue/AudibleInstruments/info/Tides_info.hh"
#include "glue/AudibleInstruments/info/Veils_info.hh"
#include "glue/AudibleInstruments/info/Warps_info.hh"
#include <plugin/Model.hpp>

namespace MetaModule::AudibleInstruments
{

inline std::string_view get_display_name(std::string_view slug) {
	if (slug == "Blinds")
		return "Quad Attenuverter";
	if (slug == "Braids")
		return "Algorithm VCO";
	if (slug == "Branches")
		return "Random Router";
	if (slug == "Clouds")
		return "Granulation";
	if (slug == "Elements")
		return "Modeler";
	if (slug == "Frames")
		return "Keyframes";
	if (slug == "Kinks")
		return "Rect-Logic-S&H";
	if (slug == "Links")
		return "Split-Combine";
	if (slug == "Marbles")
		return "Random-maker";
	if (slug == "Plaits")
		return "Algorithm VCO II";
	if (slug == "Rings")
		return "Resonator";
	if (slug == "Ripples")
		return "VC Filter";
	if (slug == "Shades")
		return "Triple Mix";
	if (slug == "Shelves")
		return "Multi-filter";
	if (slug == "Stages")
		return "Slope Sequencer";
	if (slug == "Streams")
		return "Compressing Filter";
	if (slug == "Tides")
		return "Envelopes";
	if (slug == "Tides2")
		return "Envelopes II";
	if (slug == "Veils")
		return "Quad VCA";
	if (slug == "Warps")
		return "Mod Osc";
	return "";
}

inline bool addModel(rack::plugin::Plugin *p, rack::plugin::Model *model) {
	if (!model || !p)
		return false;

	std::string_view slug = model->slug;
	std::string_view brand = p->slug;

	if (brand != "AudibleInstruments")
		return false;

	if (ModuleFactory::isValidBrandModule(brand, slug)) {
		pr_err("Duplicate module: %s:%s, skipping\n", brand.data(), slug.data());
		return false;
	}

	pr_trace("Adding VCV_adaptor model %s:%s\n", brand.data(), slug.data());

	auto get_info_view = [&](std::string_view slug) -> std::optional<ModuleInfoView> {
		if (model->slug == "Blinds")
			return ModuleInfoView::makeView<BlindsInfo>();
		if (model->slug == "Braids")
			return ModuleInfoView::makeView<BraidsInfo>();
		if (model->slug == "Branches")
			return ModuleInfoView::makeView<BranchesInfo>();
		if (model->slug == "Clouds")
			return ModuleInfoView::makeView<CloudsInfo>();
		if (model->slug == "Elements")
			return ModuleInfoView::makeView<ElementsInfo>();
		if (model->slug == "Frames")
			return ModuleInfoView::makeView<FramesInfo>();
		if (model->slug == "Kinks")
			return ModuleInfoView::makeView<KinksInfo>();
		if (model->slug == "Links")
			return ModuleInfoView::makeView<LinksInfo>();
		if (model->slug == "Marbles")
			return ModuleInfoView::makeView<MarblesInfo>();
		if (model->slug == "Plaits")
			return ModuleInfoView::makeView<PlaitsInfo>();
		if (model->slug == "Rings")
			return ModuleInfoView::makeView<RingsInfo>();
		if (model->slug == "Ripples")
			return ModuleInfoView::makeView<RipplesInfo>();
		if (model->slug == "Shades")
			return ModuleInfoView::makeView<ShadesInfo>();
		if (model->slug == "Shelves")
			return ModuleInfoView::makeView<ShelvesInfo>();
		if (model->slug == "Stages")
			return ModuleInfoView::makeView<StagesInfo>();
		if (model->slug == "Streams")
			return ModuleInfoView::makeView<StreamsInfo>();
		if (model->slug == "Tides")
			return ModuleInfoView::makeView<TidesInfo>();
		if (model->slug == "Tides2")
			return ModuleInfoView::makeView<Tides2Info>();
		if (model->slug == "Veils")
			return ModuleInfoView::makeView<VeilsInfo>();
		if (model->slug == "Warps")
			return ModuleInfoView::makeView<WarpsInfo>();

		return std::nullopt;
	};

	if (auto view = get_info_view(slug)) {
		model->plugin = p;
		std::string faceplate = p->slug + "/" + model->slug + ".png";

		ModuleFactory::registerModuleType(brand, slug, model->creation_func, *view, faceplate);
		std::string combined_slug = p->slug + ":" + model->slug;
		ModuleFactory::setModuleDisplayName(combined_slug, get_display_name(slug));
		ModuleFactory::setBrandDisplayName(p->slug, "ClonedInstruments");
		return true;
	}

	pr_err("Info not found for %s:%s, adding normally.\n", brand.data(), slug.data());

	p->addModel(model);

	return false;
}

} // namespace MetaModule::AudibleInstruments
