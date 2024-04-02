#pragma once
#include <array>
#include <optional>

// CircularStack allows popping and pushing to the back (top) only.
// If the top exceeds MaxElements, then it'll overwrite the front (bottom).
template<typename T, int MaxElements>
class CircularStack {
	static_assert(MaxElements > 0, "Zero sized CircularStack not supported");

	std::array<T, MaxElements> data;

	int top_idx = 0;
	int bottom_idx = 0;

	//when top_idx == bottom_idx, we could be full or empty, so this flag differentiates
	bool full = false;

public:
	CircularStack() = default;

	template<typename... Ts>
	CircularStack(const Ts... t)
		: data{t...} {
	}

	void push_back(T el) {
		data[top_idx] = el;
		top_idx++;
		if (top_idx >= MaxElements)
			top_idx = 0;

		if (full)
			bottom_idx = top_idx;

		if (top_idx == bottom_idx) {
			full = true;
		}
	}

	std::optional<T> pop_back() {
		if (size() == 0)
			return std::nullopt;

		if (top_idx == 0)
			top_idx = MaxElements - 1;
		else
			top_idx--;

		full = false;

		return data[top_idx];
	}

	std::optional<T> back() {
		if (size() == 0)
			return std::nullopt;
		int t = (top_idx == 0) ? MaxElements - 1 : top_idx - 1;

		return data[t];
	}

	T pop_back_or_zero() {
		if (size() == 0)
			return T{};

		if (top_idx == 0)
			top_idx = MaxElements - 1;
		else
			top_idx--;

		full = false;

		return {data[top_idx]};
	}

	size_t size() const {
		if (full)
			return MaxElements;
		if (top_idx >= bottom_idx)
			return top_idx - bottom_idx;
		else
			return top_idx + MaxElements - bottom_idx;
	}

	constexpr size_t max_size() {
		return MaxElements;
	}

	void clear() {
		top_idx = 0;
		bottom_idx = 0;
		full = false;
	}

	bool empty() {
		if (full)
			return false;
		if (top_idx == bottom_idx)
			return true;
		return false;
	}
};
