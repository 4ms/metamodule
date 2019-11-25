#include <stm32f7xx.h>

constexpr uint32_t Log2Int(uint32_t x) {
    return 
    x==(1UL<<16) ? 16 :
    x==(1UL<<15) ? 15 :
    x==16384 ? 14 :
    x==8192 ? 13 :
    x==4096 ? 12 :
    x==2048 ? 11 :
    x==1024 ? 10 :
    x==512 ? 9 :
    x==256 ? 8 :
    x==128 ? 7 :
    x==64 ? 6 :
    x==32 ? 5 :
    x==16 ? 4 :
    x==8 ? 3 :
    x==4 ? 2 :
    x==2 ? 1 :
    x==1 ? 0 : 0;
}

template<class T, int size>
struct Oversampler {
//Todo: static_assert size is power of 2
public:
    Oversampler() {}
    void add_val(T newval) {
        buff_ += newval;
        if (++idx_>size) {
            idx_ = 0;
            val_ = buff_ >> oversample_shift_;
        }
    }
    T val() {return val_;}
private:
    constexpr static int oversample_shift_ = Log2Int(size);
    T buff_ = 0;
    T val_ = 0;
    int idx_ = 0;
};
