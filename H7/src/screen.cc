#include "screen.hh"
#include "screen_demo_pic.h"
// const unsigned int pic[19200];

void Screen::set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
	write<Data>(0x2a);
	write<Cmd>(Xstart >> 8);
	write<Cmd>(Xstart);
	write<Cmd>(Xend >> 8);
	write<Cmd>(Xend);

	write<Data>(0x2b);
	write<Cmd>(Ystart >> 8);
	write<Cmd>(Ystart);
	write<Cmd>(Yend >> 8);
	write<Cmd>(Yend);

	write<Data>(0x2c); // LCD_WriteCMD(GRAMWR);
}

#define ST7735_TFTWIDTH_128 128 // for 1.44 and mini
#define ST7735_TFTWIDTH_80 80 // for mini
#define ST7735_TFTHEIGHT_128 128 // for 1.44" display
#define ST7735_TFTHEIGHT_160 160 // for 1.8" and mini display

#define ST_CMD_DELAY 0x80 // special signifier for command lists

#define ST77XX_NOP 0x00
#define ST77XX_SWRESET 0x01
#define ST77XX_RDDID 0x04
#define ST77XX_RDDST 0x09

#define ST77XX_SLPIN 0x10
#define ST77XX_SLPOUT 0x11
#define ST77XX_PTLON 0x12
#define ST77XX_NORON 0x13

#define ST77XX_INVOFF 0x20
#define ST77XX_INVON 0x21
#define ST77XX_DISPOFF 0x28
#define ST77XX_DISPON 0x29
#define ST77XX_CASET 0x2A
#define ST77XX_RASET 0x2B
#define ST77XX_RAMWR 0x2C
#define ST77XX_RAMRD 0x2E

#define ST77XX_PTLAR 0x30
#define ST77XX_TEOFF 0x34
#define ST77XX_TEON 0x35
#define ST77XX_MADCTL 0x36
#define ST77XX_COLMOD 0x3A

#define ST77XX_MADCTL_MY 0x80
#define ST77XX_MADCTL_MX 0x40
#define ST77XX_MADCTL_MV 0x20
#define ST77XX_MADCTL_ML 0x10
#define ST77XX_MADCTL_RGB 0x00

#define ST77XX_RDID1 0xDA
#define ST77XX_RDID2 0xDB
#define ST77XX_RDID3 0xDC
#define ST77XX_RDID4 0xDD

// Some ready-made 16-bit ('565') color settings:
#define ST77XX_BLACK 0x0000
#define ST77XX_WHITE 0xFFFF
#define ST77XX_RED 0xF800
#define ST77XX_GREEN 0x07E0
#define ST77XX_BLUE 0x001F
#define ST77XX_CYAN 0x07FF
#define ST77XX_MAGENTA 0xF81F
#define ST77XX_YELLOW 0xFFE0
#define ST77XX_ORANGE 0xFC00

// clang-format off

static const uint8_t generic_st7789[] =  {                // Init commands for 7789 screens
    9,                              //  9 commands in list:
    ST77XX_SWRESET,   ST_CMD_DELAY, //  1: Software reset, no args, w/delay
      150,                          //     ~150 ms delay
    ST77XX_SLPOUT ,   ST_CMD_DELAY, //  2: Out of sleep mode, no args, w/delay
      10,                          //      10 ms delay
    ST77XX_COLMOD , 1+ST_CMD_DELAY, //  3: Set color mode, 1 arg + delay:
      0x55,                         //     16-bit color
      10,                           //     10 ms delay
    ST77XX_MADCTL , 1,              //  4: Mem access ctrl (directions), 1 arg:
      0x08,                         //     Row/col addr, bottom-top refresh
    ST77XX_CASET  , 4,              //  5: Column addr set, 4 args, no delay:
      0x00,
      0,        //     XSTART = 0
      0,
      240,  //     XEND = 240
    ST77XX_RASET  , 4,              //  6: Row addr set, 4 args, no delay:
      0x00,
      0,             //     YSTART = 0
      320>>8,
      320&0xFF,  //     YEND = 320
    ST77XX_INVON  ,   ST_CMD_DELAY,  //  7: hack
      10,
    ST77XX_NORON  ,   ST_CMD_DELAY, //  8: Normal display on, no args, w/delay
      10,                           //     10 ms delay
    ST77XX_DISPON ,   ST_CMD_DELAY, //  9: Main screen turn on, no args, delay
      10 };                          //    10 ms delay

// clang-format on

void Screen::init()
{
	// RES = 0;
	// delayms(10);
	// RES = 1;
	// delayms(120);

	init_display(generic_st7789);
	return;

	write<Cmd>(0x36); // MADCTL
	// if (DERECTION == 0)
	write<Data>(0x00);
	// else if (DERECTION == 2)
	// write<Data>(0x70);

	write<Cmd>(0x3A); // COLMOD
	write<Data>(0x05);

	write<Cmd>(0xB2); //??
	write<Data>(0x0C);
	write<Data>(0x0C);
	write<Data>(0x00);
	write<Data>(0x33);
	write<Data>(0x33);

	write<Cmd>(0xB7);
	write<Data>(0x35);

	write<Cmd>(0xBB);
	write<Data>(0x19);

	write<Cmd>(0xC0);
	write<Data>(0x2C);

	write<Cmd>(0xC2);
	write<Data>(0x01);

	write<Cmd>(0xC3);
	write<Data>(0x12);

	write<Cmd>(0xC4);
	write<Data>(0x20);

	write<Cmd>(0xC6);
	write<Data>(0x0F);

	write<Cmd>(0xD0);
	write<Data>(0xA4);
	write<Data>(0xA1);

	write<Cmd>(0xE0);
	write<Data>(0xD0);
	write<Data>(0x04);
	write<Data>(0x0D);
	write<Data>(0x11);
	write<Data>(0x13);
	write<Data>(0x2B);
	write<Data>(0x3F);
	write<Data>(0x54);
	write<Data>(0x4C);
	write<Data>(0x18);
	write<Data>(0x0D);
	write<Data>(0x0B);
	write<Data>(0x1F);
	write<Data>(0x23);

	write<Cmd>(0xE1);
	write<Data>(0xD0);
	write<Data>(0x04);
	write<Data>(0x0C);
	write<Data>(0x11);
	write<Data>(0x13);
	write<Data>(0x2C);
	write<Data>(0x3F);
	write<Data>(0x44);
	write<Data>(0x51);
	write<Data>(0x2F);
	write<Data>(0x1F);
	write<Data>(0x1F);
	write<Data>(0x20);
	write<Data>(0x23);

	write<Cmd>(0x21); // INVOFF

	write<Cmd>(0x11); // SLPOUT
	HAL_Delay(120);

	write<Cmd>(0x29); // DISPON
}

void Screen::demo()
{
	int n = 0;
	set_pos(60, 40, 179, 199);
	for (int j = 0; j < 160; j++) {
		for (int i = 0; i < 120; i++) {
			write<Cmd>(pic[n++]);
		}
	}
}

void Screen::init_display(const uint8_t *addr)
{
	uint8_t numCommands, cmd, numArgs;
	uint16_t ms;

	numCommands = *addr++;			 // Number of commands to follow
	while (numCommands--) {			 // For each command...
		cmd = *addr++;				 // Read command
		numArgs = *addr++;			 // Number of args to follow
		ms = numArgs & ST_CMD_DELAY; // If hibit set, delay follows args
		numArgs &= ~ST_CMD_DELAY;	 // Mask out delay bit
		write<Cmd>(cmd);
		while (numArgs--) {
			write<Data>(*addr++);
		}
		// sendCommand(cmd, addr, numArgs);
		// addr += numArgs;

		if (ms) {
			ms = *addr++; // Read post-command delay time (ms)
			if (ms == 255)
				ms = 500; // If 255, delay for 500 ms
			HAL_Delay(ms);
		}
	}
}
void Screen::set_rotation(uint8_t m)
{
	uint8_t madctl = 0;

	rotation = m & 3; // can't be higher than 3

	switch (rotation) {
		case 0:
			madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MY | ST77XX_MADCTL_RGB;
			// _xstart = _colstart;
			// _ystart = _rowstart;
			// _width = window_width;
			// _height = window_height;
			break;
		case 1:
			madctl = ST77XX_MADCTL_MY | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB;
			// _xstart = _rowstart;
			// _ystart = _colstart;
			// _height = window_width;
			// _width = window_height;
			break;
		case 2:
			madctl = ST77XX_MADCTL_RGB;
			if ((window_width == 135) && (window_height == 240)) {
				// _xstart = _colstart - 1;
				// _ystart = _rowstart;
			} else {
				// _xstart = 0;
				// _ystart = 0;
			}
			// _width = window_width;
			// _height = window_height;
			break;
		case 3:
			madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB;
			if ((window_width == 135) && (window_height == 240)) {
				// _xstart = _rowstart;
				// _ystart = _colstart;
			} else {
				// _xstart = 0;
				// _ystart = 0;
			}
			// _height = window_width;
			// _width = window_height;
			break;
	}
	write<Cmd>(ST77XX_MADCTL);
	write<Data>(madctl);
}

