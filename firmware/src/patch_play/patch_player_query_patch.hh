#pragma once

#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "conf/patch_conf.hh"
#include "console/pr_dbg.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "util/countzip.hh"
#include <array>
#include <memory>
#include <ranges>
#include <vector>
namespace MetaModule
{

struct PatchQuery {

	PatchQuery(std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> &modules, PatchData &pd)
		: modules{modules}
		, pd{pd} {
	}

	std::vector<ModuleInitState> get_module_states() {
		std::vector<ModuleInitState> states;
		states.reserve(pd.module_slugs.size());

		for (auto module_id : std::views::iota(0u, pd.module_slugs.size())) {
			if (modules[module_id]) {
				if (auto state_data = modules[module_id]->save_state(); state_data.size() > 0)
					states.push_back({module_id, state_data});
			}
		}

		return states;
	}

	std::vector<StaticParam> get_all_params() {
		std::vector<StaticParam> params;

		for (unsigned module_id = 0; auto const &slug : pd.module_slugs) {

			// Skip module 0 (Hub)
			if (module_id > 0 && modules[module_id]) {
				auto num_params = ElementCount::count(ModuleFactory::getModuleInfo(slug).elements).num_params;

				params.reserve(params.size() + num_params);

				for (auto param_id : std::views::iota(0u, num_params)) {
					auto val = modules[module_id]->get_param(param_id);
					params.push_back({uint16_t(module_id), uint16_t(param_id), val});
				}
			}
			module_id++;
		}

		return params;
	}

private:
	std::array<std::unique_ptr<CoreProcessor>, MAX_MODULES_IN_PATCH> &modules;
	PatchData &pd;
};

} // namespace MetaModule
