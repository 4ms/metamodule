#pragma once
#include <atomic>
#include <functional>
#include <type_traits>

namespace MetaModule
{

// Synchronously run a function on Core 0 from Core 1, used to make sure
// SMP-using code runs on the core that drives Core 1 via SGI.
// Core 0 must call init() before any dispatches occur from Core 1.
struct RunOnCore0 {
	static inline std::function<void()> work;
	static inline std::atomic<bool> done{false};

	static void init() {
	}

	static bool is_core0() {
		return true;
	}

	template<typename Fn>
	static auto run(Fn fn) -> std::invoke_result_t<Fn> {
		using R = std::invoke_result_t<Fn>;

		if (is_core0())
			return fn();

		if constexpr (!std::is_void_v<R>)
			return R{};
	}
};

} // namespace MetaModule
