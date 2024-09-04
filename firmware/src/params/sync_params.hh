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
			copy(params, p);
			metaparams.transfer(m);
			HWSemaphore<ParamCacheLock>::unlock(ReadProcID);
			read_ok = true;
		}

		while (true) {
			if (auto event = midi_events.get(); event.has_value()) {
				auto e = event.value();
				if (e.type == Midi::Event::Type::CC && e.note < NumMidiCCs)
					params.midi_ccs[e.note].store_changed(e.val / 10.f);

				if (e.type == Midi::Event::Type::NoteOn && e.note < NumMidiNotes) {
					params.last_midi_note.store_changed(e.note);
					params.midi_gate = true;
				}
				if (e.type == Midi::Event::Type::NoteOff && e.note < NumMidiNotes) {
					params.last_midi_note.store_changed(e.note);
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
