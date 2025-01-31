#include "async_filebrowser.hh"
#include "gui/pages/file_browser/file_browser_adaptor.hh"
#include <cstdio>
#include <osdialog.h>

namespace MetaModule
{

namespace
{
FileBrowserDialog *browser = nullptr;
}

void register_file_browser_vcv(FileBrowserDialog &file_browser) {
	browser = &file_browser;
}

} // namespace MetaModule

void async_osdialog_file(osdialog_file_action action,
						 const char *path,
						 const char *filename,
						 osdialog_filters *filters,
						 std::function<void(char *path)> &&action_function) {

	using namespace MetaModule;

	if (!action_function || !browser)
		return;

	if (action == OSDIALOG_SAVE) {
		printf("Save file dialog box -- not supported\n");

	} else if (action == OSDIALOG_OPEN) {
		auto filter_string = stringify_osdialog_filters(filters);
		show_file_browser(browser, filter_string.c_str(), path, "Open File:", action_function);

	} else if (action == OSDIALOG_OPEN_DIR) {
		show_file_browser(browser, "*/", path, "Open Folder:", action_function);
	}
}

void async_dialog_filebrowser(const bool saving,
							  const char *const nameOrExtensions,
							  const char *const startDir,
							  const char *const title,
							  const std::function<void(char *)> action) {
	using namespace MetaModule;

	if (!action || !browser)
		return;

	if (saving) {
		printf("Save file dialog box -- not supported\n");
	} else {
		show_file_browser(browser, nameOrExtensions, startDir, title, action);
	}
}
