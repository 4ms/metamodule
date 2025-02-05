#include "gui/pages/file_browser/file_browser.hh"
#include "gui/pages/file_browser/file_save_dialog.hh"
#include <functional>

namespace MetaModule
{

void show_file_browser(FileBrowserDialog *browser,
					   const char *const nameOrExtensions,
					   const char *const startDir,
					   const char *const title,
					   const std::function<void(char *)> action) {
	if (!browser)
		return;

	if (title)
		browser->set_title(title);
	if (nameOrExtensions)
		browser->filter_extensions(nameOrExtensions);

	std::string_view start_dir = (startDir) ? std::string_view{startDir} : std::string_view{};
	browser->show(start_dir, action);
}

void show_file_save_dialog(FileSaveDialog *save_dialog,
						   std::string_view initial_path,
						   std::string_view file_name,
						   std::string_view extension,
						   std::function<void(char *)> action) {

	if (!save_dialog)
		return;

	auto full_path = std::string(initial_path);

	if (!full_path.ends_with("/"))
		full_path += "/";

	full_path += std::string(file_name);

	save_dialog->show(full_path, extension, action);
}
} // namespace MetaModule
