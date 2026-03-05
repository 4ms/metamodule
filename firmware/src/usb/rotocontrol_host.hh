#pragma once

#include "midi_cdc_composite_host.hh"
#include "pr_dbg.hh"
#include <span>

class RotocontrolHost {
	MidiCdcCompositeHost &composite;
	bool has_started_rx = false;

public:
	RotocontrolHost(MidiCdcCompositeHost &host)
		: composite{host} {
	}

	void on_cdc_connected() {
		// Configure 115200 8N1
		if (!composite.set_cdc_line_coding(115200, 8, 0, 0)) {
			pr_err("RotocontrolHost: Failed to set line coding\n");
		} else {
			pr_trace("RotocontrolHost: Line coding set to 115200 8N1\n");
		}

		// Set DTR and RTS high
		if (!composite.set_cdc_control_line_state(true, true)) {
			pr_trace("RotocontrolHost: line state control (DTR/RTS) not supported\n");
		} else {
			pr_trace("RotocontrolHost: DTR/RTS set high\n");
		}

		// Set up receive callback
		composite.set_cdc_rx_callback([](uint8_t *data, uint32_t len) {
			pr_dbg("Rotocontrol CDC rx %lu bytes: ", len);
			for (uint32_t i = 0; i < len; i++) {
				pr_dbg("%02X ", data[i]);
			}
			pr_dbg("\n");
		});
	}

	void start_rx() {
		if (!has_started_rx) {
			if (composite.cdc_receive() == USBH_OK) {
				has_started_rx = true;
				pr_dbg("Started Roto RX\n");
			}
		}
	}

	bool send_commands(std::span<const uint8_t> data) {
		if (!composite.is_cdc_available() || !composite.is_connected())
			return false;
		return composite.cdc_transmit({const_cast<uint8_t *>(data.data()), data.size()});
	}
};
