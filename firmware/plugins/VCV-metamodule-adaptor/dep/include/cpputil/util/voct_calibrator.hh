#pragma once
#include <tuple>

template<typename T = float>
	requires std::is_signed_v<T>
struct VoctCalibrator {
	enum Note : int { C0 = 0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, None };

	void reset() {
		offset_ = 0;
		slope_ = 0;
		measured_C0_ = false;
		num_datapt_ = 0;
	}

	void record_measurement(Note note, T measurement) {
		if (note == Note::None)
			return;

		// Special-case: C0 measurement overrides offset calculation
		if (note == Note::C0) {
			measured_C0_ = true;
			offset_ = measurement;
		}

		// Keep only the latest two data points
		if (num_datapt_ >= 2) {
			datapt_[0] = datapt_[1];
			num_datapt_ = 1;
		}

		datapt_[num_datapt_] = std::make_pair(note, measurement);
		num_datapt_++;

		if (num_datapt_ >= 2) {
			int octave_span = (int)datapt_[0].first - (int)datapt_[1].first;
			T measurement_diff = datapt_[0].second - datapt_[1].second;
			if (octave_span != 0 && measurement_diff != 0) {
				slope_ = measurement_diff / static_cast<T>(octave_span);
			}

			if (!measured_C0_) {
				T offset_0 = datapt_[0].second - (slope_ * (int)datapt_[0].first);
				T offset_1 = datapt_[1].second - (slope_ * (int)datapt_[1].first);
				offset_ = (offset_0 + offset_1) / 2;
			}
		}
	}

	T offset() const { return offset_; }
	T slope() const { return slope_; }

private:
	T offset_{0};
	T slope_{0};
	std::pair<Note, T> datapt_[2]{{None, 0}, {None, 0}};
	unsigned num_datapt_{0};

	bool measured_C0_ = false;
};
