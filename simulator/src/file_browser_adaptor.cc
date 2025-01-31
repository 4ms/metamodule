#include "gui/pages/file_browser/file_browser.hh"
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

	std::string_view start_dir = (startDir) ? std::string_view{startDir} : std::string_view{};

	browser->show(start_dir, [=](char *path) {
		auto host_path = SimulatorPatchStorage::convert_path_to_host(path);
		printf("Simulator: path %s => %s\n", path, host_path.c_str());

		// Need to allocate char* because action() is expecting to free() it
		auto dup_data = strndup(host_path.data(), host_path.length());
		action(dup_data);
	});
}

} // namespace MetaModule
