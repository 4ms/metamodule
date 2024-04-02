#include "doctest.h"
#include "util/wear_level.hh"
#include <array>
#include <iostream>
#include <cstdint>

struct SomeData {
	uint32_t data = 0xFFFFFFFF;
	bool validate() {
		if (data % 1000 == 0)
			return true;
		else
			return false;
	}
};

constexpr auto NumCells = 4;

// Spy variables:
int num_reads = 0;
int num_writes = 0;
int num_erases = 0;
size_t last_cell_written = 0xFFFFFFFF;
size_t last_cell_read = 0xFFFFFFFF;
void reset_counts() {
	num_erases = 0;
	num_writes = 0;
	num_reads = 0;
}
bool SimulateFailedErasing = false;
bool SimulateBadCell = false;
bool RandomizeInitialValues = false;
uint32_t BadCell = 2;

std::array<SomeData, NumCells> underlying_data;
void randomize_underlying_data() {
	for (auto &b : underlying_data) {
		uint32_t x;
		do {
			x = std::rand();
			//avoid randomly blanking a sector out
			//avoid randomly creating valid data
		} while (x == SomeData{}.data || SomeData{x}.validate());
		b = SomeData{x};
	}
}
void initialize_underlying_data() {
	for (auto &b : underlying_data)
		b = SomeData{};
}

template<size_t Size, typename DataT>
struct DataBlock {
	static_assert(Size == NumCells, "Test harness only supports underlying data of NumCells size");

	using data_t = DataT;
	static constexpr size_t cell_nr_ = Size;

	bool read(data_t &data, size_t cell) {
		num_reads++;
		last_cell_read = cell;
		if (cell >= cell_nr_)
			return false;
		data = underlying_data[cell];
		return true;
	}

	bool write(const data_t &data, size_t cell) {
		num_writes++;
		last_cell_written = cell;
		if (cell >= cell_nr_)
			return false;

		//If we're simulating bad blocks, don't write to the BadBlockCell
		if (!(SimulateBadCell && BadCell == cell))
			// Simulate writing to Flash: can only clear bits, cannot set bits
			underlying_data[cell].data &= data.data;

		return true;
	}

	bool erase() {
		num_erases++;
		if (SimulateFailedErasing) {
			randomize_underlying_data();
		} else {
			for (auto &b : underlying_data)
				b = SomeData{};
		}
		return true;
	}

	bool is_writeable(size_t cell) {
		if (cell >= cell_nr_)
			return false;
		return underlying_data[cell].data == 0xFFFFFFFF;
	}
};

TEST_CASE("Normal Usage") {
	SimulateFailedErasing = false;
	SimulateBadCell = false;
	reset_counts();

	SUBCASE("First read on a blank/random block should return false, meaning we need to erase") {
		initialize_underlying_data();
		WearLevel<DataBlock<NumCells, SomeData>> w;

		SomeData data;
		CHECK_FALSE(w.read(data));
		CHECK(num_reads == NumCells);
		CHECK(num_writes == 0);
		CHECK(num_erases == 0);

		AND_THEN("Writing first time works on first try, with no erases") {
			reset_counts();

			data.data = 1000;
			CHECK(w.write(data));

			CHECK(num_reads == 0);
			CHECK(num_writes == 1);
			CHECK(num_erases == 0);
			CHECK(last_cell_written == 0);

			SUBCASE("And reads back OK") {
				data.data = 0;
				CHECK(w.read(data));
				CHECK(data.data == 1000);
			}

			AND_THEN("Writing up until number of cells works with no erasing, and reads back ok") {
				reset_counts();

				for (int i = 1; i < NumCells; i++) {
					data.data = i * 1000;
					CHECK(w.write(data));
					CHECK(num_reads == i - 1);
					CHECK(num_writes == i);
					CHECK(num_erases == 0);
					CHECK(last_cell_written == i);

					data.data = 0;
					CHECK(w.read(data));
					CHECK(data.data == i * 1000);
				}

				AND_THEN("Writing to a full block results in an attempted write, an erase, and a write to first cell") {
					reset_counts();

					data.data = 9000;
					CHECK(w.write(data));

					// One write: checking for writeable sectors triggers an erase, then we write to cell 0
					CHECK(num_writes == 1);
					CHECK(num_reads == 0);
					CHECK(num_erases == 1);
					CHECK(last_cell_written == 0);

					AND_THEN("Reading should return last valid written value") {
						data.data = 0;
						CHECK(w.read(data));
						CHECK(data.data == 9000);

						AND_THEN("Writing an invalid value, and then reading should return the last valid value") {
							auto cached = last_cell_read;
							data.data = 1;
							CHECK(w.write(data));
							data.data = 0;
							CHECK(w.read(data));
							CHECK(data.data == 9000);
							CHECK(last_cell_read == cached);

							data.data = 999;
							CHECK(w.write(data));
							data.data = 0;
							CHECK(w.read(data));
							CHECK(data.data == 9000);
							CHECK(last_cell_read == cached);

							data.data = 4000;
							CHECK(w.write(data));
							data.data = 0;
							CHECK(w.read(data));
							CHECK(data.data == 4000);
							CHECK(last_cell_read != cached);
						}
					}
				}
			}
		}
	}
}

//Test with DataBlock that has a faulty Erase()
TEST_CASE("Flash Block fails to erase completely, returns false first time it writes over a sector") {
	SimulateFailedErasing = true;
	SimulateBadCell = false;

	initialize_underlying_data();
	WearLevel<DataBlock<NumCells, SomeData>> w;
	SomeData data;

	AND_THEN("Writing works once per cell, since cells are pre-initialized in this test framework") {
		for (int i = 0; i < NumCells; i++) {
			CHECK(w.write(data));
		}

		AND_THEN("Writing back at the first cell fails, since every sector fails to write") {

			CHECK_FALSE(w.write(data));
		}
	}
}

TEST_CASE("Flash will skip a bad cell (bad = writing to it doesn't work)") {
	SimulateFailedErasing = false;
	SimulateBadCell = true;
	BadCell = 2;

	initialize_underlying_data();
	WearLevel<DataBlock<NumCells, SomeData>> w;
	SomeData data;

	// Write then Read Cell 0
	data.data = 1000;
	CHECK(w.write(data));
	CHECK(last_cell_written == 0);
	data.data = 0;
	CHECK(w.read(data));
	CHECK(data.data == 1000);

	// Write then Read Cell 1
	data.data = 2000;
	CHECK(w.write(data));
	CHECK(last_cell_written == 1);
	data.data = 0;
	CHECK(w.read(data));
	CHECK(data.data == 2000);
	CHECK(last_cell_read == 1);

	// Write Cell 2: Bad Block!
	data.data = 3000;
	CHECK(w.write(data));
	CHECK(last_cell_written == 2);

	SUBCASE("Immediately read bad cell: falls back on last valid value, then works fine") {
		data.data = 0;
		CHECK(w.read(data));
		// Should be the last valid value
		CHECK(data.data == 2000);
		CHECK(last_cell_read == 1);

		AND_THEN("Works normally once cell past bad cell is written") {
			// Write then Read Cell 3
			data.data = 4000;
			CHECK(w.write(data));
			CHECK(last_cell_written == 3);
			data.data = 0;
			CHECK(w.read(data));
			CHECK(data.data == 4000);
			CHECK(last_cell_read == 3);

			// Write then Read Cell 0
			data.data = 5000;
			CHECK(w.write(data));
			CHECK(last_cell_written == 0);
			data.data = 0;
			CHECK(w.read(data));
			CHECK(data.data == 5000);
			CHECK(last_cell_read == 0);
		}
	}

	SUBCASE("Writes again past bad block") {
		// Write then Read Cell 3
		data.data = 4000;
		CHECK(w.write(data));
		CHECK(last_cell_written == 3);
		data.data = 0;
		CHECK(w.read(data));
		CHECK(data.data == 4000);
		CHECK(last_cell_read == 3);
	}
}

TEST_CASE("Flash contains garbage data on power-up") {
	SimulateFailedErasing = false;
	SimulateBadCell = false;

	randomize_underlying_data();
	WearLevel<DataBlock<NumCells, SomeData>> w;

	AND_THEN("Fails on first read because there is no valid data") {
		SomeData data;
		CHECK_FALSE(w.read(data));
		AND_THEN("First write causes an erase, and then a successful write") {
			reset_counts();
			data.data = 3000;
			CHECK(w.write(data));
			CHECK(num_erases == 1);
			CHECK(num_writes == 1);
			AND_THEN("Subsqeuent read returns value written") {
				data.data = 0;
				w.read(data);
				CHECK(data.data == 3000);
			}
		}
	}
}

TEST_CASE("Flash contains initialized data on power-up") {
	SimulateFailedErasing = false;
	SimulateBadCell = false;

	initialize_underlying_data();
	WearLevel<DataBlock<NumCells, SomeData>> w;

	reset_counts();
	AND_THEN("Fails on first read because there is no valid data") {
		SomeData data;
		CHECK_FALSE(w.read(data));
		AND_THEN("First write works with no erase") {
			data.data = 3000;
			CHECK(w.write(data));
			CHECK(num_erases == 0);
			CHECK(num_writes == 1);
			AND_THEN("Subsqeuent read returns value written") {
				data.data = 0;
				w.read(data);
				CHECK(data.data == 3000);
			}
		}
	}
}

TEST_CASE("Flash contains valid data on power-up") {
	SimulateFailedErasing = false;
	SimulateBadCell = false;

	underlying_data[0] = SomeData{4000};
	underlying_data[1] = SomeData{5000};
	underlying_data[2] = SomeData{};
	underlying_data[3] = SomeData{};
	WearLevel<DataBlock<NumCells, SomeData>> w;

	reset_counts();
	AND_THEN("First read succeeds and finds latest valid value") {
		SomeData data;
		CHECK(w.read(data));
		CHECK(data.data == 5000);

		AND_THEN("Writing writes to the first empty cell") {
			data.data = 6000;
			CHECK(w.write(data));

			data.data = 0;
			CHECK(w.read(data));
			CHECK(data.data == 6000);
		}
	}
}
