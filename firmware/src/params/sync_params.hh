#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"
#include "params/metaparams.hh"
#include "params/params_state.hh"

namespace MetaModule
{

// SyncParams class
// Thread-safe sharing of ParamsState and MetaParams.
// Each writer and reader keeps their own copy of data.
// A third copy of the data is kept internally in this class.
// Non-blocking, if simultaneous read/write occurs, it just returns
// (unmodified local copy will still be valid, just out-dated)
struct SyncParams {

private:
	ParamsState p;
	MetaParams m;

	static constexpr uint32_t WriteProcID = 1;
	static constexpr uint32_t ReadProcID = 2;

public:
	SyncParams() {
		clear();
	}

	// copy to internal
	void write_sync(ParamsState &params, MetaParams &metaparams) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			copy(p, params);
			m.update_with(metaparams);
			HWSemaphore<ParamCacheLock>::unlock(WriteProcID);
		}
	}

	// copy from internal
	bool read_sync(ParamsState &params, MetaParams &metaparams) {
		bool read_ok = false;

		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(ReadProcID) == HWSemaphoreFlag::LockedOk) {
			transfer_events(params, p);
			metaparams.transfer(m);
			HWSemaphore<ParamCacheLock>::unlock(ReadProcID);
			read_ok = true;
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
