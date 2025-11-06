#include <functional>
#include <string_view>

namespace MetaModule
{

struct FileBrowserDialog;
struct FileSaveDialog;

void show_file_browser(FileBrowserDialog *browser,
					   const char *const nameOrExtensions,
					   const char *const startDir,
					   const char *const title,
					   const std::function<void(char *)> action) {
}

void show_file_save_dialog(FileSaveDialog *save_dialog,
						   std::string_view initial_path,
						   std::string_view file_name,
						   std::string_view extension,
						   std::function<void(char *)> action) {
}
} // namespace MetaModule
