#pragma once

#include <cstdint>
#include "util/lockfree_fifo_spsc.hh"


class BufferedUSART2
{
public:
    static void init();
    static void deinit();

    static bool setBaudrate(uint32_t);

    static void transmit(uint8_t);
    static std::optional<uint8_t> receive();

private:
    static void initPeripheral();

private:
    static LockFreeFifoSpsc<uint8_t,256> queue;
};