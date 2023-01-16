#include "patch_fileio.hh"

namespace MetaModule
{
std::vector<size_t> PatchFileIO::found_files;
std::array<char, 65536> PatchFileIO::buf;
} // namespace MetaModule
