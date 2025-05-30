#include "patch_file/file_storage_proxy.hh"
#include <cstring>

namespace MetaModule::FS
{

bool write_file(FileStorageProxy &proxy, std::span<const char> filedata, PatchLocation location);
bool write_file(FileStorageProxy &proxy, std::string const &filedata, PatchLocation location);
bool write_file(FileStorageProxy &proxy, std::string_view filedata, PatchLocation location);

bool append_file(FileStorageProxy &proxy, std::string_view filedata, PatchLocation location);

// TODO:
std::optional<unsigned> read_file(FileStorageProxy &proxy, std::string &filedata, PatchLocation location);
// unsigned read_file(FileStorageProxy &proxy, std::span<char> filedata, PatchLocation location); //bounded

std::optional<unsigned> file_size(FileStorageProxy &, PatchLocation);

} // namespace MetaModule::FS
