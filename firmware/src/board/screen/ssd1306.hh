#pragma once
#include <cstdint>

namespace SSD1306
{

// Not tested!!!
// From Adafruit driver
// https://github.com/adafruit/Adafruit_SSD1306/blob/master/Adafruit_SSD1306.cpp

enum Commands {
	SETLOWCOLUMN = 0x00,
	SETHIGHCOLUMN = 0x10,

	SETSTARTLINE = 0x40,

	MEMORYMODE = 0x20,
	COLUMNADDR = 0x21,
	PAGEADDR = 0x22,

	RIGHT_HORIZONTAL_SCROLL = 0x26,				 ///< Init rt scroll
	LEFT_HORIZONTAL_SCROLL = 0x27,				 ///< Init left scroll
	VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL = 0x29, ///< Init diag scroll
	VERTICAL_AND_LEFT_HORIZONTAL_SCROLL = 0x2A,	 ///< Init diag scroll
	DEACTIVATE_SCROLL = 0x2E,					 ///< Stop scroll
	ACTIVATE_SCROLL = 0x2F,						 ///< Start scroll

	SETCONTRAST = 0x81,
	CHARGEPUMP = 0x8D,

	SEGREMAP = 0xA0,
	SET_VERTICAL_SCROLL_AREA = 0xA3, ///< Set scroll range
	DISPLAYALLON_RESUME = 0xA4,
	DISPLAYALLON = 0xA5,
	NORMALDISPLAY = 0xA6,
	INVERTDISPLAY = 0xA7,
	SETMULTIPLEX = 0xA8,
	DISPLAYOFF = 0xAE,
	DISPLAYON = 0xAF,
	COMSCANINC = 0xC0,
	COMSCANDEC = 0xC8,
	SETDISPLAYOFFSET = 0xD3,
	SETDISPLAYCLOCKDIV = 0xD5,
	SETPRECHARGE = 0xD9,
	SETCOMPINS = 0xDA,
	SETVCOMDETECT = 0xDB,

};

enum class VCCMode {
	EXTERNALVCC = 0x01,	 ///< External display voltage source
	SWITCHCAPVCC = 0x02, ///< Gen. display voltage from 3.3V
};

// @param  vccstate
// VCC selection. Pass SWITCHCAPVCC to generate the display
// voltage (step up) from the 3.3V source, or EXTERNALVCC
// otherwise. Most situations with Adafruit SSD1306 breakouts will
// want SWITCHCAPVCC.
template<VCCMode vccstate = VCCMode::SWITCHCAPVCC>
static constexpr uint8_t InitCmds[] = {

	DISPLAYOFF,			// 0xAE
	SETDISPLAYCLOCKDIV, // 0xD5
	0x80,				// the suggested ratio 0x80
	SETMULTIPLEX,		// 0xA8
	64 - 1,

	SETDISPLAYOFFSET,	// 0xD3
	0x0,				// no offset
	SETSTARTLINE | 0x0, // line #0
	CHARGEPUMP,			// 0x8D

	(vccstate == VCCMode::EXTERNALVCC) ? 0x10 : 0x14,

	MEMORYMODE, // 0x20
	0x00,		// 0x0 act like ks0108
	SEGREMAP | 0x1,
	COMSCANDEC,
	SETCOMPINS,
	0x12, //comPins
	SETCONTRAST,
	(vccstate == VCCMode::EXTERNALVCC) ? 0x9F : 0xCF,

	SETPRECHARGE, // 0xd9
	(vccstate == VCCMode::EXTERNALVCC) ? 0x22 : 0xF1,

	SETVCOMDETECT, // 0xDB
	0x40,
	DISPLAYALLON_RESUME, // 0xA4
	NORMALDISPLAY,		 // 0xA6
	DEACTIVATE_SCROLL,
	DISPLAYON, // Main screen turn on
};

static constexpr uint8_t StartRedrawCmds[] = {
	PAGEADDR,
	0,			// Page start address
	0xFF,		// Page end (not really, but works here)
	COLUMNADDR, // Column start address
	0,			// Column start
	128 - 1,	// Column end address
};
} // namespace SSD1306
