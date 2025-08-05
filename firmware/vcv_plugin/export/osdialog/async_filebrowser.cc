#include "async_filebrowser.hh"
#include "gui/pages/file_browser/file_browser_adaptor.hh"
#include <cstdio>
#include <cstring>
#include <filesystem>
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

////// Native API:

void async_open_file(std::string_view initial_path,
					 std::string_view filter_extension_list,
					 std::string_view title,
					 std::function<void(char *path)> &&action) {
	using namespace MetaModule;
	show_file_browser(browser, filter_extension_list.data(), initial_path.data(), title.data(), action);
}

void async_open_dir(std::string_view initial_path, std::string_view title, std::function<void(char *path)> &&action) {
	using namespace MetaModule;
	show_file_browser(browser, "*/", initial_path.data(), title.data(), action);
}

void async_save_file(std::string_view initial_path,
					 std::string_view filename,
					 std::string_view extension,
					 std::function<void(char *path)> &&action) {
	using namespace MetaModule;
	show_file_save_dialog(save_dialog, initial_path.data(), filename.data(), extension.data(), action);
}

///// Rack-like API:

void async_osdialog_file(osdialog_file_action action,
						 const char *path,
						 const char *filename,
						 osdialog_filters *filters,
						 std::function<void(char *path)> &&action_function) {

	using namespace MetaModule;

	if (!action_function || !browser)
		return;

	if (!path)
		path = "";

	if (action == OSDIALOG_SAVE) {

		auto clean_filename = filename ? std::filesystem::path(filename).stem().string() : "Untitled";

		auto extension = filename ? std::filesystem::path(filename).extension().string() : "";
		if (extension == "" && filters && filters->patterns) {
			extension = "." + std::string(filters->patterns->pattern);
		}

		show_file_save_dialog(save_dialog, path, clean_filename, extension, action_function);

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
		auto path = startDir ? std::string_view{startDir} : "";
		auto filename = nameOrExtensions ? std::filesystem::path(nameOrExtensions).stem().string() : "Untitled";
		auto extension = nameOrExtensions ? std::filesystem::path(nameOrExtensions).extension().string() : "";
		show_file_save_dialog(save_dialog, path, filename, extension, action);
	} else {
		auto path = startDir ? startDir : "";
		auto ext = nameOrExtensions ? nameOrExtensions : "";
		auto title_v = title ? title : "";
		show_file_browser(browser, ext, path, title_v, action);
	}
}
