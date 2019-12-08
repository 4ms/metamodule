#pragma once

#include "pin.hh"
#include <tuple>

const uint8_t kNumDebugPins = 1;

struct Debug {
    // using namespace GPIOPin;
  static void set_0(bool value);

private:
    static inline PinL<GPIO::D, 2> pin0 {PinMode::OUTPUT, PinPull::NONE};
};

/*
template <int Z>
class SomePeriph {
public:
    SomePeriph() : a(Z) {}
    int a;
};

template <int Z, int Y>
class SomeOtherPeriph {
public:
    SomeOtherPeriph() : a(Z), b(Y) {
        //init Peripheral Z, channel Y
    }
    int a, b;
};


template <typename X>
auto constexpr create_SomePeriph(X x) {
    return SomePeriph<x()>();
}

template <typename X>
auto constexpr create_SomeOtherPeriph(X x) {
    return SomeOtherPeriph<std::get<0>(x()), std::get<1>(x())>();
}

void test2() {
  auto Channel1 = create_SomePeriph([] { return 1; });
  auto Channel2 = create_SomePeriph([] { return 2; });
  //
  auto OtherChannel3 = create_SomeOtherPeriph([] { return std::make_tuple(ADC2_BASE, 3); });
}
*/
