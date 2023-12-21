#pragma once
#include "git_version.h"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{

struct SystemStatusTab {

	void prepare_focus(lv_group_t *group) {
		this->group = group;

		std::string_view fw_version = GIT_FIRMWARE_VERSION_TAG;
		if (fw_version.starts_with("firmware-"))
			fw_version.remove_prefix(9);

		lv_label_set_text_fmt(ui_SystemMenuFWversion, "Firmware version: %s", fw_version.data());
	}

	void update() {
	}

private:
	lv_group_t *group = nullptr;
};
} // namespace MetaModule
