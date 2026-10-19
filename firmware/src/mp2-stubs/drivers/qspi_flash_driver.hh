#pragma once
// MP2 version of mdrivlib's drivers/qspi_flash_driver.hh (MP1's QUADSPI driver):
// the NOR flash is on an OCTOSPI, with mdrivlib's OSpiFlash driver, which has the same API.
// Found first because src/mp2-stubs is first in the include path.
#include "drivers/ospi_flash_driver.hh"

namespace mdrivlib
{
using QSpiFlash = OSpiFlash;
}
