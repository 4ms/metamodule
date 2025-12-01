#include <cstring>
#include <functional>
#include <osdialog.h>
#include <string_view>

void async_open_file(std::string_view initial_path,
					 std::string_view filter_extension_list,
					 std::string_view title,
					 std::function<void(char *path)> &&action) {
}

void async_open_dir(std::string_view initial_path, std::string_view title, std::function<void(char *path)> &&action) {
}

void async_save_file(std::string_view initial_path,
					 std::string_view filename,
					 std::string_view extension,
					 std::function<void(char *path)> &&action) {
}

void async_osdialog_file(osdialog_file_action action,
						 const char *path,
						 const char *filename,
						 osdialog_filters *filters,
						 std::function<void(char *path)> &&action_function) {
}

void async_dialog_filebrowser(const bool saving,
							  const char *const nameOrExtensions,
							  const char *const startDir,
							  const char *const title,
							  const std::function<void(char *)> action) {
}

namespace MetaModule
{

struct FileSaveDialog;
struct FileBrowserDialog;
void register_file_browser_vcv(FileBrowserDialog &, FileSaveDialog &) {
}

} // namespace MetaModule
