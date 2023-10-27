#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"
#include "metaparams.hh"
#include "params_state.hh"
#include "util/lockfree_fifo_spsc.hh"

namespace MetaModule
{

// SyncParams class
// Thread-safe sharing of ParamsState and MetaParams.
// Each writer and reader keeps their own copy of data.
// Non-blocking, if simultaneous read/write occurs, it just returns
// (unmodified local copy will still be valid, just out-dated)
struct SyncParams {
	ParamsState p;
	MetaParams m;
	LockFreeFifoSpsc<Midi::Event, 64> midi_events;

	static constexpr uint32_t WriteProcID = 1;
	static constexpr uint32_t ReadProcID = 2;

	SyncParams() {
		clear();
	}

	void write_sync(ParamsState &p_, MetaParams &m_) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			p.copy_from(p_);
			m.update_with(m_);
			HWSemaphore<ParamCacheLock>::unlock(WriteProcID);
		}
	}

	bool read_sync(ParamsState &params, MetaParams &metaparams) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(ReadProcID) == HWSemaphoreFlag::LockedOk) {
			p.copy_to(params);
			metaparams.transfer(m);
			HWSemaphore<ParamCacheLock>::unlock(ReadProcID);
			return true;
		}
		return false;
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
