#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/moduleFactory.hh"
#include "CoreModules/module_type_slug.hh"
#include <cstdio>

namespace MetaModule
{

struct DumpModuleInfo {

	static void print(BrandModuleSlug slug) {

		auto info = ModuleFactory::getModuleInfo(slug);

		for (unsigned i = 0; auto &el : info.elements) {
			auto base = MetaModule::base_element(el);
			auto count = ElementCount::count(el);

			printf("[%d] ", i);
			printf("type=%zu ", el.index());
			printf("xy=%f,%f ", base.x_mm, base.y_mm);
			printf("\"%.*s\" ", (int)base.short_name.size(), base.short_name.data());
			printf("p:%zu i:%zu o:%zu l:%zu ", count.num_params, count.num_inputs, count.num_outputs, count.num_lights);
			printf("\n");
			i++;
		}
	}
};
} // namespace MetaModule
