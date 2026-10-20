#include "static_buffers.hh"
#include <array>

namespace MetaModule::StaticBuffers
{

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

// Same as MP1's (src/core_a7/static_buffers.cc)
void init() {
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
