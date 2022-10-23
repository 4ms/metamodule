#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"
#include "params.hh"

// ParamCache class
// Stores a copy of Params and MetaParams and allows access from single core
// where a higher-priority ISR does write_sync(), and a lower-priority ISR does read_sync()
// The users of this class should each have their own copy of Params and MetaParams.
//
// Todo: use HSEM to allow for multiple cores and inverted ISR priorities
namespace MetaModule
{

struct ParamQueue {
	Params p;
	MetaParams m;

	static constexpr uint32_t WriteProcID = 1;
	static constexpr uint32_t ReadProcID = 2;

	ParamQueue() {
		clear();
	}

	void write_sync(Params &p_, MetaParams &m_) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheWritable>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			p.copy(p_);
			m.update_with(m_);
			HWSemaphore<ParamCacheWritable>::unlock(WriteProcID);
		}
	}

	bool read_sync(Params *params, MetaParams *metaparams) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheWritable>::lock(ReadProcID) == HWSemaphoreFlag::LockedOk) {
			params->copy(p);
			metaparams->transfer(m);
			HWSemaphore<ParamCacheWritable>::unlock(ReadProcID);
			return true;
		}
		return false;
	}

	void clear() {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheWritable>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			p.clear();
			m.clear();
			HWSemaphore<ParamCacheWritable>::unlock(WriteProcID);
		}
	}
};
} // namespace MetaModule
