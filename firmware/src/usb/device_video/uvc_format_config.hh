#pragma once

// Select the USB Video Class pixel format at compile time.
// When USE_UVC_FORMAT_BGR3 is defined, the UVC stream uses uncompressed
// BGR24 (3 bytes/pixel, UVC "BGR3" / Windows MEDIASUBTYPE_RGB24).
// When not defined, the UVC stream uses YUY2 (2 bytes/pixel, 4:2:2).
//
// This selector must stay consistent between:
//   - the A7 side (src/screen/usb_video_buffer.hh), which converts
//     RGB565 -> format into the shadow framebuffer, and
//   - the M4 side (src/usb/usbd_conf.h + device_video/usb_video_device.cc),
//     which advertises the format in the USB descriptor and streams bytes.
//

//#define USE_UVC_FORMAT_BGR3
