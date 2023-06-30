#include <cstdint>
#include <span>
#include <array>
#include <algorithm>
#include <cmath>

namespace Mapping
{

struct Point_t
{
	float x;
	float y;
};

namespace Impl
{
	template<typename T, std::size_t LEN, float min, float max, typename F>
	struct EmptyArray
	{
		constexpr EmptyArray(const F& func) : data()
		{
			for (std::size_t i = 0; i < LEN; i++)
			{
				data[i].x = min + i * (max - min) / float(LEN-1);
				data[i].y = func(data[i].x);
			}
		}
		std::array<T,LEN> data;
	};

	template <std::size_t LEN>
	bool constexpr isMonotonicallyIncreasing(const std::array<Point_t,LEN>& val)
	{
		for (std::size_t i=0; i<LEN-1; i++)
		{
			if (not (val[i].x < val[i+1].x))
			{
				return false;
			}
		}
		return true;
	}
}


template <std::size_t LEN>
class LookupTable_t
{
public:
    using Base_t = std::array<Point_t,LEN>;

public:
	constexpr LookupTable_t(const Base_t& input)
	{
		static_assert(LEN >= 2);
		std::copy_n(input.begin(), LEN, points.begin());
	}

	constexpr float lookup(float val) const
	{
		auto upper = std::upper_bound(points.begin(), points.end(), val, [](auto v, auto candidate)
		{
			return v < candidate.x;
		});

		if (upper == points.end())
		{
			return points.back().y;
		}
		else if (upper == points.begin())
		{
			return points.front().y;
		}
		else
		{
			auto lower = std::prev(upper);
			return std::lerp(lower->y, upper->y, (val - lower->x)/(upper->x - lower->x));
		}
	}

private:
	Base_t points;

public:
	template <float min, float max, typename F>
	static constexpr LookupTable_t<LEN> generate(const F func)
	{
		constexpr Impl::EmptyArray<Point_t, LEN, min, max, F> dataArray(func);
		static_assert(Impl::isMonotonicallyIncreasing(dataArray.data));
		return LookupTable_t<LEN> (dataArray.data);
	}

};




}