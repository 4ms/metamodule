#include "patch/patch_file.hh"
#include <filesystem>
#include <string>
#include <string_view>

namespace MetaModule::Filesystem
{

bool is_local_path(std::string_view path) {
	return path.starts_with("sdc:") || path.starts_with("usb:") || path.starts_with("nor:") || path.starts_with("ram:");
}

std::string translate_path_to_patchdir(std::string_view path, unsigned num_subdirs) {
	// /Users/user/rack/samples/a.wav
	auto p = std::filesystem::path{path};

	// "sdc:/patches/"
	printf("translate(%d): patch::get_dir = %s\n", num_subdirs, MetaModule::Patch::get_dir().c_str());
	printf("patch::get_path = %s\n", MetaModule::Patch::get_path().c_str());

	auto local = std::filesystem::path(MetaModule::Patch::get_dir());

	// First subdir: samples/
	if ((num_subdirs > 0) && p.has_parent_path()) {
		local = local / p.parent_path().filename();

		// Second subdir: rack/samples/
		if ((num_subdirs > 1) && p.parent_path().has_parent_path()) {
			local = local / p.parent_path().parent_path().filename();
		}
	}

	printf("translate: append filename %s\n", p.filename().string().c_str());

	local = local / p.filename();

	return local;
}

} // namespace MetaModule::Filesystem
