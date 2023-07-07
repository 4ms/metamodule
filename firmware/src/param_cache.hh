#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
#include "params.hh"

// ParamCache class
// Stores a copy of Params and MetaParams and allows thread-safe R/W access.
//
namespace MetaModule
{

struct ParamCache {
	Params p;
	MetaParams m;

	static constexpr uint32_t WriteProcID = 1;
	static constexpr uint32_t ReadProcID = 2;

	ParamCache() {
		clear();
	}

	void write_sync(Params &p_, MetaParams &m_) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			p.copy(p_);
			m.update_with(m_);
			HWSemaphore<ParamCacheLock>::unlock(WriteProcID);
		}
	}

	bool read_sync(Params *params, MetaParams *metaparams) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(ReadProcID) == HWSemaphoreFlag::LockedOk) {
			params->copy(p);
			metaparams->transfer(m);
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

struct ParamCacheSync {
	ParamCache &param_cache;
	ParamBlock &param_block;

	ParamCacheSync(ParamCache &param_cache, ParamBlock &param_block)
		: param_cache{param_cache}
		, param_block{param_block} {
	}

	~ParamCacheSync() {
		param_cache.write_sync(param_block.params[0], param_block.metaparams);
		mdrivlib::SystemCache::clean_dcache_by_range(&param_cache, sizeof(ParamCache));
	}
};

} // namespace MetaModule
