# "pro" board config (STM32MP25x)

One header per peripheral, selected purely by include path (`src/pro` is on the
include path; generic code does `#include "conf/xxx_conf.hh"`) — the same
mechanism as `firmware/src/medium/conf/` on MP1. No `#ifdef`s.

Port each header from `firmware/src/medium/conf/` as its subsystem comes up in
bring-up, translating MP1 peripheral choices to MP2 (HPDMA channels/requests
instead of DMA streams, flexgen XBAR kernel clocks, LTDC instead of the SPI
screen). Pin assignments are TBD until the hardware pin list exists.

Present so far:

- `screen_buffer_conf.hh` — PROVISIONAL 720x480; drives GUI-layout work via the
  simulator's `--screenw/--screenh` preview before hardware exists
