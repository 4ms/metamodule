#pragma once
#include <stm32f7xx.h>

constexpr uint32_t Log2Int(const uint32_t x) {
    for (int i=0; i<32; i++)
        if (x==(1UL<<i)) return i;
    return 0;
}

template<class T, int size>
struct Oversampler {
//Todo: static_assert size is power of 2
public:
    Oversampler() {}
    void add_val(T newval) {
        buff_ += newval;
        if (++idx_>=size) {
            val_ = buff_ >> oversample_shift_;
            idx_ = 0;
            buff_ = 0;
        }
    }
    T val() {return val_;}
private:
    constexpr static int oversample_shift_ = Log2Int(size);
    T buff_ = 0;
    T val_ = 0;
    int idx_ = 0;
};
