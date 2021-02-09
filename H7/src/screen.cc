#include "screen.hh"
#include "screen_demo_pic.h"
// const unsigned int pic[19200];

void Screen::set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
	write<CmdPacket>(0x2a);
	write<DataPacket>(Xstart >> 8);
	write<DataPacket>(Xstart);
	write<DataPacket>(Xend >> 8);
	write<DataPacket>(Xend);

	write<CmdPacket>(0x2b);
	write<DataPacket>(Ystart >> 8);
	write<DataPacket>(Ystart);
	write<DataPacket>(Yend >> 8);
	write<DataPacket>(Yend);

	write<CmdPacket>(0x2c); // LCD_WriteCMD(GRAMWR);
}

void Screen::init()
{
	// RES = 0;
	// delayms(10);
	// RES = 1;
	// delayms(120);

	write<DataPacket>(0x36);
	// if (DERECTION == 0)
	write<CmdPacket>(0x00);
	// else if (DERECTION == 2)
	// write<CmdPacket>(0x70);

	write<DataPacket>(0x3A);
	write<CmdPacket>(0x05);

	write<DataPacket>(0xB2);
	write<CmdPacket>(0x0C);
	write<CmdPacket>(0x0C);
	write<CmdPacket>(0x00);
	write<CmdPacket>(0x33);
	write<CmdPacket>(0x33);

	write<DataPacket>(0xB7);
	write<CmdPacket>(0x35);

	write<DataPacket>(0xBB);
	write<CmdPacket>(0x19);

	write<DataPacket>(0xC0);
	write<CmdPacket>(0x2C);

	write<DataPacket>(0xC2);
	write<CmdPacket>(0x01);

	write<DataPacket>(0xC3);
	write<CmdPacket>(0x12);

	write<DataPacket>(0xC4);
	write<CmdPacket>(0x20);

	write<DataPacket>(0xC6);
	write<CmdPacket>(0x0F);

	write<DataPacket>(0xD0);
	write<CmdPacket>(0xA4);
	write<CmdPacket>(0xA1);

	write<DataPacket>(0xE0);
	write<CmdPacket>(0xD0);
	write<CmdPacket>(0x04);
	write<CmdPacket>(0x0D);
	write<CmdPacket>(0x11);
	write<CmdPacket>(0x13);
	write<CmdPacket>(0x2B);
	write<CmdPacket>(0x3F);
	write<CmdPacket>(0x54);
	write<CmdPacket>(0x4C);
	write<CmdPacket>(0x18);
	write<CmdPacket>(0x0D);
	write<CmdPacket>(0x0B);
	write<CmdPacket>(0x1F);
	write<CmdPacket>(0x23);

	write<DataPacket>(0xE1);
	write<CmdPacket>(0xD0);
	write<CmdPacket>(0x04);
	write<CmdPacket>(0x0C);
	write<CmdPacket>(0x11);
	write<CmdPacket>(0x13);
	write<CmdPacket>(0x2C);
	write<CmdPacket>(0x3F);
	write<CmdPacket>(0x44);
	write<CmdPacket>(0x51);
	write<CmdPacket>(0x2F);
	write<CmdPacket>(0x1F);
	write<CmdPacket>(0x1F);
	write<CmdPacket>(0x20);
	write<CmdPacket>(0x23);

	write<DataPacket>(0x21);

	write<DataPacket>(0x11);
	HAL_Delay(120);

	write<DataPacket>(0x29);
}

void Screen::demo()
{
	int n = 0;
	set_pos(60, 40, 179, 199);
	for (int j = 0; j < 160; j++) {
		for (int i = 0; i < 120; i++) {
			write<DataPacket>(pic[n++]);
		}
	}
}
