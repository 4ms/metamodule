#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <span>

namespace Mapping
{

struct Point_t {
	float y;
};

namespace Impl
{
#ifdef __clang__
template<typename T, std::size_t LEN, int min10, int max10, typename F>
#else
template<typename T, std::size_t LEN, float min, float max, typename F>
#endif
struct EmptyArray {
	constexpr EmptyArray(const F &func)
		: data() {
#ifdef __clang__
	constexpr float min = min10 / 10.f;
	constexpr float max = max10 / 10.f;
#endif
		for (std::size_t i = 0; i < LEN; i++) {
			auto x = min + i * (max - min) / float(LEN - 1);
			data[i].y = func(x);
		}
	}
	std::array<T, LEN> data;
};

} // namespace Impl

#ifdef __clang__
template<int min10, int max10, std::size_t LEN>
#else
template<float min, float max, std::size_t LEN>
#endif
class LookupTable_t {
public:
	using Base_t = std::array<Point_t, LEN>;

public:
	constexpr LookupTable_t(const Base_t &input) {
		static_assert(LEN >= 2);
		std::copy_n(input.begin(), LEN, points.begin());
	}

	constexpr float lookup(float val) const {
		float idx = ((val - min) / (max - min)) * (LEN - 1);

		if (idx <= 0.f)
			return points.front().y;
		else if (idx >= (LEN - 1))
			return points.back().y;
		else {
			auto lower_idx = (uint32_t)idx;
			float phase = idx - lower_idx;
			auto lower = points[lower_idx];
			auto upper = points[lower_idx + 1];
			return lower.y + phase * (upper.y - lower.y);
		}
	}

private:
	Base_t points;
#ifdef __clang__
	constexpr static float min = min10 / 10.f;
	constexpr static float max = max10 / 10.f;
#endif

public:
	template<typename F>
	static constexpr LookupTable_t generate(const F func) {
#ifdef __clang__
		constexpr Impl::EmptyArray<Point_t, LEN, min10, max10, F> dataArray(func);
#else
		constexpr Impl::EmptyArray<Point_t, LEN, min, max, F> dataArray(func);
#endif
		return LookupTable_t(dataArray.data);
	}
};

} // namespace Mapping
