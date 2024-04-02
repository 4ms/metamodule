#pragma once
#include <cstddef>
#include <cstring>
#include <span>

// CircularBufferAccess is a circular buffer where the backing data
// is external and passed by reference to the constructor
template<class T>
requires requires(T &x, typename T::value_type y) {
	x[0] = y;
	y = x[0];
	{
		x.size()
	};
	// {
	// 	x.data()
	// };
}
class CircularBufferAccess {
public:
	using value_type = typename T::value_type;

	CircularBufferAccess(T &buffer, size_t initial_offset = 0)
		: buf{buffer}
		, sz{buffer.size()}
		, rd{0}
		, wr{initial_offset} {
	}

	void clear() {
		// std::memset(buf, 0, size);
		for (size_t i = 0; i < sz; i++)
			buf[i] = 0;
	}

	bool read(std::span<value_type> read_data) {
		bool wrapped = false;
		for (auto &d : read_data) {
			d = buf[rd++];
			if (rd >= sz) {
				rd = 0;
				wrapped = true;
			}
		}
		return wrapped;
	}

	bool read_reverse(std::span<value_type> read_data) {
		bool wrapped = false;
		for (auto &d : read_data) {
			d = buf[rd--];
			if (rd >= sz) {
				rd = sz - 1;
				wrapped = true;
			}
		}
		return wrapped;
	}

	bool write(const std::span<const value_type> newdata, float phase = 1.f) {
		bool wrapped = false;
		for (auto d : newdata) {
			value_type xfade = d * phase + buf[wr] * (1.f - phase);
			buf[wr++] = xfade;
			if (wr >= sz) {
				wr = 0;
				wrapped = true;
			}
		}
		return wrapped;
	}

	bool write_reverse(const std::span<const value_type> newdata, float phase = 1.f) {
		bool wrapped = false;
		for (auto d : newdata) {
			value_type xfade = d * phase + buf[wr] * (1.f - phase);
			buf[wr--] = xfade;
			if (wr >= sz) {
				wr = sz - 1;
				wrapped = true;
			}
		}
		return wrapped;
	}

	bool read_check_crossed(std::span<value_type> read_data, size_t marker) {
		bool was_before_marker = rd <= marker;
		bool wrapped = read(read_data);
		bool is_before_marker = rd <= marker;
		bool changed_marker_side = was_before_marker != is_before_marker;
		bool crossed_marker = changed_marker_side != wrapped;
		return crossed_marker; //|| newdata.size() >= sz;
	}

	bool read_reverse_check_crossed(std::span<value_type> read_data, size_t marker) {
		bool was_before_marker = rd <= marker;
		bool wrapped = read_reverse(read_data);
		bool is_before_marker = rd <= marker;
		bool changed_marker_side = was_before_marker != is_before_marker;
		bool crossed_marker = changed_marker_side != wrapped;
		return crossed_marker; //|| newdata.size() >= sz;
	}

	bool write_check_crossed(const std::span<const value_type> newdata, size_t marker) {
		bool was_before_marker = wr < marker;
		bool wrapped = write(newdata);
		bool is_before_marker = wr < marker;
		bool changed_marker_side = was_before_marker != is_before_marker;
		bool crossed_marker = changed_marker_side != wrapped;
		return crossed_marker; //|| newdata.size() >= sz;
	}

	// TODO: use this
	// Writes largest contigious block it can without wrapping wr.
	// Returns number of elements that were not written
	// size_t write_contigious(std::span<value_type> newdata) {
	// 	auto num_elements = std::min(newdata.size(), size - wr);
	// 	auto sz = num_elements * sizeof(value_type);
	// 	std::memcpy(buf.data(), newdata.data(), sz);
	// 	wr += num_elements;
	// 	return newdata.size() - num_elements;
	// }

	//wr_pos() returns the index of the *next* element written by write()
	size_t wr_pos() const {
		return wr;
	}

	void wr_pos(size_t pos) {
		wr = pos;
	}

	//rd_pos() returns the index of the *next* element read by read()
	size_t rd_pos() const {
		return rd;
	}
	void rd_pos(size_t pos) {
		rd = pos;
	}

	size_t size() const {
		return sz;
	}

private:
	T &buf;
	size_t sz;
	size_t rd;
	size_t wr;
};
