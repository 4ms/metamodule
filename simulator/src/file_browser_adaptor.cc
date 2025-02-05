#include "gui/pages/file_browser/file_browser.hh"
#include "gui/pages/file_browser/file_save_dialog.hh"
#include "patch_file/file_storage_comm.hh"
#include <functional>

namespace MetaModule
{

void show_file_browser(FileBrowserDialog *browser,
					   const char *const nameOrExtensions,
					   const char *const startDir,
					   const char *const title,
					   const std::function<void(char *)> action) {
	if (title)
		browser->set_title(title);
	if (nameOrExtensions)
		browser->filter_extensions(nameOrExtensions);

	if (!action) {
		printf("Must give an action\n");
		return;
	}

	std::string start_dir = (startDir) ? SimulatorPatchStorage::convert_path_to_mm(startDir) : "";
	if (startDir)
		printf("Simulator: start '%s'\n=>               '%s'\n", startDir, start_dir.c_str());

	browser->show(start_dir, [=](char *path) {
		auto host_path = SimulatorPatchStorage::convert_path_to_host(path);
		printf("Simulator: path '%s'\n=>              '%s'\n", path, host_path.c_str());

		// Need to allocate char* because action() is expecting to free() it
		auto dup_data = strndup(host_path.data(), host_path.length());
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

	printf("Simulator: save browser starts at '%s'\n", full_path.c_str());

	if (save_dialog) {
		save_dialog->show(full_path, extension, [=](char *path) {
			auto host_path = SimulatorPatchStorage::convert_path_to_host(path);
			printf("Simulator: saving to '%s'", host_path.c_str());

			// Need to allocate char* because action() is expecting to free() it
			auto dup_data = strndup(host_path.data(), host_path.length());
			action(dup_data);
		});
	}
}
} // namespace MetaModule
