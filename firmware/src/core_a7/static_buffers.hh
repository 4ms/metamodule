#pragma once
#include "concurrent_buffer.hh"
#include "params/param_block.hh"

namespace MetaModule
{

// StaticBuffers sets up our regions of memory that have specific requirements in the target chip architecture.
namespace StaticBuffers
{

extern StreamConf::Audio::AudioInBlock audio_in_dma_block;
extern StreamConf::Audio::AudioOutBlock audio_out_dma_block;
extern DoubleBufParamBlock param_blocks;
extern ConcurrentBuffer console_a7_0_buff;
extern ConcurrentBuffer console_a7_1_buff;
extern ConcurrentBuffer console_m4_buff;

void init();

}; // namespace StaticBuffers

} // namespace MetaModule
