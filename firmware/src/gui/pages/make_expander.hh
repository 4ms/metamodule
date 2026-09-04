#pragma once
#include "gui/gui_state.hh"
#include "gui/notify/queue.hh"
#include "patch/patch_data.hh"

// GUI-side helpers for attaching/detaching VCV expander modules.
namespace MetaModule
{

inline void abort_expander(GuiState &gui_state, NotificationQueue &notify_queue) {
	if (gui_state.new_expander) {
		gui_state.new_expander = std::nullopt;
		notify_queue.put(Notification{"Cancelled attaching an expander", Notification::Priority::Status, 1000});
	}
}

// Returns nullptr if target can be attached to the given side of the module
// in beginning, otherwise a message explaining why not.
inline const char *expander_target_error(PatchData const &pd, GuiState::ExpanderBeginning beginning, uint16_t target) {
	if (target == beginning.module_id)
		return "A module cannot be its own expander";

	if (target == 0)
		return "The hub cannot be an expander";

	if (target >= pd.module_slugs.size())
		return "Module not found";

	auto conn = ExpanderConnection::make(beginning.module_id, beginning.side, target);
	if (pd.has_expander(conn))
		return "Already attached";

	if (pd.find_expander(target, beginning.side == ExpanderSide::Left ? ExpanderSide::Right : ExpanderSide::Left))
		return "That module already has an expander on that side";

	if (!pd.can_add_expander(conn))
		return "Cannot attach expander";

	return nullptr;
}

} // namespace MetaModule
