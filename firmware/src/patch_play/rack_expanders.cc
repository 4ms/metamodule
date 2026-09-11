#include "patch_play/rack_expanders.hh"
#include "conf/patch_conf.hh"
#include "plugin_module.hh"
#include "pr_dbg.hh"
#include <engine/Module.hpp>

namespace MetaModule
{

RackExpanders::RackExpanders() {
	// Avoid allocating on the audio thread when connections are added
	conns.reserve(MAX_MODULES_IN_PATCH);
}

bool RackExpanders::connect(CoreProcessor *left, CoreProcessor *right) {
	auto *left_module = as_rack_module(left);
	auto *right_module = as_rack_module(right);

	if (!left_module || !right_module) {
		pr_warn("Expander connection skipped: not rack modules\n");
		return false;
	}

	if (!conns.connect(left_module, right_module)) {
		pr_warn("Expander connection skipped: invalid or side already in use\n");
		return false;
	}

	pr_info("Connected expander: rack module %lld <-> %lld\n", (long long)left_module->id, (long long)right_module->id);
	return true;
}

bool RackExpanders::disconnect_pair(CoreProcessor *left, CoreProcessor *right) {
	return conns.disconnect_pair(as_rack_module(left), as_rack_module(right));
}

void RackExpanders::disconnect(CoreProcessor *m) {
	conns.disconnect(as_rack_module(m));
}

void RackExpanders::disconnect_all() {
	conns.disconnect_all();
}

void RackExpanders::flip_messages() {
	conns.flip_messages();
}

bool RackExpanders::is_connected(CoreProcessor *left, CoreProcessor *right) const {
	return conns.is_connected(as_rack_module(left), as_rack_module(right));
}

bool RackExpanders::is_active(CoreProcessor *left, CoreProcessor *right) const {
	return conns.is_active(as_rack_module(left), as_rack_module(right));
}

void RackExpanders::clear() {
	conns.clear();
}

} // namespace MetaModule
