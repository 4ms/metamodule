#pragma once
#include "fs/dir_tree.hh"

// MP2 version of src/core_a7/static_buffers.hh: only what's used so far.
namespace MetaModule::StaticBuffers
{

// The file browser's directory listing (FileStorageProxy fills it in from what the M33 sends)
extern DirTree<FileEntry> dir_tree;

} // namespace MetaModule::StaticBuffers
