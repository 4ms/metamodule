#include "sim_midi.hh"
#include <cstdint>
#include <cstdio>

#if defined(SIM_HAS_RTMIDI)
#include "RtMidi.h"
#endif

namespace MetaModule
{

#if defined(SIM_HAS_RTMIDI)

namespace
{
constexpr const char *kInPortName = "MetaModule Simulator In";
constexpr const char *kOutPortName = "MetaModule Simulator Out";
constexpr const char *kClientName = "MetaModule Simulator";

// Pick the MIDI API explicitly rather than RtMidi::UNSPECIFIED. UNSPECIFIED opens
// every compiled API in turn looking for one that already has ports, which (a)
// probes JACK on macOS -- spamming errors when no JACK server runs -- and (b) is
// the wrong heuristic for virtual ports, which we create rather than connect to.
// Prefer the native platform API and only fall back to JACK/other as a last resort.
RtMidi::Api chosen_api() {
	std::vector<RtMidi::Api> apis;
	RtMidi::getCompiledApi(apis);

	const RtMidi::Api preferred[] = {
		RtMidi::MACOSX_CORE,
		RtMidi::LINUX_ALSA,
		RtMidi::WINDOWS_MM,
		RtMidi::UNIX_JACK,
	};
	for (auto want : preferred)
		for (auto have : apis)
			if (have == want)
				return want;

	for (auto have : apis)
		if (have != RtMidi::RTMIDI_DUMMY)
			return have;

	return RtMidi::UNSPECIFIED;
}

// Number of bytes in a MIDI message given its status byte (serial MIDI, not USB).
// Returns 0 for status bytes we don't emit (e.g. SysEx, which is handled elsewhere).
unsigned midi_tx_length(uint8_t status) {
	if (status < 0x80)
		return 0; // not a status byte

	if (status < 0xF0) {
		// Channel voice messages
		switch (status >> 4) {
			case 0xC: // Program Change
			case 0xD: // Channel Pressure
				return 2;
			default: // Note off/on, poly-key pressure, CC, pitch-bend
				return 3;
		}
	}

	// System messages
	switch (status) {
		case 0xF1: // MTC quarter frame
		case 0xF3: // Song select
			return 2;
		case 0xF2: // Song position pointer
			return 3;
		case 0xF6: // Tune request
			return 1;
		default:
			// System real-time (0xF8..0xFF) are single-byte; SysEx (0xF0/0xF7) not sent here.
			return (status >= 0xF8) ? 1 : 0;
	}
}
} // namespace

struct SimMidi::Impl {
	RtMidiIn *in = nullptr;
	RtMidiOut *out = nullptr;

	~Impl() {
		delete in;
		delete out;
	}
};

SimMidi::SimMidi(Config config) {
	impl_ = new Impl();

	try {
		impl_->in = new RtMidiIn(chosen_api(), kClientName);

		// Keep timing/transport messages (MIDI clock is a supported event), but
		// ignore SysEx (not representable as MidiMessage) and active sensing (the
		// audio path also filters 0xFE).
		impl_->in->ignoreTypes(/*sysex=*/true, /*timing=*/false, /*activesense=*/true);

		if (config.in_port) {
			unsigned n = impl_->in->getPortCount();
			if (*config.in_port >= 0 && (unsigned)*config.in_port < n) {
				impl_->in->openPort(*config.in_port, kInPortName);
				connected_ = true;
			} else {
				std::printf("SimMidi: input port %d out of range (0..%u); MIDI input disabled\n",
							*config.in_port,
							n ? n - 1 : 0);
			}
		} else {
			impl_->in->openVirtualPort(kInPortName);
			connected_ = true;
		}

		if (connected_)
			impl_->in->setCallback(&SimMidi::rx_callback, this);

	} catch (RtMidiError &e) {
		std::printf("SimMidi: MIDI input init failed: %s\n", e.getMessage().c_str());
		delete impl_->in;
		impl_->in = nullptr;
	}

	try {
		impl_->out = new RtMidiOut(chosen_api(), kClientName);

		if (config.out_port) {
			unsigned n = impl_->out->getPortCount();
			if (*config.out_port >= 0 && (unsigned)*config.out_port < n) {
				impl_->out->openPort(*config.out_port, kOutPortName);
				connected_ = true;
			} else {
				std::printf("SimMidi: output port %d out of range (0..%u); MIDI output disabled\n",
							*config.out_port,
							n ? n - 1 : 0);
			}
		} else {
			impl_->out->openVirtualPort(kOutPortName);
			connected_ = true;
		}

	} catch (RtMidiError &e) {
		std::printf("SimMidi: MIDI output init failed: %s\n", e.getMessage().c_str());
		delete impl_->out;
		impl_->out = nullptr;
	}

	if (connected_)
		std::printf("SimMidi: MIDI ready (in: %s, out: %s)\n",
					config.in_port ? "hardware port" : "virtual port",
					config.out_port ? "hardware port" : "virtual port");
	else
		std::printf("SimMidi: no MIDI ports opened; MIDI is disabled\n");
}

SimMidi::~SimMidi() {
	delete impl_;
}

void SimMidi::rx_callback(double, std::vector<unsigned char> *message, void *userdata) {
	if (message && userdata)
		static_cast<SimMidi *>(userdata)->push_incoming(*message);
}

void SimMidi::push_incoming(const std::vector<unsigned char> &bytes) {
	if (bytes.empty())
		return;

	// SysEx and other >3-byte payloads are not represented by MidiMessage; skip them.
	if (bytes.size() > 3)
		return;

	uint8_t status = bytes[0];
	uint8_t d0 = bytes.size() > 1 ? bytes[1] : 0;
	uint8_t d1 = bytes.size() > 2 ? bytes[2] : 0;

	// The 3-arg constructor deduces the USB cable/CIN header from the status byte.
	rx_fifo_.put(MidiMessage{status, d0, d1});
}

void SimMidi::send(MidiMessage msg) {
	if (!impl_ || !impl_->out)
		return;

	uint8_t status = (uint8_t)msg.status;
	unsigned len = midi_tx_length(status);
	if (len == 0)
		return;

	std::vector<unsigned char> bytes;
	bytes.reserve(len);
	bytes.push_back(status);
	if (len > 1)
		bytes.push_back(msg.data.byte[0]);
	if (len > 2)
		bytes.push_back(msg.data.byte[1]);

	try {
		impl_->out->sendMessage(&bytes);
	} catch (RtMidiError &e) {
		std::printf("SimMidi: send failed: %s\n", e.getMessage().c_str());
	}
}

void SimMidi::list_ports() {
	try {
		RtMidiIn in(chosen_api(), kClientName);
		unsigned nin = in.getPortCount();
		std::printf("Available MIDI input ports (%u):\n", nin);
		for (unsigned i = 0; i < nin; i++)
			std::printf("  %u: %s\n", i, in.getPortName(i).c_str());
	} catch (RtMidiError &e) {
		std::printf("MIDI input: %s\n", e.getMessage().c_str());
	}

	try {
		RtMidiOut out(chosen_api(), kClientName);
		unsigned nout = out.getPortCount();
		std::printf("Available MIDI output ports (%u):\n", nout);
		for (unsigned i = 0; i < nout; i++)
			std::printf("  %u: %s\n", i, out.getPortName(i).c_str());
	} catch (RtMidiError &e) {
		std::printf("MIDI output: %s\n", e.getMessage().c_str());
	}

	std::printf("(Pass no --midiin/--midiout to create virtual 'MetaModule Simulator' ports instead.)\n");
}

#else // !SIM_HAS_RTMIDI -- inert stub build

SimMidi::SimMidi(Config) {
	std::printf("SimMidi: built without rtmidi; MIDI is disabled. "
				"Run `git submodule update --init simulator/rtmidi` and rebuild.\n");
}

SimMidi::~SimMidi() = default;

void SimMidi::rx_callback(double, std::vector<unsigned char> *, void *) {
}

void SimMidi::push_incoming(const std::vector<unsigned char> &) {
}

void SimMidi::send(MidiMessage) {
}

void SimMidi::list_ports() {
	std::printf("Simulator was built without rtmidi (MIDI disabled).\n"
				"Run `git submodule update --init simulator/rtmidi` and rebuild to enable MIDI.\n");
}

#endif

} // namespace MetaModule
