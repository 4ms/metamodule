#pragma once

#include "esp_loader.h"

#include <cstdint>
#include <span>


namespace Flasher
{

esp_loader_error_t init(uint32_t baudrate);

esp_loader_error_t flash(uint32_t, std::span<uint8_t>);

}