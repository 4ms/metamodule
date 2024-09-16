#include "debug.hh"
#include "delay.hh"
#include "memory/ram_buffer.hh"
#include "patch_file/file_storage_proxy.hh"
#include <cstring>

namespace MetaModule::FS
{

bool write_file(FileStorageProxy &proxy, std::span<const char> filedata, PatchLocation location);
bool write_file(FileStorageProxy &proxy, std::string const &filedata, PatchLocation location);
bool write_file(FileStorageProxy &proxy, std::string_view filedata, PatchLocation location);

// TODO:
// unsigned read_file(FileStorageProxy &proxy, std::string &filedata, PatchLocation location);	   //unbounded
// unsigned read_file(FileStorageProxy &proxy, std::span<char> filedata, PatchLocation location); //bounded

} // namespace MetaModule::FS
