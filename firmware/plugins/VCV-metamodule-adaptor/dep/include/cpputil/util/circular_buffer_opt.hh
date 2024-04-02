#pragma once
#include "util/math.hh"
#include <array>
#include <optional>

// Same as CircularBuffer but returns std::optional<T> for get()
// Not thread-safe (consumer and producer must not interrupt each other)
template<class T, size_t max_size_>
class CircularBufferOpt {
public:
	static_assert(MathTools::is_power_of_2(max_size_), "CircularBuffer size must be a power of 2");
	static constexpr size_t SIZE_MASK = max_size_ - 1;

	CircularBufferOpt() = default;

	void put(T item) {
		buf_[head_] = item;

		if (full_)
			inc_tail();

		inc_head();
		full_ = head_ == tail_;
	}

	[[nodiscard("Use remove_first() if discarding result of get()")]] std::optional<T> get() {
		if (empty()) {
			return std::nullopt;
		}

		// Read data and advance the tail (we now have a free space)
		auto val = buf_[tail_];
		full_ = false;
		inc_tail();

		return val;
	}

	// Set the position of the next put().
	// Useful, for example, if get() and put() happen at the same rates
	// and you want to provide a fixed delay (similar to double-buffering)
	void set_head(size_t head) {
		head_ = head;
	}

	// get the next element but discard it
	void remove_first() {
		if (!empty()) {
			full_ = false;
			inc_tail();
		}
	}

	// Return a reference to the first element
	// T &first() const {
	// 	return buf_[tail_];
	// }

	//TODO: allow access to any element with operator[]

	void reset() {
		head_ = tail_;
		full_ = false;
	}

	bool empty() const {
		// if head and tail are equal, we are empty
		return (!full_ && (head_ == tail_));
	}

	bool full() const {
		return full_;
	}

	// Maximum number of elements it can hold
	constexpr size_t max_size() const {
		return max_size_;
	}
	constexpr size_t max_capacity() const {
		return max_size_;
	}

	// Number of elements filled
	size_t count() const {
		size_t size = max_size_;

		if (!full_) {
			if (head_ >= tail_)
				size = head_ - tail_;
			else
				size = max_size_ + head_ - tail_;
		}

		return size;
	}

	void fill_buffer(std::array<T, max_size_> &src) {
		memcpy(buf_.data(), src.data(), max_size_);
	}

	void fill_buffer(T val) {
		memset(buf_.data(), val, max_size_);
	}

	// Alias for count()
	size_t num_filled() const {
		return count();
	}

	size_t get_head_idx() const {
		return head_;
	}

	size_t get_tail_idx() const {
		return tail_;
	}

private:
	void inc_head() {
		head_ = (head_ + 1) & SIZE_MASK;
		// head_ = (head_ + 1) % max_size_;
	}

	void inc_tail() {
		tail_ = (tail_ + 1) & SIZE_MASK;
		// tail_ = (tail_ + 1) % max_size_;
	}

private:
	std::array<T, max_size_> buf_{};
	size_t head_ = 0;
	size_t tail_ = 0;
	bool full_ = false;
};
