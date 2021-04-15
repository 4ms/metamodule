#pragma once
#include "drivers/hsem.hh"

template<unsigned SemID>
class SemaphoreActionOnUnlock {
	using CallbackT = std::function<void(void)>;

public:
	SemaphoreActionOnUnlock(CallbackT &&callback)
	{
		HWSemaphore<SemID>::clear_ISR();
		HWSemaphore<SemID>::disable_channel_ISR();
		HWSemaphoreGlobalBase::register_channel_ISR<SemID>(std::forward<CallbackT>(callback));
		HWSemaphore<SemID>::enable_channel_ISR();
	}

	~SemaphoreActionOnUnlock()
	{
		HWSemaphore<SemID>::clear_ISR();
		HWSemaphore<SemID>::disable_channel_ISR();
	}
};
