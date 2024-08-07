#pragma once
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
#include "shared/CoreModules/moduleFactory.hh"
#include <plugin/Model.hpp>

namespace MetaModule::AudibleInstruments
{

bool addModel(rack::plugin::Plugin *p, rack::plugin::Model *model) {
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
		if (model->slug == "Rings")
			return ModuleInfoView::makeView<RingsInfo>();

		if (model->slug == "Kinks")
			return ModuleInfoView::makeView<KinksInfo>();

		return std::nullopt;
	};

	if (auto view = get_info_view(slug)) {
		model->plugin = p;
		std::string faceplate = p->slug + "/" + model->slug + ".png";

		ModuleFactory::registerModuleType(brand, slug, model->creation_func, *view, faceplate);
		return true;
	}

	pr_err("Info not found for %s:%s, adding normally.\n", brand.data(), slug.data());

	p->addModel(model);

	return false;
}

} // namespace MetaModule::AudibleInstruments
