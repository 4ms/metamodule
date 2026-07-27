// Stubs for GUI-only interfaces referenced by code linked into the headless
// build (vcv_plugin_export, coreproc_plugin_export, osdialog).

#include "coreproc_plugin/internal_interface/plugin_app_interface.hh"
#include "gui/pages/file_browser/file_browser_adaptor.hh"
#include "vcv_plugin/export/nanovg/fontstash-wrapper.h"
#include <cstdio>

// Fontstash: the GUI build implements these in vcv_plugin/internal/fons-wrapper.cc
// using the LVGL TTF font loader. Headless never renders text.

FONScontext *fonsCreateInternal() {
	return nullptr;
}

int fonsAddFont(FONScontext *, const char *, const char *, int) {
	return -1;
}

namespace MetaModule
{

// PluginAppInterface: the GUI build implements these in
// coreproc_plugin/internal_interface/plugin_app_interface.cc using the
// patch storage and notification queue, neither of which exists headless.

uint32_t PluginAppInterface::get_block_size() {
	// Matches the block size main-headless.cc processes with
	return 32;
}

void PluginAppInterface::mark_patch_modified() {
}

StaticString<7> PluginAppInterface::get_volume() {
	return "";
}

std::string PluginAppInterface::get_path() {
	return "";
}

std::string PluginAppInterface::get_dir() {
	return "/";
}

void PluginAppInterface::notify_user(std::string_view message, int) {
	printf("%.*s\n", (int)message.size(), message.data());
}

// File browser: the GUI build implements these in src/file_browser_adaptor.cc.
// The action callback is never invoked, as if the user cancelled the dialog.

void show_file_browser(FileBrowserDialog *, std::string_view, std::string_view, std::string_view,
					   const std::function<void(char *)>) {
	printf("File browser is not available in the headless build\n");
}

void show_file_save_dialog(
	FileSaveDialog *, std::string_view, std::string_view, std::string_view, std::function<void(char *)>) {
	printf("File save dialog is not available in the headless build\n");
}

} // namespace MetaModule
