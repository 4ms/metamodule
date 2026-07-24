#pragma once
#include "drivers/i2c.hh"
#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include <cstdint>
#include <span>
#include <utility>

struct MIDI_expander_conf {
	uint8_t addr{};
};

struct MIDIExpander {
	enum Commands : uint8_t {
		Reserved,
		// return 2 bytes, din size, trs size
		ReadSize,
		// return din size + trs size amount of data
		ReadData,

		WriteData,
	};

	enum Error {
		None,
		ReadFailed,
		WriteFailed,
	};

	MIDIExpander(mdrivlib::I2CPeriph &i2c, const MIDI_expander_conf &conf)
		: _conf{conf}
		, _device_addr(conf.addr << 1)
		, _i2c{i2c} {
	}

	bool start() {
		return true;
	}

	bool is_present() {
		auto err = _i2c.mem_read(_device_addr, Commands::ReadSize, I2C_MEMADD_SIZE_8BIT, _data, 2);
		return err == mdrivlib::I2CPeriph::I2C_NO_ERR;
	}

	// Todo:
	// Create an EXTI interrupt to respond to chip telling us there's a pin change
	// void start_ISR(std::function<void(void)> &&cb) {
	// 	callback = std::move(cb);
	// 	InterruptManager::registerISR(_conf.IRQn, _conf.pri1, _conf.pri2, [&]() { callback(); });
	// }

	void set_address(uint8_t dev_addr_unshifted) {
		_device_addr = dev_addr_unshifted << 1;
	}

	uint8_t dev_address() {
		return _device_addr >> 1;
	}

	// start/finish_read() can be used to split up blocking time
	auto read_sizes() {
		using namespace mdrivlib;
		auto err = _i2c.mem_read_IT(_device_addr, Commands::ReadSize, I2C_MEMADD_SIZE_8BIT, _data, 2);
		return err == I2CPeriph::I2C_NO_ERR ? Error::None : Error::WriteFailed;
	}

	auto read_payload() {
		using namespace mdrivlib;

		size_0 = _data[0];
		size_1 = _data[1];
		read_size = size_0 + size_1;
		if (!read_size) { return Error::None; }

		const auto err = _i2c.mem_read_IT(_device_addr, Commands::ReadData, I2C_MEMADD_SIZE_8BIT, _data, read_size);
		return err == I2CPeriph::I2C_NO_ERR ? Error::None : Error::ReadFailed;
	}

	std::array<std::span<const uint8_t>, 2> collect_payload() {
		return {{{&_data[0], size_0}, {&_data[size_0], size_0 + size_1}}};
	}

private:
	const MIDI_expander_conf &_conf;
	uint8_t _device_addr;
	mdrivlib::I2CPeriph &_i2c;
	uint8_t size_0{};
	uint8_t size_1{};
	uint16_t read_size{};
	uint8_t _data[512]{};
};
