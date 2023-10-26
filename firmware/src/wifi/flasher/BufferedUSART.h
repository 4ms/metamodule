#pragma once

#include <cstdint>
#include <spsc/queue.hpp>
using namespace lockfree::spsc;



class BufferedUSART
{
public:
    static void init();

    static bool setBaudrate(uint32_t);

    static void transmit(uint8_t);
    static std::optional<uint8_t> receive();

private:
    static void initPeripheral();

private:
    static Queue<uint8_t,256> queue;
};