#pragma once
#include "drivers/i2c.hh"
#include "printf.h"
#include <cstdint>

namespace FUSB302
{

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

// TODO: add conf for INT pin and optional SRC Enable pin
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

	//TODO: std::expected when compiler supports it
	uint8_t read(Register reg) {
		uint8_t data = 0;
		auto ok = i2c.mem_read(dev_addr, static_cast<uint16_t>(reg), 1, &data, 1);
		return data;
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
	operator uint8_t() {
		return (PullDownCC1 << 0) | (PullDownCC2 << 1) | (MeasureCC1 << 2) | (MeasureCC2 << 3) |
			   (ConnectVConnCC1 << 4) | (ConnectVConnCC2 << 5) | (PullUpCC1 << 6) | (PullUpCC2 << 7);
	}
};

struct Switches1 {
	uint8_t EnableTXCC1 : 1;
	uint8_t EnableTXCC2 : 1;
	uint8_t AutoCRC : 1;
	uint8_t _res : 1;
	uint8_t DataRoleSrc : 1;
	uint8_t SpecRev : 2;
	uint8_t PowerRoleSrc : 1;

	operator uint8_t() {
		return (EnableTXCC1 << 0) | (EnableTXCC2 << 1) | (AutoCRC << 2) | (DataRoleSrc << 4) | (SpecRev << 5) |
			   (PowerRoleSrc << 7);
	}
};

struct Mesaure {
	uint8_t DAC : 6;
	uint8_t MeasureVBUS : 1;
	uint8_t _res : 1;

	operator uint8_t() {
		return (DAC << 0) | (MeasureVBUS << 6);
	}
};

struct Slice {
	uint8_t BMCSlicerDAC : 6;
	uint8_t SliderDACHys : 2;

	operator uint8_t() {
		return (BMCSlicerDAC << 0) | (SliderDACHys << 6);
	}
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
		return (TXStart << 0) | (AutoStartOnCRCRx << 1) | (HostCurrent << 2) | (MaskAllInt << 5) | (TXFlush << 6);
	}

	enum HostCurrents {
		NoCurrent = 0b00,
		DefaultCurrent = 0b01,
		MediumCurrent = 0b10,
		HighCurrent = 0b11,
	};
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
	operator uint8_t() {
		return (EnableSOP1 << 0) | (EnableSOP2 << 1) | (RXFlush << 2) | (BISTMode2 << 4) | (EnableSOP1Dbg << 5) |
			   (EnableSOP2Dbg << 6);
	}
};

struct Control2 {
	uint8_t Toggle : 1;
	uint8_t PollingMode : 2;
	uint8_t WakeEnable : 1;
	uint8_t _res2 : 1;
	uint8_t ToggleIgnoreRa : 1;
	uint8_t ToggleTime : 2;

	operator uint8_t() {
		return (Toggle << 0) | (PollingMode << 1) | (WakeEnable << 3) | (ToggleIgnoreRa << 5) | (ToggleTime << 6);
	}

	enum PollingModes {
		PollDRP = 0b01,
		PollSNK = 0b10,
		PollSRC = 0b11,
	};
};

struct Control3 {
	uint8_t AutoRetryCRC : 1;
	uint8_t NumRetries : 2;
	uint8_t AutoSoftReset : 1;
	uint8_t AutoHardReset : 1;
	uint8_t BISTTMode : 1;
	uint8_t SendHardReset : 1;
	uint8_t _res : 1;

	operator uint8_t() {
		return (AutoRetryCRC << 0) | (NumRetries << 1) | (AutoSoftReset << 3) | (AutoHardReset << 4) |
			   (BISTTMode << 5) | (SendHardReset << 6);
	}
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

	operator uint8_t() {
		return (HostCurrentReq << 0) | (Collision << 1) | (Wake << 2) | (Alert << 3) | (CRCCheck << 4) |
			   (CompChange << 5) | (CCBusActivity << 6) | (VBusOK << 7);
	}
};

// R/W
struct Power {
	uint8_t BandGapAndWake : 1;
	uint8_t MeasureBlock : 1;
	uint8_t RXAndCurrentRefs : 1;
	uint8_t IntOsc : 1;
	uint8_t _res : 4;

	operator uint8_t() {
		return (BandGapAndWake << 0) | (MeasureBlock << 1) | (RXAndCurrentRefs << 2) | (IntOsc << 3);
	}
};

// W/C
struct Reset {
	uint8_t SWReset : 1;
	uint8_t PDReset : 1;
	uint8_t _res : 6;

	operator uint8_t() {
		return (SWReset << 0) | (PDReset << 1);
	}
};

// R/W
struct OCPREG {
	uint8_t OverCurrentDivEighths : 3;
	uint8_t OverCurrentMax : 1;
	uint8_t _res : 4;

	operator uint8_t() {
		return (OverCurrentDivEighths << 0) | (OverCurrentMax << 3);
	}

	enum OverCurrentMax {
		_80mA = 0,
		_800mA = 1,
	};
};

// R/W
struct MaskA {
	uint8_t HardResetRx : 1;
	uint8_t SoftResetRx : 1;
	uint8_t TxSent : 1;
	uint8_t HardResetSent : 1;
	uint8_t RetryFail : 1;
	uint8_t SoftFail : 1;
	uint8_t ToggleDone : 1;
	uint8_t OCPTempEvent : 1;

	operator uint8_t() {
		return (HardResetRx << 0) | (SoftResetRx << 1) | (TxSent << 2) | (HardResetSent << 3) | (RetryFail << 4) |
			   (SoftFail << 5) | (ToggleDone << 6) | (OCPTempEvent << 7);
	}
};

// R/W
struct MaskB {
	uint8_t GoodCRCSent : 1;
	uint8_t _res : 7;

	operator uint8_t() {
		return (GoodCRCSent << 0);
	}
};

// R/W
struct Control4 {
	uint8_t ToggleExitAudio : 1;
	uint8_t _res : 7;

	operator uint8_t() {
		return (ToggleExitAudio << 0);
	}
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

	operator uint8_t() {
		return (HardReset << 0) | (SoftReset << 1) | (Power2 << 2) | (Power3 << 3) | (RetryFail << 4) | (SoftFail << 5);
	}
};

// RO
struct Status1A_alt {
	uint8_t RXSOP : 1;
	uint8_t RXSOP1Dbg : 1;
	uint8_t RXSOP2Dbg : 1;
	uint8_t ToggleOutcome : 3;
	uint8_t _res : 2;

	operator uint8_t() {
		return (RXSOP << 0) | (RXSOP1Dbg << 1) | (RXSOP2Dbg << 2) | (ToggleOutcome << 3);
	}

	//Bit 5 = Sink, Bit 4 = CC2, Bit 3 = CC1, where Audio is a Sink with both CCs
	enum ToggleOutcomes {
		Running = 0b000,
		SrcConCC1 = 0b001,
		SrcConCC2 = 0b010,
		SnkConCC1 = 0b101,
		SnkConCC2 = 0b110,
		AudioAcc = 0b111,
	};
};

//RO
struct Status1A {
	uint8_t RXSOP : 1;
	uint8_t RXSOP1Dbg : 1;
	uint8_t RXSOP2Dbg : 1;
	uint8_t ToggleOutcomeIsCC1 : 1;
	uint8_t ToggleOutcomeIsCC2 : 1;
	uint8_t ToggleOutcomeIsSink : 1;
	uint8_t _res : 2;

	operator uint8_t() {
		return (RXSOP << 0) | (RXSOP1Dbg << 1) | (RXSOP2Dbg << 2) | (ToggleOutcomeIsCC1 << 3) |
			   (ToggleOutcomeIsCC2 << 4) | (ToggleOutcomeIsSink << 5);
	}
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

	operator uint8_t() {
		return (HardResetRx << 0) | (SoftResetRx << 1) | (TxSent << 2) | (HardResetSent << 3) | (RetryFail << 4) |
			   (SoftFail << 5) | (ToggleDone << 6) | (OCPTempEvent << 7);
	}
};

// R/C
struct InterruptB {
	uint8_t GCRSent : 1;
	uint8_t _res : 7;

	operator uint8_t() {
		return (GCRSent << 0);
	}
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

	operator uint8_t() {
		return (BCLevel << 0) | (Wake << 2) | (Alert << 3) | (CRCCheck << 4) | (Comp << 5) | (Activity << 6) |
			   (VBusOK << 7);
	}
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

	operator uint8_t() {
		return (OCP << 0) | (OverTemp << 1) | (TXFull << 2) | (TXEmpty << 3) | (RXFull << 4) | (RXEmpty << 5) |
			   (RXSOP1 << 6) | (RXSOP2 << 7);
	}
};

//Read/Clear
struct Interrupt {
	uint8_t BLLevel : 1;
	uint8_t Collision : 1;
	uint8_t Wake : 1;
	uint8_t Alert : 1;
	uint8_t CRCCheck : 1;
	uint8_t CompChanged : 1;
	uint8_t Activity : 1;
	uint8_t VBusOK : 1;

	operator uint8_t() {
		return (BLLevel << 0) | (Collision << 1) | (Wake << 2) | (Alert << 3) | (CRCCheck << 4) | (CompChanged << 5) |
			   (Activity << 6) | (VBusOK << 7);
	}
};
} // namespace FUSB302

// How this was created:
// First, manually created the bitfield structs.
//
// Create operator uint8_t() for bitfields with all 1-bit fields:
//%s/^struct .*\zs\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;/\0\r\toperator uint8_t() { return (\1 << 0) | (\2 << 1) | (\3 << 2) | (\4 << 3) | (\5 << 4) | (\6 << 5) | (\7 << 6) | (\8 << 7); }/
// Create operator uint8_t for bitfields with seven fields. Must fill in shifts manually
// s/^struct .*\zs\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\ze};/\0\r\toperator uint8_t() { return (\1 << 0) | (\2 << X) | (\3 << X) | (\4 << X) | (\5 << X) | (\6 << X) | (\7 << X); }/
// Create operator uint8_t for bitfields with six fields. Must fill in shifts manually
// s/^struct .*\zs\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\ze};/\0\r\toperator uint8_t() { return (\1 << 0) | (\2 << X) | (\3 << X) | (\4 << X) | (\5 << X) | (\6 << X); }/
// Create operator uint8_t for bitfields with five fields. Must fill in shifts manually
// s/^struct .*\zs\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\ze};/\0\r\toperator uint8_t() { return (\1 << 0) | (\2 << X) | (\3 << X) | (\4 << X) | (\5 << X); }/
// Create operator uint8_t for bitfields with four fields. Must fill in shifts manually
// s/^struct .*\zs\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\tuint8_t \(.*\) : \d;\n\ze};/\0\r\toperator uint8_t() { return (\1 << 0) | (\2 << X) | (\3 << X) | (\4 << X); }/
// Three, two, and one fields are easy to do manually (typically have one or more _res)
// Afterwards, remove all (_res << \d);
// %s/ | (_res << \d)//g
