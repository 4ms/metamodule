#pragma once
#include <cstdint>

// The console UART, shared with the M33. printf() etc. write to it (see _write() in console.cc).
namespace MetaModule::A35Console
{

void init();

// Once the HSEM is initialized: lock the UART semaphore while writing, since the M33 also writes
// to the console
void use_hsem_lock();

void write(const char *str);

// Reads a received character, if there is one
bool receive(uint8_t &c);

// Whether core 0 writes to its console buffer (UartLog::use_buffer()), which it does once the M33,
// which sends the buffers on, is running
bool core0_buffered();

} // namespace MetaModule::A35Console
