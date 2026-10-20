#pragma once
#include "conf/stream_conf.hh"
#include "fs/dir_tree.hh"
#include "param_block.hh"
#include "sync_params.hh"
#include <cstdint>
#include <span>

// MP2 version of src/core_a7/static_buffers.hh: only what's used so far.
namespace MetaModule::StaticBuffers
{

// The file browser's directory listing (FileStorageProxy fills it in from what the M33 sends)
extern DirTree<FileEntry> dir_tree;

// The buffer for loading files: see get_ram_buffer() (mp2-stubs/memory/ram_buffer.hh)
extern std::span<uint8_t> fw_buffer;

// Audio
extern StreamConf::Audio::AudioInBlock audio_in_dma_block;
extern StreamConf::Audio::AudioOutBlock audio_out_dma_block;

// Controls -> Audio. The M33 writes these (core_m33/controls.hh), as the M4 does on MP1.
extern DoubleBufParamBlock param_blocks;

// Audio -> GUI
extern SyncParams sync_params;

void init();

} // namespace MetaModule::StaticBuffers
