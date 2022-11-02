#pragma once
#include "drivers/i2c.hh"
#include "fusb302_registers.hh"
#include <cstdint>

//Debugging:
#include "printf.h"
#include <optional>
#include <string_view>

namespace FUSB302
{

// TODO: add conf for INT pin and optional SRC Enable pin
struct Device {

	mdrivlib::I2CPeriph &i2c;
	uint8_t dev_addr;
	uint8_t device_id = 0;

	enum class ConnectedState { None, TogglePolling, AsHost, AsDevice } state = ConnectedState::None;

	Device(mdrivlib::I2CPeriph &i2c, uint8_t device_addr)
		: i2c{i2c}
		, dev_addr{device_addr} {
	}

	bool init() {
		uint8_t data;
		auto err = i2c.mem_read(dev_addr, 0x01, 1, &data, 1);
		if (err != mdrivlib::I2CPeriph::I2C_NO_ERR)
			return false;

		device_id = data;

		// Read Interrupt registers to clear them
		read(Register::Interrupt);
		read(Register::InterruptA);
		read(Register::InterruptB);
		return true;
	}

	uint8_t get_chip_id() {
		return device_id;
	}

	void start_drp_polling() {
		// Setup per datasheet p. 7 (Toggle Functionality)
		// TODO: which registers need to be reset? It doesnt toggle the second time unless we do a SWReset
		write(Register::Reset, Reset{.SWReset = 1});
		write(Register::Control0, Control0{.HostCurrent = Control0::DefaultCurrent, .MaskAllInt = 0});
		write(Register::Control2, Control2{.Toggle = 1, .PollingMode = Control2::PollDRP, .ToggleIgnoreRa = 1});
		write(Register::Switches0, Switches0{.ConnectVConnCC1 = 0, .ConnectVConnCC2 = 0});
		write(Register::Mask1,
			  Mask{.HostCurrentReq = 0,
				   .Collision = 1,
				   .Wake = 1,
				   .Alert = 1,
				   .CRCCheck = 1,
				   .CompChange = 1,
				   .CCBusActivity = 1,
				   .VBusOK = 1}); //0xFE
		write(Register::MaskA,
			  MaskA{.HardResetRx = 1,
					.SoftResetRx = 1,
					.TxSent = 1,
					.HardResetSent = 1,
					.RetryFail = 1,
					.SoftFail = 1,
					.ToggleDone = 0,
					.OCPTempEvent = 1});				 //0xBF
		write(Register::MaskA, MaskB{.GoodCRCSent = 1}); //0x01
		write(Register::Power,
			  Power{.BandGapAndWake = 1, .MeasureBlock = 1, .RXAndCurrentRefs = 1, .IntOsc = 1}); //0x01

		state = ConnectedState::TogglePolling;
	}

	ConnectedState get_state() {
		return state;
	}

	void handle_interrupt() {
		//read all Interrupt regs!
		reg_dump<FUSB302::Register::Interrupt>("Interrupt");
		reg_dump<FUSB302::Register::InterruptA>("InterruptA");
		reg_dump<FUSB302::Register::InterruptB>("InterruptB");
		//update state based on their contents
		switch (state) {
			case ConnectedState::TogglePolling: {
				// Look for plug event:
				Status1A status1a{read(Register::Status1A)};
				if (status1a.ToggleOutcomeIsSink)
					state = ConnectedState::AsDevice;
				else if (status1a.ToggleOutcomeIsCC1 || status1a.ToggleOutcomeIsCC2)
					state = ConnectedState::AsHost;
				//could also check Status0: Comp == 0 && BCLevel < 3
				//Comp == 0 means CC pin is read as less than reference, meaning device Rd pull-down was detected
				//BC<3 means CC pin is read as < 1.23V, meaning a device Rd pull-down was detected
			} break;

			case ConnectedState::AsDevice: {
				Status0 status0{read(Register::Status0)};
				// Look for unplug event:
				// VBusOK = 0 means no VBUS, BCLevel == 0 means CC detected as low (no host pull-up detected)
				if (status0.VBusOK == 0 && status0.BCLevel == 0)
					state = ConnectedState::None;
			} break;

			case ConnectedState::AsHost: {
				Status0 status{read(Register::Status0)};
				// Look for Unplug event:
				// Comp==1, BC==3 means CC pin is read as > 1.23V, meaning no device Rd pull-down
				//FIXME: why isn't Comp set at this point? it gets set a moment later...
				if (/*status.Comp == 1 &&*/ status.BCLevel == 3)
					state = ConnectedState::None;
			} break;

			case ConnectedState::None: {
				// printf_("State is currently None\n");
			} break;
		}
	}

	// Returns true on sucess
	bool write(Register reg, auto data) {
		auto d = static_cast<uint8_t>(data);
		return i2c.mem_write(dev_addr, static_cast<uint8_t>(reg), 1, &d, 1) == mdrivlib::I2CPeriph::I2C_NO_ERR;
	}

	//TODO: return std::expected<uint8_t> when compiler supports it
	uint8_t read(Register reg) {
		uint8_t data = 0;
		auto ok = i2c.mem_read(dev_addr, static_cast<uint16_t>(reg), 1, &data, 1);
		return data;
	}

	template<FUSB302::Register Reg>
	void reg_check(std::string_view regname) {
		static uint8_t last_val = 0xFF;
		auto val = read(Reg);
		if (val != last_val)
			printf_("%s: 0x%x\n", regname.data(), val);
		last_val = val;
	}

	template<FUSB302::Register Reg>
	void reg_dump(std::string_view regname) {
		auto val = read(Reg);
		printf_("%s: 0x%x\n", regname.data(), val);
		if constexpr (Reg == FUSB302::Register::Status0) {
			Status0 s{val};
			printf_("BCLevel=%d Wake=%d Comp=%d VBusOK=%d\n", s.BCLevel, s.Wake, s.Comp, s.VBusOK);
		}
	}
};

} // namespace FUSB302
