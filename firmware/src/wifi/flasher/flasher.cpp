#include "flasher.h"

#include "custom_port.h"
#include "esp_loader.h"
#include "esp_loader_io.h"
#include "drivers/stm32xx.h"

#include <console/pr_dbg.hh>

#include <cstring>
#include <string_view>
#include <span>
#include <optional>

namespace Flasher
{

esp_loader_error_t init(uint32_t baudrate)
{
    loader_port_init();

    esp_loader_connect_args_t connect_config = ESP_LOADER_CONNECT_DEFAULT();

    esp_loader_error_t err = esp_loader_connect(&connect_config);
    if (err != ESP_LOADER_SUCCESS)
    {
        pr_err("Flasher: Cannot connect to target. Error: %u\n", err);
    }
    else
    {
        pr_trace("Flasher: Connected to target\n");

        err = esp_loader_change_transmission_rate(baudrate);
        if (err == ESP_LOADER_ERROR_UNSUPPORTED_FUNC)
        {
            pr_err("Flasher: ESP does not support change transmission rate command.\n");
        }
        else if (err != ESP_LOADER_SUCCESS)
        {
            pr_err("Flasher: Unable to change transmission rate on target.\n");
        }
        else
        {
            err = loader_port_change_transmission_rate(baudrate);
            if (err != ESP_LOADER_SUCCESS)
            {
                pr_err("Flasher: Unable to change transmission rate.\n");
            }
            else
            {
                pr_trace("Flasher: Transmission rate changed\n");
            }
        }
    }

    return err;
}

void deinit()
{
    loader_port_deinit();
}

void reboot()
{
    esp_loader_reset_target();
}

esp_loader_error_t flash(uint32_t address, std::span<const uint8_t> buffer)
{
    esp_loader_error_t err;

    const std::size_t BatchSize = 1024;
    std::array<uint8_t, BatchSize> BatchBuffer;

    pr_dbg("Flasher: Erasing flash (this may take a while)...\n");
    err = esp_loader_flash_start(address, buffer.size(), BatchBuffer.size());

    if (err != ESP_LOADER_SUCCESS)
    {
        pr_err("Flasher: Erasing flash failed with error %d\n", err);
        return err;
    }
    pr_dbg("Flasher: Start programming %08x - %08x\n", address, address + buffer.size());

    const uint8_t* bin_addr = buffer.data();
    const std::size_t binary_size = buffer.size();
    size_t written = 0;

    std::optional<int> lastPrintedProgress;

    while (written < binary_size)
    {
        size_t to_read = std::min(binary_size - written, BatchBuffer.size());
        std::memcpy(BatchBuffer.data(), bin_addr, to_read);

        err = esp_loader_flash_write(BatchBuffer.data(), to_read);
        if (err != ESP_LOADER_SUCCESS)
        {
            pr_err("Packet could not be written! Error %d\n", err);
            return err;
        }

        bin_addr += to_read;
        written += to_read;

        int progress = (int)(((float)written / float(binary_size)) * 100);

        if (not lastPrintedProgress or lastPrintedProgress != progress)
        {
            pr_dbg("Flasher: Progress: %d %%\n", progress);
            lastPrintedProgress = progress;
        }        
    };

    pr_dbg("Flasher: Finished programming\n");

    return ESP_LOADER_SUCCESS;
}

esp_loader_error_t verify(uint32_t address, uint32_t length, std::string_view checksum)
{
	HAL_Delay(10);
    pr_trace("Flasher: Getting checksum from %08x-%08x\n", address, address + length);

    std::array<uint8_t,32> readValue;

    auto result = esp_loader_get_md5_hex(address, length, readValue.data());

    if (result == ESP_LOADER_SUCCESS)
    {
        if (std::memcmp(checksum.data(), readValue.data(), checksum.size()) == 0)
        {
            return ESP_LOADER_SUCCESS;
        }
        else
        {
            pr_err("Flasher: Mismatch: Expected %.*s vs Read %.*s\n", checksum.size(), checksum.data(), readValue.size(), readValue.data());
            return ESP_LOADER_ERROR_INVALID_MD5;
        }
    }
    else
    {
        pr_err("Flasher: Failed to get checksum: %u\n", result);
    }

    return result;
}

esp_loader_error_t conditional_flash(uint32_t address, std::span<const uint8_t> payload, std::string_view checksum)
{
    pr_dbg("Flasher: Conditionally flash %p-%p with checksum %.*s to %p\n", &payload.front(), &payload.back(), checksum.size(), checksum.data(), address);

    auto result = verify(address, payload.size(), checksum);

    if (result == ESP_LOADER_SUCCESS)
    {
        pr_dbg("Flasher: Checksum already matches\n");
        return ESP_LOADER_SUCCESS;
    }
    else if (result == ESP_LOADER_ERROR_INVALID_MD5)
    {
        result = flash(address, payload);

        if (result == ESP_LOADER_SUCCESS)
        {
            pr_dbg("Flasher: Payload flashed successfully\n");
            return ESP_LOADER_SUCCESS;
        }
        else
        {
            pr_err("Flasher: Flashing failed with result: %u\n", result);
        }
    }
    else
    {
        pr_err("Flasher: Failed to read checksum of destination area\n");
    }

    return result;
}

esp_loader_error_t flash_start(uint32_t address, uint32_t length, uint32_t batchSize, std::optional<std::size_t> uncompressed_size)
{
    if (not uncompressed_size)
    {
        return esp_loader_flash_start(address, length, batchSize);
    }
    else
    {
        return esp_loader_flash_defl_start(address, *uncompressed_size, length, batchSize);
    }
}

esp_loader_error_t flash_process(std::span<uint8_t> buffer, bool compressed)
{
    if (not compressed)
    {
        return esp_loader_flash_write(buffer.data(), buffer.size());
    }
    else
    {
        return esp_loader_flash_defl_write(buffer.data(), buffer.size());
    }
}

esp_loader_error_t flash_finish(bool compressed)
{
    if (not compressed)
    {
        return esp_loader_flash_finish(false);
    }
    else
    {
        printf("Finishing defl flash\n");
        return esp_loader_flash_defl_finish(false);
    }
}

}
