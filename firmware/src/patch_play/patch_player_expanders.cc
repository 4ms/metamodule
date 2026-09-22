#include "patch_play/patch_player.hh"

namespace MetaModule
{

void PatchPlayer::assign_rack_module_id(unsigned module_idx) {
	if (module_idx >= num_modules)
		return;
	if (auto *rack_module = as_rack_module(modules[module_idx].get()))
		rack_module->id = next_rack_module_id++;
}

bool PatchPlayer::connect_expander(ExpanderConnection conn) {
	if (conn.left_module_id >= num_modules || conn.right_module_id >= num_modules)
		return false;
	return rack_expanders.connect(modules[conn.left_module_id].get(), modules[conn.right_module_id].get());
}

void PatchPlayer::connect_all_expanders() {
	for (auto const &exp : pd.expanders)
		connect_expander(exp);
}

void PatchPlayer::connect_expanders_for(unsigned module_idx) {
	for (auto const &exp : pd.expanders) {
		if (exp.left_module_id == module_idx || exp.right_module_id == module_idx)
			connect_expander(exp);
	}
}

bool PatchPlayer::add_expander(ExpanderConnection conn) {
	/// TODO: check if this works: (why would rack_expanders.connect() fail?)
	// if (pd.add_expander(conn)) {
	// 	if (connect_expander(conn))
	// 		return true;
	// 	else
	// 		pd.remove_expander(conn);
	// }
	// return false;

	if (!pd.can_add_expander(conn))
		return false;

	if (!connect_expander(conn))
		return false;

	pd.expanders.push_back(conn);
	return true;
}

bool PatchPlayer::remove_expander(ExpanderConnection conn) {
	bool removed = pd.remove_expander(conn);
	if (conn.left_module_id < num_modules && conn.right_module_id < num_modules)
		rack_expanders.disconnect_pair(modules[conn.left_module_id].get(), modules[conn.right_module_id].get());
	return removed;
}

PatchPlayer::ExpanderStatus PatchPlayer::expander_status(ExpanderConnection conn) const {
	if (conn.left_module_id >= num_modules || conn.right_module_id >= num_modules)
		return ExpanderStatus::NotConnected;

	auto *left = modules[conn.left_module_id].get();
	auto *right = modules[conn.right_module_id].get();

	if (rack_expanders.is_active(left, right))
		return ExpanderStatus::Active;

	if (rack_expanders.is_connected(left, right))
		return ExpanderStatus::Connected;

	return ExpanderStatus::NotConnected;
}

} // namespace MetaModule
