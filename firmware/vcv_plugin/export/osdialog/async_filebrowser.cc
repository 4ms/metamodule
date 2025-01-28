#include "gui/pages/file_browser.hh"
#include <cstdio>
#include <cstring>

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
		printf("Open file dialog box\n");
		browser->set_title(title);
		browser->filter_extensions(nameOrExtensions);
		browser->show(startDir, action);
	}
}
