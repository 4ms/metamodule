#pragma once
#include "concurrent_buffer.hh"
#include "conf/ramdisk_conf.hh"
#include "core_intercom/intercore_message.hh"
#include "core_intercom/intercore_modulefs_message.hh"
#include "params/param_block.hh"
#include "params/sync_params.hh"
#include "patch_file/patch_dir_list.hh"
#include <array>

namespace MetaModule
{

// StaticBuffers sets up our regions of memory that have specific requirements in the target chip architecture.
namespace StaticBuffers
{

extern StreamConf::Audio::AudioInBlock audio_in_dma_block;
extern StreamConf::Audio::AudioOutBlock audio_out_dma_block;
extern std::array<char, 1024 * 1024> raw_patch_data;
extern IntercoreStorageMessage icc_shared_message;
extern IntercoreModuleFS::Message icc_module_fs_message_core0;
extern IntercoreModuleFS::Message icc_module_fs_message_core1;
extern std::array<uint8_t, 128 * 1024> module_fs_buffer_core0;
extern std::array<uint8_t, 128 * 1024> module_fs_buffer_core1;
extern PatchDirList patch_dir_list;
extern DirTree<FileEntry> dir_tree;
extern DoubleBufParamBlock param_blocks;
extern SyncParams sync_params;
extern RamDisk<RamDiskSizeBytes, RamDiskBlockSize> virtdrive;
extern ConcurrentBuffer console_a7_0_buff;
extern ConcurrentBuffer console_a7_1_buff;
extern ConcurrentBuffer console_m4_buff;

void init();

}; // namespace StaticBuffers

} // namespace MetaModule
