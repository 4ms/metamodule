#pragma once
#include "git_version.h"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct InfoTab : SystemMenuTab {

	void prepare_focus(lv_group_t *group) override {
		this->group = group;

		std::string_view fw_version = GIT_FIRMWARE_VERSION_TAG;
		if (fw_version.starts_with("firmware-"))
			fw_version.remove_prefix(9);

		lv_label_set_text_fmt(ui_SystemMenuFWversion, "Firmware version: %s", fw_version.data());
	}

private:
	lv_group_t *group = nullptr;
};
} // namespace MetaModule
