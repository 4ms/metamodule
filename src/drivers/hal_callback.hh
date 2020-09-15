#ifndef _SRC_DRIVERS_HAL_CALLBACK
#define _SRC_DRIVERS_HAL_CALLBACK

#ifdef STM32F7
	#include "stm32f7xx.h"
#else
#endif

enum class HALCallbackID {
	MemTxCplt,
};

class HALCallbackManager {
public:
	struct HALCBBase {
		virtual void halcb() = 0;
	};
	using HALCBType = HALCBBase *;
	static inline void registerHALCB(HALCallbackID cbnum, HALCBType cb_obj)
	{
		HALCBs[static_cast<uint8_t>(cbnum)] = cb_obj;
	}
	static inline void callHALCB(HALCallbackID cbnum)
	{
		HALCBs[static_cast<uint8_t>(cbnum)]->halcb();
	}

private:
	static inline HALCBType HALCBs[128];
};

#endif
