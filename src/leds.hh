#pragma once
#include <stm32f7xx.h>

struct Color {
    struct Adjustment {
        uint8_t r, g, b;
    };

    explicit constexpr Color(uint8_t r, uint8_t g, uint8_t b) : r_(r), g_(g), b_(b) {}

    uint8_t red() { return r_; }
    uint8_t green() { return g_; }
    uint8_t blue() { return b_; }

    constexpr const Color operator+(Color const that) const {
        return Color(__UQADD8(r_, that.r_),
                    __UQADD8(g_, that.g_),
                    __UQADD8(b_, that.b_));
    }

    constexpr Color blend(Color const that) const {
        return Color((r_>>1) + (that.r_>>1),
                     (g_>>1) + (that.g_>>1),
                     (b_>>1) + (that.b_>>1));
    }

    constexpr const Color blend(Color const that, uint8_t const phase) const {
        return Color(Signal::crossfade(r_, that.r_, phase),
                    Signal::crossfade(g_, that.g_, phase),
                    Signal::crossfade(b_, that.b_, phase));
    }

    constexpr const bool operator!=(Color const that) {
        return this->r_ != that.r_ || this->g_ != that.g_ || this->b_ != that.b_;
    }

    constexpr const Color adjust(Adjustment const adj) const {
        uint16_t ra = r_ * adj.r;
        uint16_t rg = g_ * adj.g;
        uint16_t rb = b_ * adj.b;

        return Color(ra >> 7,
                     rg >> 7,
                     rb >> 7);
    } 

private:
    uint8_t r_, g_, b_;
};


class Led {

};
