#include "patch_play/rack_expanders.hh"
#include "patch_play/expander_hookup.hh"
#include "pr_dbg.hh"
#include "vcv_plugin/internal/rack_module_registry.hh"
#include <algorithm>
#include <engine/Module.hpp>

namespace MetaModule
{

bool RackExpanders::connect(CoreProcessor *left, CoreProcessor *right, uint16_t left_id, uint16_t right_id) {
	auto *left_module = RackModuleRegistry::as_rack_module(left);
	auto *right_module = RackModuleRegistry::as_rack_module(right);

	if (!left_module || !right_module) {
		pr_warn("Expander connection %u -> %u skipped: not rack modules\n", left_id, right_id);
		return false;
	}

	left_module->id = left_id;
	right_module->id = right_id;

	if (!ExpanderHookup::connect(left_module, right_module)) {
		pr_warn("Expander connection %u -> %u skipped: invalid or duplicate\n", left_id, right_id);
		return false;
	}

	if (std::find(modules.begin(), modules.end(), left_module) == modules.end())
		modules.push_back(left_module);
	if (std::find(modules.begin(), modules.end(), right_module) == modules.end())
		modules.push_back(right_module);

	pr_info("Connected expander: module %u <-> module %u\n", left_id, right_id);
	return true;
}

void RackExpanders::flip_messages() {
	for (auto *module : modules)
		ExpanderHookup::flip_messages(module);
}

void RackExpanders::disconnect_all() {
	for (auto *module : modules)
		ExpanderHookup::disconnect(module);
	modules.clear();
}

void RackExpanders::clear() {
	modules.clear();
}

} // namespace MetaModule
