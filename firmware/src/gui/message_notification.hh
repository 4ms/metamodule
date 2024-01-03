#pragma once
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include <string_view>

namespace MetaModule::MessageNotification
{

void show(std::string_view msg) {
	lv_label_set_text(ui_MessageLabel, msg.data());
	SlideDown_Animation(ui_MessagePanel, 0);
	SlideUp_Animation(ui_MessagePanel, 5000);
}

} // namespace MetaModule::MessageNotification
