#pragma once
#include "drivers/i2c.hh"
#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <span>
#include <utility>

struct MIDI_expander_conf {
	uint8_t addr{};
};

struct MIDIExpander {
	static constexpr size_t MaxPayloadPerJack = 255;
	static constexpr size_t HeaderSize = 2;
	static constexpr size_t MaxPayload = MaxPayloadPerJack * 2;

	enum Commands : uint8_t {
		// return the 6-byte ID block below
		ReadId,
		// return 2 bytes, din size, trs size
		ReadSize,
		// return din size + trs size amount of data
		ReadData,

		WriteData,
	};

	// Expected values:
	static constexpr size_t IdSize = 6;
	static constexpr std::array<uint8_t, 4> IdSignature{0x04, 0x6d, 0x73, 0x00}; // "4ms\0"
	static constexpr uint8_t IdDeviceMidiExpander = 0x02;
	static constexpr uint8_t IdProtocolVersion = 0x01;

	struct Id {
		bool responded = false;
		bool signature_ok = false;
		uint8_t device_type = 0;
		uint8_t protocol_version = 0;
	};

	enum Error {
		None,
		ReadFailed,
		WriteFailed,
	};

	MIDIExpander(mdrivlib::I2CPeriph &i2c, const MIDI_expander_conf &conf)
		: _device_addr(conf.addr << 1)
		, _i2c{i2c} {
	}

	bool start() {
		return true;
	}

	// Blocking: only for use at scan time.
	Id read_id() {
		Id id{};

		uint8_t data[IdSize]{};
		auto err = _i2c.mem_read(_device_addr, Commands::ReadId, I2C_MEMADD_SIZE_8BIT, data, IdSize);
		if (err != mdrivlib::I2CPeriph::I2C_NO_ERR)
			return id;

		id.responded = true;
		id.signature_ok = std::ranges::equal(std::span{data}.first(IdSignature.size()), IdSignature);
		id.device_type = data[4];
		id.protocol_version = data[5];

		return id;
	}

	bool is_present() {
		const auto id = read_id();
		return id.signature_ok && id.device_type == IdDeviceMidiExpander && id.protocol_version == IdProtocolVersion;
	}

	void set_address(uint8_t dev_addr_unshifted) {
		_device_addr = dev_addr_unshifted << 1;
	}

	uint8_t dev_address() {
		return _device_addr >> 1;
	}

	// start/finish_read() can be used to split up blocking time
	auto read_sizes() {
		using namespace mdrivlib;
		auto err = _i2c.mem_read_IT(_device_addr, Commands::ReadSize, I2C_MEMADD_SIZE_8BIT, _rx_data, HeaderSize);
		return err == I2CPeriph::I2C_NO_ERR ? Error::None : Error::ReadFailed;
	}

	// Only call this once read_sizes() has actually completed: the sizes are read
	// back out of the RX buffer, and a transfer that failed leaves stale bytes there.
	auto read_payload() {
		using namespace mdrivlib;

		size_0 = _rx_data[0];
		size_1 = _rx_data[1];
		read_size = size_0 + size_1;
		if (!read_size) {
			return Error::None;
		}

		const auto err = _i2c.mem_read_IT(_device_addr, Commands::ReadData, I2C_MEMADD_SIZE_8BIT, _rx_data, read_size);
		return err == I2CPeriph::I2C_NO_ERR ? Error::None : Error::ReadFailed;
	}

	auto write_payload(std::span<const uint8_t> s0, std::span<const uint8_t> s1) {
		using namespace mdrivlib;

		if (s0.size() == 0 && s1.size() == 0) {
			return Error::None;
		}

		// Fail if a bad size was given. The caller must ensure size is <=255.
		if (s0.size() > MaxPayloadPerJack || s1.size() > MaxPayloadPerJack) {
			return Error::WriteFailed;
		}

		const auto payload_size = s0.size() + s1.size() + HeaderSize;
		_tx_data[0] = s0.size();
		_tx_data[1] = s1.size();
		std::ranges::copy(s0, &_tx_data[HeaderSize]);
		std::ranges::copy(s1, &_tx_data[HeaderSize + s0.size()]);

		const auto err =
			_i2c.mem_write_IT(_device_addr, Commands::WriteData, I2C_MEMADD_SIZE_8BIT, _tx_data, payload_size);

		return err == I2CPeriph::I2C_NO_ERR ? Error::None : Error::WriteFailed;
	}

	// The returned spans point into the RX buffer, which the next read overwrites:
	// consume them before advancing the state machine.
	std::array<std::span<const uint8_t>, 2> collect_payload() {
		return {{{&_rx_data[0], size_0}, {&_rx_data[size_0], size_1}}};
	}

	// Drop whatever the last read left behind, so a failed transfer can't be
	// collected as if it were valid MIDI.
	void discard_payload() {
		size_0 = 0;
		size_1 = 0;
		read_size = 0;
	}

private:
	uint8_t _device_addr;
	mdrivlib::I2CPeriph &_i2c;
	uint8_t size_0{};
	uint8_t size_1{};
	uint16_t read_size{};

	// RX and TX get their own buffers in case we overlap pre-loading TX while RX is happening
	// and/or copying/parsing RX while TX is happening
	uint8_t _rx_data[MaxPayload]{};
	uint8_t _tx_data[HeaderSize + MaxPayload]{};
};
