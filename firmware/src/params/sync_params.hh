#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"
#include "metaparams.hh"
#include "params_state.hh"
#include "patch_play/patch_player.hh"
#include "util/lockfree_fifo_spsc.hh"

namespace MetaModule
{

// SyncParams class
// Thread-safe sharing of ParamsState and MetaParams.
// Each writer and reader keeps their own copy of data.
// Non-blocking, if simultaneous read/write occurs, it just returns
// (unmodified local copy will still be valid, just out-dated)
struct SyncParams {
	LockFreeFifoSpsc<Midi::Event, 64> midi_events;

private:
	ParamsState p;
	MetaParams m;

	static constexpr uint32_t WriteProcID = 1;
	static constexpr uint32_t ReadProcID = 2;

public:
	SyncParams() {
		clear();
	}

	void write_sync(ParamsState &params, MetaParams &metaparams) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			copy(p, params);
			m.update_with(metaparams);
			HWSemaphore<ParamCacheLock>::unlock(WriteProcID);
		}
	}

	bool read_sync(ParamsMidiState &params, MetaParams &metaparams) {
		using namespace mdrivlib;
		bool read_ok = false;
		if (HWSemaphore<ParamCacheLock>::lock(ReadProcID) == HWSemaphoreFlag::LockedOk) {
			transfer_events(params, p);
			metaparams.transfer(m);
			HWSemaphore<ParamCacheLock>::unlock(ReadProcID);
			read_ok = true;
		}

		while (true) {
			if (auto event = midi_events.get(); event.has_value()) {
				auto e = event.value();
				if (e.type == Midi::Event::Type::CC && e.note < NumMidiCCs) {
					params.last_midi_cc.num = e.note;
					params.last_midi_cc.channel = e.midi_chan;
					params.last_midi_cc.port = e.port;
					// e.val is 14-bit from the M4 core. GUI/knobset-control consumers
					// of this expect the coarse 7-bit value, so shift back down
					params.last_midi_cc.value = e.val >> 7;
				}
				if (e.type == Midi::Event::Type::PC) {
					params.last_midi_pc.num = static_cast<uint8_t>(e.val);
					params.last_midi_pc.value = -1;
					params.last_midi_pc.channel = e.midi_chan;
					params.last_midi_pc.port = e.port;
				}
				if (e.type == Midi::Event::Type::NoteOn && e.note < NumMidiNotes) {
					params.last_midi_note.num = e.note;
					params.last_midi_note.value = static_cast<int8_t>(e.val); //velocity
					params.last_midi_note.channel = e.midi_chan;
					params.last_midi_note.port = e.port;
					params.midi_gate = true;
				}
				if (e.type == Midi::Event::Type::NoteOff && e.note < NumMidiNotes) {
					params.last_midi_note.num = e.note;
					params.last_midi_note.value = 0;
					params.last_midi_note.channel = e.midi_chan;
					params.last_midi_note.port = e.port;
					params.midi_gate = false;
				}
			} else
				break;
		}

		return read_ok;
	}

	void clear() {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			p.clear();
			m.clear();
			HWSemaphore<ParamCacheLock>::unlock(WriteProcID);
		}
	}
};

} // namespace MetaModule
