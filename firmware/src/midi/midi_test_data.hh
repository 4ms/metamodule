#include <array>
#include <cstdint>
#include <vector>

#if defined(DEMO_MIDI_IN)

static inline constexpr std::array<std::array<uint8_t, 4>, 28> MidiDemoData{{
	{0x0B, 0xB0, 0x50, 0x55},

	{0x1B, 0xB0, 0x10, 0x20},
	{0x1C, 0xC4, 0x10, 0x20},

	{0x28, 0x80, 0x60, 0x7F},
	{0x28, 0x90, 0x60, 0x00},
	{0x28, 0x90, 0x60, 0x00},

	{0x3F, 0xF8, 0x66, 0x77},

	// 2-byte sysex (0-byte payload)
	{0x36, 0xF0, 0xF7, 0x00},

	// 3-byte sysex (1-byte payload)
	{0x37, 0xF0, 0x01, 0xF7},

	// 4-byte sysex (2-byte payload)
	{0x34, 0xF0, 0x01, 0x02},
	{0x35, 0xF7, 0x00, 0x00},

	// 5-byte sysex (3-byte payload)
	{0x34, 0xF0, 0x01, 0x02},
	{0x36, 0x03, 0xF7, 0x00},

	// 6-byte sysex (4-byte payload)
	{0x34, 0xF0, 0x01, 0x02},
	{0x37, 0x03, 0x04, 0xF7},

	// 7-byte sysex (5-byte payload)
	{0x34, 0xF0, 0x01, 0x02},
	{0x34, 0x03, 0x04, 0x05},
	{0x35, 0xF7, 0x00, 0x00},

	// 8-byte sysex (6-byte payload)
	{0x34, 0xF0, 0x01, 0x02},
	{0x34, 0x03, 0x04, 0x05},
	{0x36, 0x06, 0xF7, 0x00},

	// 9-byte sysex (7-byte payload)
	{0x34, 0xF0, 0x01, 0x02},
	{0x34, 0x03, 0x04, 0x05},
	{0x37, 0x06, 0x07, 0xF7},

	// 10-byte sysex (8-byte payload)
	{0x34, 0xF0, 0x01, 0x02},
	{0x34, 0x03, 0x04, 0x05},
	{0x34, 0x06, 0x07, 0x08},
	{0x35, 0xF7, 0x00, 0x00},
}};

static inline unsigned md_idx = 0;

#endif

#if defined(DEMO_MIDI_OUT)
static std::vector<rack::midi::Message> MidiDemoData;

static void fill_midi_data() {
	using namespace rack;
	{
		midi::Message msg;
		msg.setUsbCable(1);
		msg.setChannel(7);
		msg.setStatus(0x8);
		msg.setNote(0x60);
		msg.setValue(0x20);
		MidiDemoData.push_back(msg);
	}
	{
		midi::Message msg;
		msg.setUsbCable(1);
		msg.setChannel(7);
		msg.setStatus(0x9);
		msg.setNote(0x60);
		msg.setValue(0x00);
		MidiDemoData.push_back(msg);
	}
	{
		midi::Message msg;
		msg.setUsbCable(0);
		msg.sysExNoPayload();
		MidiDemoData.push_back(msg);
	}
	{
		midi::Message msg;
		msg.setUsbCable(1);
		msg.sysExSingleByte(1);
		MidiDemoData.push_back(msg);
	}
	{
		midi::Message msg;
		msg.setUsbCable(2);
		msg.startSysEx(1, 2);
		MidiDemoData.push_back(msg);
		msg.endSysEx();
		MidiDemoData.push_back(msg);
	}
	{
		midi::Message msg;
		msg.setUsbCable(3);
		msg.startSysEx(1, 2);
		MidiDemoData.push_back(msg);
		msg.endSysEx(3);
		MidiDemoData.push_back(msg);
	}
	{
		midi::Message msg;
		msg.setUsbCable(4);
		msg.startSysEx(1, 2);
		MidiDemoData.push_back(msg);
		msg.endSysEx(3, 4);
		MidiDemoData.push_back(msg);
	}
	{
		midi::Message msg;
		msg.setUsbCable(5);
		msg.startSysEx(1, 2);
		MidiDemoData.push_back(msg);
		msg.continueSysEx(3, 4, 5);
		MidiDemoData.push_back(msg);
		msg.endSysEx();
		MidiDemoData.push_back(msg);
	}
	{
		midi::Message msg;
		msg.setUsbCable(6);
		msg.startSysEx(1, 2);
		MidiDemoData.push_back(msg);
		msg.continueSysEx(3, 4, 5);
		MidiDemoData.push_back(msg);
		msg.endSysEx(6);
		MidiDemoData.push_back(msg);
	}
	{
		midi::Message msg;
		msg.setUsbCable(7);
		msg.startSysEx(1, 2);
		MidiDemoData.push_back(msg);
		msg.continueSysEx(3, 4, 5);
		MidiDemoData.push_back(msg);
		msg.endSysEx(6, 7);
		MidiDemoData.push_back(msg);
	}
	{
		midi::Message msg;
		msg.setUsbCable(8);
		msg.startSysEx(1, 2);
		MidiDemoData.push_back(msg);
		msg.continueSysEx(3, 4, 5);
		MidiDemoData.push_back(msg);
		msg.continueSysEx(6, 7, 8);
		MidiDemoData.push_back(msg);
		msg.endSysEx();
		MidiDemoData.push_back(msg);
	}
}

#endif
