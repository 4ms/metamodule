#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"
#include "midi_params.hh"
#include "params/metaparams.hh"
#include "params/params_state.hh"
#include "util/lockfree_fifo_spsc.hh"

namespace MetaModule
{

// TODO: set this up with all data that the GUI thread needs to see

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

	// Audio thread calls this
	void write_sync(ParamsState &params, MetaParams &) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			copy(p, params);
			HWSemaphore<ParamCacheLock>::unlock(WriteProcID);
		}
	}

	// UI thread calls this
	bool read_sync(ParamsState &params, MetaParams &) {
		bool read_ok = false;

		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(ReadProcID) == HWSemaphoreFlag::LockedOk) {
			transfer_events(params, p);
			HWSemaphore<ParamCacheLock>::unlock(ReadProcID);
			read_ok = true;
		}

		// while (true) {
		// 	if (auto event = midi_events.get(); event.has_value()) {
		// 		auto e = event.value();
		// 		if (e.type == Midi::Event::Type::CC && e.note < NumMidiCCs) {
		// 			params.midi_ccs[e.note].changed = 1;
		// 			params.midi_ccs[e.note].val = e.midi_chan;
		// 		}
		// 		if (e.type == Midi::Event::Type::NoteOn && e.note < NumMidiNotes) {
		// 			params.last_midi_note.changed = 1;
		// 			params.last_midi_note.val = e.note;
		// 			params.last_midi_note_channel = e.midi_chan;
		// 			params.midi_gate = true;
		// 		}
		// 		if (e.type == Midi::Event::Type::NoteOff && e.note < NumMidiNotes) {
		// 			params.last_midi_note.changed = 1;
		// 			params.last_midi_note.val = e.note;
		// 			params.last_midi_note_channel = e.midi_chan;
		// 			params.midi_gate = false;
		// 		}
		// 	} else
		// 		break;
		// }

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
