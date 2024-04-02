#pragma once
#include "util/circular_buffer.hh"
// #include "lib/cpputil/util/math.hh"
#include "util/math.hh"

template<unsigned Size, class T = unsigned, unsigned InputValueBits = 12>
struct MovingAverage {
	static_assert(MathTools::is_power_of_2(Size) > 0, "MovingAverage<Size, T> requires Size to be a power of 2");

	using AccumT = unsigned;
	static_assert(sizeof(AccumT) * 8 >= (MathTools::Log2<Size>::val + InputValueBits));

public:
	MovingAverage() = default;

	T add_val(T newval) {
		sum_ -= buff_[idx_];
		buff_[idx_] = newval;
		sum_ += newval;
		inc_index();
		return sum_ >> oversample_shift_;
	}
	T val() {
		return sum_ >> oversample_shift_;
	}

private:
	constexpr static auto oversample_shift_ = MathTools::Log2<Size>::val;
	AccumT sum_ = 0;
	std::array<T, Size> buff_{};
	size_t idx_ = 0;

	void inc_index() {
		idx_ = (idx_ + 1) & (Size - 1);
	}
};

template<unsigned Size, class T = unsigned, unsigned InputValueBits = 12>
struct Oversampler {
	static_assert(MathTools::is_power_of_2(Size) > 0, "Oversampler<Size, T> requires Size to be a power of 2");

	using AccumT = unsigned;
	static_assert(sizeof(AccumT) * 8 >= (MathTools::Log2<Size>::val + InputValueBits));

public:
	Oversampler() = default;

	T add_val(T newval) {
		buff_ += newval;
		if (++idx_ >= Size) {
			val_ = buff_ >> oversample_shift_;
			idx_ = 0;
			buff_ = 0;
		}
		return val_;
	}
	T val() {
		return val_;
	}

private:
	constexpr static auto oversample_shift_ = MathTools::Log2<Size>::val;
	AccumT buff_ = 0;
	T val_ = 0;
	unsigned int idx_ = 0;
};

// Like Oversampler but returns a float, does not require Size to be a power of 2
template<unsigned Size, class T = unsigned, unsigned InputValueBits = 12>
struct SmoothOversampler {

	using AccumT = unsigned;
	static_assert(sizeof(AccumT) * 8 >= (MathTools::Log2<Size>::val + InputValueBits));

public:
	SmoothOversampler() = default;

	float add_val(T newval) {
		buff_ += newval;
		if (++idx_ >= Size) {
			val_ = buff_ / (float)Size;
			idx_ = 0;
			buff_ = 0;
		}
		return val_;
	}
	float val() {
		return val_;
	}

private:
	AccumT buff_ = 0;
	float val_ = 0;
	unsigned int idx_ = 0;
};

template<class T, class Transfer>
class NonLinearOnePoleLp {
	T state_;

public:
	NonLinearOnePoleLp(float state)
		: state_(state) {
	}
	NonLinearOnePoleLp()
		: state_(0.f) {
	}
	T add_val(T input) {
		state_ += Transfer::Process(input - state_);
		return state_;
	}

	T val() {
		return state_;
	}
};

template<size_t Divisor>
struct TransferQuadratic {
	static float Process(float x) {
		constexpr float const fact = 1.f / float(Divisor);
		return std::abs(x) * x * fact;
	}
};

template<size_t Numerator, size_t Divisor>
struct TransferHysteresis {
	static float Process(float x) {
		constexpr float const flat = float(Numerator) / float(Divisor);
		return x - std::clamp(x, -flat, flat);
	}
};

template<size_t Divisor>
class QuadraticOnePoleLp : public NonLinearOnePoleLp<float, TransferQuadratic<Divisor>> {};

template<size_t Numerator, size_t Divisor, typename T = float>
class HysteresisFilter : public NonLinearOnePoleLp<T, TransferHysteresis<Numerator, Divisor>> {};

template<typename T = unsigned>
struct NoFilter {
public:
	NoFilter() = default;

	T add_val(T newval) {
		val_ = newval;
		return val_;
	}
	T val() {
		return val_;
	}

private:
	T val_ = 0;
};

// Two filters in series
// Second is only filled when val() is called
template<typename T, typename FirstFilter, typename SecondFilter>
class CascadingFilter {
public:
	T add_val(T newval) {
		return f1.add_val(newval);
	}
	T val() {
		return f2.add_val(f1.val());
	}

private:
	FirstFilter f1{};
	SecondFilter f2{};
};
