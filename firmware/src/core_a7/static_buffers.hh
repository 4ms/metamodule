#pragma once
#include "conf/ramdisk_conf.hh"
#include "core_intercom/intercore_message.hh"
#include "param_block.hh"
#include "patch_file/patch_dir_list.hh"
#include "sync_params.hh"
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
extern PatchDirList patch_dir_list;
extern DoubleBufParamBlock param_blocks;
extern SyncParams sync_params;
extern RamDisk<RamDiskSizeBytes, RamDiskBlockSize> virtdrive;

void init();

}; // namespace StaticBuffers

} // namespace MetaModule
