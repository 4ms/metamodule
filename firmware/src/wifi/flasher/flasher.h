#pragma once

#include "esp_loader.h"

#include <cstdint>
#include <span>
#include <string_view>

namespace Flasher
{

esp_loader_error_t init(uint32_t baudrate);
void deinit();
void reboot();

esp_loader_error_t flash(uint32_t address, std::span<const uint8_t>);
esp_loader_error_t verify(uint32_t address, uint32_t length, std::string_view);
esp_loader_error_t conditional_flash(uint32_t address, std::span<const uint8_t>, std::string_view);

esp_loader_error_t flash_start(uint32_t address, uint32_t length, uint32_t batchSize);
esp_loader_error_t flash_process(std::span<uint8_t>);

} // namespace Flasher
