#include "gui/pages/file_browser/file_browser_adaptor.hh"
#include <cstdio>

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
		show_file_browser(browser, title, nameOrExtensions, startDir, action);
	}
}
