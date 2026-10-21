#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"

namespace MetaModule
{

// MP2: the A35 (codec) and the M33 (FUSB302, jack sense) share I2C4. Hold this while using the bus,
// including while (re)initializing the peripheral: mdrivlib's I2CPeriph::init() resets it.
// (Only one context per core uses the bus, so a single process ID is enough.)
struct SharedI2CGuard {
	SharedI2CGuard() {
		while (mdrivlib::HWSemaphore<SharedI2CLock>::lock(ProcID) != mdrivlib::HWSemaphoreFlag::LockedOk)
			;
	}

	~SharedI2CGuard() {
		mdrivlib::HWSemaphore<SharedI2CLock>::unlock(ProcID);
	}

	SharedI2CGuard(const SharedI2CGuard &) = delete;
	SharedI2CGuard &operator=(const SharedI2CGuard &) = delete;

private:
	static constexpr uint32_t ProcID = 0;
};

} // namespace MetaModule
