#pragma once
#include <functional>

namespace MetaModule
{
struct FileBrowserDialog;

void show_file_browser(FileBrowserDialog *browser,
					   const char *const nameOrExtensions,
					   const char *const startDir,
					   const char *const title,
					   const std::function<void(char *)> action);

} // namespace MetaModule
