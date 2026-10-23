#pragma once
#include "conf/screen_buffer_conf.hh"
#include "conf/stream_conf.hh"
#include "console/concurrent_buffer.hh"
#include "core_intercom/intercore_devicesettings_message.hh"
#include "core_intercom/intercore_message.hh"
#include "fs/dir_tree.hh"
#include "param_block.hh"
#include "lvgl.h"
#include "sync_params.hh"
#include "usb/dev_drive_block.hh"
#include "usb/usb_connection_status_block.hh"
#include <array>
#include <cstdint>
#include <span>

// MP2 version of src/core_a7/static_buffers.hh: only what's used so far.
namespace MetaModule::StaticBuffers
{

// Display: the framebuffer the LTDC scans out, and LVGL's partial render buffer (1/4 of the GUI,
// same as MP1)
extern std::array<uint32_t, ScreenBufferConf::width * ScreenBufferConf::height> framebuffer;
extern std::array<lv_color_t, ScreenBufferConf::viewWidth * ScreenBufferConf::viewHeight / 4> lvgl_draw_buffer;

// Patch storage, on the M33 (patch_file/file_storage_proxy.hh): the M33 reads files into
// raw_patch_data, and writes the patch list and dir entries into storage_list_buffer serialized
// (see dir_list_serial.hh)
extern IntercoreStorageMessage storage_message;
extern std::array<char, 1024 * 1024> raw_patch_data;
extern std::array<char, 256 * 1024> storage_list_buffer;

// The developer drive's handoff between the USB device (M33) and the A35 (DevDriveService)
extern DevDriveBlock dev_drive_block;

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

// USB, shared with the M33: settings (GUI -> M33, see core_a7/device_settings_proxy.hh), and
// connection status (M33 -> GUI, see usb/usb_status_reader.hh)
extern DeviceSettingsMessage icc_device_settings_message;
extern UsbConnectionStatusBlock usb_connection_status;

// Console output, shared with the M33, which sends it to the UART or the USB console: one per core
// (A35 core 0, A35 core 1, M33)
extern std::array<ConcurrentBuffer, 3> console_buffers;

void init();

} // namespace MetaModule::StaticBuffers
