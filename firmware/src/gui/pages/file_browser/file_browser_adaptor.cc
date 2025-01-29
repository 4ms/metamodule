#include "gui/pages/file_browser/file_browser.hh"
#include <functional>

namespace MetaModule
{

void show_file_browser(FileBrowserDialog *browser,
					   const char *const nameOrExtensions,
					   const char *const startDir,
					   const char *const title,
					   const std::function<void(char *)> action) {
	browser->set_title(title);
	browser->filter_extensions(nameOrExtensions);
	browser->show(startDir, action);
}

} // namespace MetaModule
