#pragma once
#include "util/math.hh"
#include <array>
#include <atomic>
#include <optional>
#include <span>

// Thread-safe Lock-free Single-Producer Single-Consumer
// For cheaply copied types
// Will not overwrite
template<class T, size_t max_size_>
class LockFreeFifoSpsc {
public:
	static_assert(MathTools::is_power_of_2(max_size_), "Size must be a power of 2");
	static constexpr size_t SIZE_MASK = max_size_ - 1;

	LockFreeFifoSpsc() = default;

	LockFreeFifoSpsc(std::span<T, max_size_> src) {
		memcpy(buf_.data(), src.data(), max_size_);
	}

	// Initialize with an offset between get and put
	// Useful, for example, if get() and put() happen at the same rates
	// and you want to provide a fixed delay
	LockFreeFifoSpsc(size_t head)
		: head_{head} {
	}

	//
	// Producer
	//
	bool put(T item) {
		auto tmp_head = head_.load(std::memory_order_relaxed);

		if ((tmp_head - tail_.load(std::memory_order_acquire)) == max_size_)
			return false;

		buf_[tmp_head & SIZE_MASK] = item;
		tmp_head++;
		std::atomic_signal_fence(std::memory_order_release);
		head_.store(tmp_head, std::memory_order_release);
		return true;
	}

	// Number of elements available to write
	size_t num_free() const {
		return max_size_ - (head_.load(std::memory_order_relaxed) - tail_.load(std::memory_order_acquire));
	}

	bool full() const {
		return num_free() == 0;
	}

	//
	// Consumer
	//
	std::optional<T> get() {
		auto tmp_tail = tail_.load(std::memory_order_relaxed);

		if (tmp_tail == head_.load(std::memory_order_relaxed)) {
			return std::nullopt;
		}

		auto item = buf_[tmp_tail & SIZE_MASK];
		tmp_tail++;
		std::atomic_signal_fence(std::memory_order_release);
		tail_.store(tmp_tail, std::memory_order_release);
		return item;
	}

	T get_or_default() {
		return get().value_or(T{});
	}

	void remove_first() {
		auto tmp_tail = tail_.load(std::memory_order_relaxed);

		if (tmp_tail != head_.load(std::memory_order_relaxed))
			tail_.store(++tmp_tail, std::memory_order_release);
	}

	// Number of elements available to read
	size_t num_filled() const {
		return head_.load(std::memory_order_acquire) - tail_.load(std::memory_order_relaxed);
	}

	bool empty() const {
		return num_filled() == 0;
	}

	// Reset can be done by consumer or producer
	void reset() {
		tail_.store(head_.load(std::memory_order_relaxed), std::memory_order_relaxed);
	}

	// Maximum number of elements it can hold
	constexpr size_t max_size() const {
		return max_size_;
	}

private:
	std::atomic<size_t> head_ = 0;
	std::atomic<size_t> tail_ = 0;
	std::atomic<bool> full_ = 0;
	std::array<T, max_size_> buf_{};
};
