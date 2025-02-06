#include "conf/ramdisk_conf.hh"
#include "console/concurrent_buffer.hh"
#include "core_intercom/intercore_message.hh"
#include "core_intercom/intercore_modulefs_message.hh"
#include "param_block.hh"
#include "patch_file/patch_dir_list.hh"
#include "sync_params.hh"
#include <array>

namespace MetaModule
{

// StaticBuffers sets up our regions of memory that have specific requirements in the target chip architecture.
// The sections are defined in the linker file.
namespace StaticBuffers
{

//If DMA Burst mode is enabled, See RM sec 18.3.12;
//The burst configuration has to be selected in order to respect the AHB protocol, where bursts must not cross the 1 Kbyte address boundary because the minimum address space that can be allocated to a single slave is 1 Kbyte. This means that the 1-Kbyte address boundary must not be crossed by a burst block transfer, otherwise an AHB error is generated, that is not reported by the DMA registers.

__attribute__((section(".sysram"))) StreamConf::Audio::AudioInBlock audio_in_dma_block{};
__attribute__((section(".sysram"))) StreamConf::Audio::AudioOutBlock audio_out_dma_block{};
__attribute__((section(".ddma"))) std::array<char, 1024 * 1024> raw_patch_data;

__attribute__((section(".ddma"))) IntercoreStorageMessage icc_shared_message;
__attribute__((section(".ddma"))) IntercoreModuleFS::Message icc_module_fs_message_core0;
__attribute__((section(".ddma"))) IntercoreModuleFS::Message icc_module_fs_message_core1;
__attribute__((section(".ddma"))) std::array<uint8_t, 64 * 1024> module_fs_buffer_core0;
__attribute__((section(".ddma"))) std::array<uint8_t, 64 * 1024> module_fs_buffer_core1;

__attribute__((section(".ddma"))) PatchDirList patch_dir_list;

__attribute__((section(".sysram"))) DoubleBufParamBlock param_blocks{};
__attribute__((section(".sysram"))) SyncParams sync_params;

__attribute__((section(".virtdrive"))) RamDisk<RamDiskSizeBytes, RamDiskBlockSize> virtdrive;

__attribute__((section(".consolebuf"))) ConcurrentBuffer console_a7_0_buff{};
__attribute__((section(".consolebuf"))) ConcurrentBuffer console_a7_1_buff{};
__attribute__((section(".consolebuf"))) ConcurrentBuffer console_m4_buff{};

void init() {
	for (auto &block : param_blocks) {
		for (auto &param : block.params) {
			param.clear();
		}
		block.metaparams.clear();
	}

	//clear buffers
	for (auto &buff : audio_out_dma_block.codec) {
		for (auto &frame : buff)
			frame = StreamConf::Audio::AudioOutFrame{};
	}

	for (auto &buff : audio_out_dma_block.ext_codec) {
		for (auto &frame : buff)
			frame = StreamConf::Audio::AudioOutFrame{};
	}

	for (auto &buff : audio_in_dma_block.codec) {
		for (auto &frame : buff)
			frame = StreamConf::Audio::AudioInFrame{};
	}

	for (auto &buff : audio_in_dma_block.ext_codec) {
		for (auto &frame : buff)
			frame = StreamConf::Audio::AudioInFrame{};
	}

	console_a7_0_buff.writer_ref_count = 0;
	console_a7_0_buff.current_write_pos = 0;
	console_a7_0_buff.buffer.data[0] = 0;
	console_a7_0_buff.use_color = false;

	console_a7_1_buff.writer_ref_count = 0;
	console_a7_1_buff.current_write_pos = 0;
	console_a7_1_buff.buffer.data[0] = 0;
	console_a7_1_buff.use_color = false;

	console_m4_buff.writer_ref_count = 0;
	console_m4_buff.current_write_pos = 0;
	console_m4_buff.buffer.data[0] = 0;
	console_m4_buff.use_color = false;
}

}; // namespace StaticBuffers

} // namespace MetaModule
