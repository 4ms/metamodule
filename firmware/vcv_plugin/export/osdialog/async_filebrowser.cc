#include "async_filebrowser.hh"
#include "gui/pages/file_browser/file_browser_adaptor.hh"
#include <cstdio>
#include <cstring>
#include <osdialog.h>

namespace MetaModule
{

namespace
{
FileBrowserDialog *browser = nullptr;
FileSaveDialog *save_dialog = nullptr;
} // namespace

void register_file_browser_vcv(FileBrowserDialog &file_browser, FileSaveDialog &file_save_dialog) {
	browser = &file_browser;
	save_dialog = &file_save_dialog;
}

} // namespace MetaModule

void async_open_file(std::string_view initial_path,
					 std::string_view filter_extension_list,
					 std::string_view title,
					 std::function<void(char *path)> &&action) {
	show_file_browser(MetaModule::browser, filter_extension_list.data(), initial_path.data(), title.data(), action);
}

void async_open_dir(std::string_view initial_path, std::string_view title, std::function<void(char *path)> &&action) {
	show_file_browser(MetaModule::browser, "*/", initial_path.data(), title.data(), action);
}

void async_save_file(std::string_view initial_path,
					 std::string_view filename,
					 std::string_view extension,
					 std::function<void(char *path)> &&action) {
	MetaModule::show_file_save_dialog(MetaModule::save_dialog, initial_path, filename, extension, action);
}

void async_osdialog_file(osdialog_file_action action,
						 const char *path,
						 const char *filename,
						 osdialog_filters *filters,
						 std::function<void(char *path)> &&action_function) {

	using namespace MetaModule;

	if (!action_function || !browser)
		return;

	if (action == OSDIALOG_SAVE) {

		if (!path)
			path = "";
		if (!filename || filename[0] == '\0')
			filename = "Untitled";

		std::string extension = "";
		if (filters && filters->patterns) {
			extension = "." + std::string(filters->patterns->pattern);
		}

		printf("async_osdialog_file(OSDIALOG_SAVE, %s, %s, %s)\n", path, filename, extension.c_str());

		show_file_save_dialog(MetaModule::save_dialog, std::string_view(path), filename, extension, action_function);

		// action_function(dup_str);
		// show_file_browser(browser, "", filename, "Save File:", action_function);

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
