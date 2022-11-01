#pragma once
#include "drivers/i2c.hh"
#include "printf.h"
#include <cstdint>

namespace FUSB302
{

// TODO: Get USB-C working totally and move to its own class/file

enum class Register : uint8_t {
	ID = 0x01,
	Control0 = 0x06,
	Control1 = 0x07,
	Control2 = 0x08,
	Power = 0x0B,
	OCP = 0x0D,
	Status0A = 0x3C,
	Status1A = 0x3D,
	InterruptA = 0x3E,
	InterruptB = 0x3F,
	Status0 = 0x40,
	Status1 = 0x41,
	Interrupt = 0x42,
};

struct Device {

	mdrivlib::I2CPeriph &i2c;
	uint8_t dev_addr;

	Device(mdrivlib::I2CPeriph &i2c, uint8_t device_addr)
		: i2c{i2c}
		, dev_addr{device_addr} {
	}

	bool init() {
		uint8_t data;
		auto err = i2c.mem_read(dev_addr, 0x01, 1, &data, 1);
		if (err == mdrivlib::I2CPeriph::I2C_NO_ERR) {
			printf_("FUSB302 ID Read %d\n", data);
			return true;
		} else {
			printf_("FUSB302 ID Read Error: %d\n", err);
			return false;
		}
	}

	auto write(Register reg, auto data) {
		auto d = static_cast<uint8_t>(data);
		return i2c.mem_write(dev_addr, static_cast<uint8_t>(reg), 1, &d, 1);
	}
};

struct Switches0 {
	uint8_t PullDownCC1 : 1;
	uint8_t PullDownCC2 : 1;
	uint8_t MeasureCC1 : 1;
	uint8_t MeasureCC2 : 1;
	uint8_t ConnectVConnCC1 : 1;
	uint8_t ConnectVConnCC2 : 1;
	uint8_t PullUpCC1 : 1;
	uint8_t PullUpCC2 : 1;
};

struct Switches1 {
	uint8_t EnableTXCC1 : 1;
	uint8_t EnableTXCC2 : 1;
	uint8_t AutoCRC : 1;
	uint8_t _res : 1;
	uint8_t DataRoleSrc : 1;
	uint8_t SpecRev : 2;
	uint8_t PowerRoleSrc : 1;
};

struct Mesaure {
	uint8_t DAC : 6;
	uint8_t MeasureVBUS : 1;
	uint8_t _res : 1;
};

struct Slice {
	uint8_t BMCSlicerDAC : 6;
	uint8_t SliderDACHys : 2;
};

struct Control0 {
	uint8_t TXStart : 1;
	uint8_t AutoStartOnCRCRx : 1;
	uint8_t HostCurrent : 2;
	uint8_t _res2 : 1;
	uint8_t MaskAllInt : 1;
	uint8_t TXFlush : 1;
	uint8_t _res : 1;

	operator uint8_t() {
		return (HostCurrent << 2) | MaskAllInt M << 5
	}
};

struct Control1 {
	uint8_t EnableSOP1 : 1;
	uint8_t EnableSOP2 : 1;
	uint8_t RXFlush : 1;
	uint8_t _res2 : 1;
	uint8_t BISTMode2 : 1;
	uint8_t EnableSOP1Dbg : 1;
	uint8_t EnableSOP2Dbg : 1;
	uint8_t _res : 1;
};

struct Control2 {
	uint8_t Toggle : 1;
	uint8_t PollingMode : 2;
	uint8_t WakeEnable : 1;
	uint8_t _res2 : 1;
	uint8_t ToggleIgnoreRa : 1;
	uint8_t ToggleTime : 2;
};

struct Control3 {
	uint8_t AutoRetryCRC : 1;
	uint8_t NumRetries : 2;
	uint8_t AutoSoftReset : 1;
	uint8_t AutoHardReset : 1;
	uint8_t BISTTMode : 1;
	uint8_t SendHardReset : 1;
	uint8_t _res : 1;
};

struct Mask {
	uint8_t HostCurrentReq : 1;
	uint8_t Collision : 1;
	uint8_t Wake : 1;
	uint8_t Alert : 1;
	uint8_t CRCCheck : 1;
	uint8_t CompChange : 1;
	uint8_t CCBusActivity : 1;
	uint8_t VBusOK : 1;
};

// R/W
struct Power {
	uint8_t BandGapAndWake : 1;
	uint8_t MeasureBlock : 1;
	uint8_t RXAndCurrentRefs : 1;
	uint8_t IntOsc : 1;
	uint8_t _res : 4;
};

// W/C
struct Reset {
	uint8_t SWReset : 1;
	uint8_t PDReset : 1;
	uint8_t _res : 6;
};

// R/W
struct OCPREG {
	//TODO
};

// R/W
struct MaskA {
	//TODO
};

// R/W
struct MaskB {
	//TODO
};

// R/W
struct Control4 {
	uint8_t ToggleExitAudio : 1;
	uint8_t _res : 7;
};

// RO
struct Status0A {
	uint8_t HardReset : 1;
	uint8_t SoftReset : 1;
	uint8_t Power2 : 1;
	uint8_t Power3 : 1;
	uint8_t RetryFail : 1;
	uint8_t SoftFail : 1;
	uint8_t _res : 2;
};

// RO
struct Status1A {
	uint8_t RXSOP : 1;
	uint8_t RXSOP1Dbg : 1;
	uint8_t RXSOP2Dbg : 1;
	uint8_t ToggleOutcome : 3;
	uint8_t _res : 2;

	enum ToggleOutcomes {
		Running = 0b000,
		SrcConCC1 = 0b001,
		SrcConCC2 = 0b010,
		SnkConCC1 = 0b101,
		SnkConCC2 = 0b110,
		AudioAcc = 0b111,
	};
};

// R/C
struct InterruptA {
	uint8_t HardResetRx : 1;
	uint8_t SoftResetRx : 1;
	uint8_t TxSent : 1;
	uint8_t HardResetSent : 1;
	uint8_t RetryFail : 1;
	uint8_t SoftFail : 1;
	uint8_t ToggleDone : 1;
	uint8_t OCPTempEvent : 1;
};

// R/C
struct InterruptB {
	uint8_t GCRSent : 1;
	uint8_t _res : 7;
};

// RO
struct Status0 {
	uint8_t BCLevel : 2;
	uint8_t Wake : 1;
	uint8_t Alert : 1;
	uint8_t CRCCheck : 1;
	uint8_t Comp : 1;
	uint8_t Activity : 1;
	uint8_t VBusOK : 1;
};

// RO
struct Status1 {
	uint8_t OCP : 1;
	uint8_t OverTemp : 1;
	uint8_t TXFull : 1;
	uint8_t TXEmpty : 1;
	uint8_t RXFull : 1;
	uint8_t RXEmpty : 1;
	uint8_t RXSOP1 : 1;
	uint8_t RXSOP2 : 1;
};

//Read/Clear
struct Interrupt {
	uint8_t BLLevel : 1;
	uint8_t Collision : 1;
	uint8_t Wak : 1;
	uint8_t Alert : 1;
	uint8_t CRCCheck : 1;
	uint8_t CompChanged : 1;
	uint8_t Activity : 1;
	uint8_t VBusOK : 1;
};
} // namespace FUSB302
