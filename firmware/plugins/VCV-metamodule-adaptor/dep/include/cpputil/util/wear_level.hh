#pragma once
#include <cstddef>

template<class Storage>
// require:
// Storage::data_t
// Storage::data_t::validate() --> bool
// Storage::read(data_t, size_t)
// Storage::write(data_t, size_t) --> bool
// Storage::erase()
// Storage::is_writeable(size_t) --> bool
class WearLevel : Storage {
	size_t cell_ = Storage::cell_nr_;

public:
	using data_t = typename Storage::data_t;

	// Scan the block from top to bottom for the first valid data.
	// Assign the cell_ value such that the next cell we will (try to) write is
	// the cell after the one containing the first valid data
	WearLevel() {
		data_t data;
		while (cell_) {
			if (Storage::read(data, --cell_)) {
				if (data.validate()) {
					cell_++;
					return;
				}
			}
		}
	}

	// Reads the latest valid data, starting with the last written cell and scanning downwards.
	// Returns false only if the bottom of the block is reached without finding any valid data.
	bool read(data_t &data) {
		size_t c = cell_;
		while (c) {
			Storage::read(data, --c);
			if (data.validate()) {
				return true;
			}
		}
		return false;
	}

	// Attempts to write to a new cell.
	// Checks if the cell is writable first, and if not it keeps trying
	// with the next sequential cell until it finds a writable cell.
	// Once the top of block is reached, it erases the block and starts back at the first cell.
	// If the top of the block is reached a second time, it returns false.
	// Otherwise it writes the data and returns the result of the low-level write.
	bool write(const data_t &data) {
		bool erased_once = false;
		while (!Storage::is_writeable(cell_)) {
			cell_++;
			if (cell_ >= Storage::cell_nr_) {
				if (erased_once)
					return false;
				if (!Storage::erase())
					return false;
				cell_ = 0;
				erased_once = true;
			}
		}
		return Storage::write(data, cell_++);
	}
};
