#pragma once
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "params/params_state.hh"

namespace MetaModule
{

// SyncParams class
// Thread-safe sharing of ParamsState between audio and GUI threads.
// The audio thread writes and the GUI thread reads.
// The writer and reader keep their own copy of data, and another copy is stored here.
//
// Non-blocking, if simultaneous read/write occurs, it just returns
// (unmodified local copy will still be valid, just out-dated)
class SyncParams {

	ParamsState p;

	static constexpr uint32_t WriteProcID = 1;
	static constexpr uint32_t ReadProcID = 2;

public:
	SyncParams() {
		clear();
	}

	// Audio thread calls this (~7us)
	void write_sync(ParamsState &params) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			accumulate_events(p, params);
			HWSemaphore<ParamCacheLock>::unlock(WriteProcID);
		}
		// FIXME: we could miss an event if the lock fails
	}

	// UI thread calls this
	bool read_sync(ParamsState &param_state) {
		bool read_ok = false;

		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(ReadProcID) == HWSemaphoreFlag::LockedOk) {
			transfer_events(param_state, p);
			HWSemaphore<ParamCacheLock>::unlock(ReadProcID);
			read_ok = true;
		}

		return read_ok;
	}

	void clear() {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			p.clear();
			HWSemaphore<ParamCacheLock>::unlock(WriteProcID);
		}
	}
};

} // namespace MetaModule
