#include "static_buffers.hh"
#include <array>
#include <cstdint>
#include <span>

namespace MetaModule::StaticBuffers
{

DirTree<FileEntry> dir_tree;

// The buffer for loading files (get_ram_buffer()): the M33 reads files into it, so it's in
// memory shared with the M33. Same size as MP1's FW buffer.
namespace
{
__attribute__((section(".sharedmem"))) std::array<uint8_t, 20 * 1024 * 1024> fw_buffer_mem;
}
std::span<uint8_t> fw_buffer{fw_buffer_mem};

} // namespace MetaModule::StaticBuffers
