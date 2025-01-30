#include "gui/pages/file_browser/file_browser.hh"
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

	std::string_view start_dir = (startDir) ? std::string_view{startDir} : std::string_view{};
	browser->show(start_dir, action);
}

} // namespace MetaModule
