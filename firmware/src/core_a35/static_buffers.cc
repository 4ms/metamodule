#include "static_buffers.hh"
#include <array>
#include <memory>

namespace MetaModule::StaticBuffers
{

__attribute__((section(".framebuffers"))) alignas(4096)
std::array<uint32_t, ScreenBufferConf::width * ScreenBufferConf::height> framebuffer;
std::array<lv_color_t, ScreenBufferConf::viewWidth * ScreenBufferConf::viewHeight / 4> lvgl_draw_buffer;

__attribute__((section(".sharedmem"))) IntercoreStorageMessage storage_message;
__attribute__((section(".sharedmem"))) std::array<char, 1024 * 1024> raw_patch_data;
__attribute__((section(".sharedmem"))) std::array<char, 256 * 1024> storage_list_buffer;

__attribute__((section(".sharedmem"))) DevDriveBlock dev_drive_block;

DirTree<FileEntry> dir_tree;

// The M33 reads files into it, so it's in memory shared with the M33. Same size as MP1's FW buffer.
namespace
{
__attribute__((section(".sharedmem"))) std::array<uint8_t, 20 * 1024 * 1024> fw_buffer_mem;
}
std::span<uint8_t> fw_buffer{fw_buffer_mem};

// DMA buffers: in non-cacheable memory
__attribute__((section(".dmabuf"))) StreamConf::Audio::AudioInBlock audio_in_dma_block;
__attribute__((section(".dmabuf"))) StreamConf::Audio::AudioOutBlock audio_out_dma_block;

// The M33 writes these (controls)
__attribute__((section(".sharedmem"))) DoubleBufParamBlock param_blocks{};
SyncParams sync_params;

__attribute__((section(".sharedmem"))) DeviceSettingsMessage icc_device_settings_message;
__attribute__((section(".sharedmem"))) UsbConnectionStatusBlock usb_connection_status;

__attribute__((section(".sharedmem"))) std::array<ConcurrentBuffer, 3> console_buffers;
static_assert(sizeof(ConcurrentBuffer) == ConcurrentBuffer::Size + 8, "Same on the A35 and M33");

// Same as MP1's (src/core_a7/static_buffers.cc)
void init() {
	// .sharedmem isn't loaded or cleared at startup
	icc_device_settings_message = {};
	std::construct_at(&usb_connection_status);

	// (Only the positions: the data needn't be cleared)
	for (auto &buff : console_buffers) {
		buff.write_pos = 0;
		buff.read_pos = 0;
	}

	for (auto &block : param_blocks) {
		for (auto &param : block.params) {
			param.clear();
		}
		block.metaparams.clear();

		// FIXME: no jack sense yet. Report all jacks as patched (as MP1 does when it can't read the
		// jack sense chip), so the patch's inputs and outputs are used.
		block.metaparams.jack_senses = 0xFFFFFFFF;
	}

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
}

} // namespace MetaModule::StaticBuffers
