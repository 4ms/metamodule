#include "gui/pages/file_browser/file_browser.hh"
#include "gui/pages/file_browser/file_save_dialog.hh"
#include "patch_file/file_storage_comm.hh"
#include <functional>
#include <string_view>

namespace MetaModule
{

void show_file_browser(FileBrowserDialog *browser,
					   std::string_view nameOrExtensions,
					   std::string_view startDir,
					   std::string_view title,
					   const std::function<void(char *)> action) {
	if (title.data())
		browser->set_title(title);

	if (nameOrExtensions.data())
		browser->filter_extensions(nameOrExtensions);

	browser->show(startDir, [=](char *path) {
		auto host_path = SimulatorPatchStorage::convert_path_to_host(path);

		// Need to allocate char* because action() is expecting to free() it
		auto dup_data = strdup(host_path.data());
		if (action)
			action(dup_data);
	});
}

void show_file_save_dialog(FileSaveDialog *save_dialog,
						   std::string_view initial_path,
						   std::string_view file_name,
						   std::string_view extension,
						   std::function<void(char *)> action) {

	auto full_path = SimulatorPatchStorage::convert_path_to_mm(initial_path);
	if (!full_path.ends_with("/"))
		full_path += "/";
	full_path += std::string(file_name);

	if (save_dialog) {
		save_dialog->show(full_path, extension, [=](char *path) {
			auto host_path = SimulatorPatchStorage::convert_path_to_host(path);

			// Need to allocate char* because action() is expecting to free() it
			auto dup_data = strdup(host_path.data());

			if (action)
				action(dup_data);
		});
	}
}
} // namespace MetaModule
