#pragma once
#include "gui/elements/element_type.hh"
#include "patch/patch.hh"
#include "util/debouncer.hh"
#include <optional>

namespace MetaModule
{

struct GuiState {
	struct CableBeginning {
		Jack jack;
		ElementType type;
		bool has_connections;
	};
	std::optional<CableBeginning> new_cable{};
	bool already_displayed_cable_instructions = false;

	struct ExpanderBeginning {
		uint16_t module_id;
		ExpanderSide side;
	};
	std::optional<ExpanderBeginning> new_expander{};

	// Set after an expander connection is made, so the module view re-opens
	// the Expanders menu (showing the new connection) when it comes back into focus
	bool reopen_expander_menu = false;

	bool force_redraw_patch{};
	bool view_patch_file_changed{};

	// Setting this to true will keep page manager from
	// using inter-core-comm to check if the patch file changed on disk
	bool prohibit_file_refresh = false;

	bool do_write_settings{};

	Toggler back_button{};

	Toggler file_browser_visible{};

	bool midi_quick_mapping_mode = false;
};

} // namespace MetaModule
