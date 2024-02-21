#include "esp_loader.h"
#include "esp_loader_io.h"
#include "custom_port.h"

#include "conf/wifi_uart_conf.hh"
#include "drivers/pin.hh"

#include "BufferedUSART.h"

#include <console/pr_dbg.hh>

#include <cstring>

//#define LOG_TRANSACTIONS

static mdrivlib::Pin resetPin;
static mdrivlib::Pin bootSelectPin;

extern "C"
{

static void serial_debug_print(const uint8_t* data, uint16_t size, bool write)
{
    #ifdef LOG_TRANSACTIONS
    if (write)
    {
        printf("WRITE ");
    }
    else
    {
        printf("Read ");
    }
    printf("Len %u\n", size);
    

    for (uint32_t i=0; i<size; i++)
    {
        printf("0x%02x ", data[i]);
    }
    printf("\n");
    #endif
}

static uint32_t s_time_end;

esp_loader_error_t loader_port_write(const uint8_t* data, uint16_t size, uint32_t timeout)
{
    serial_debug_print(data, size, true);

    for (uint32_t i=0; i<size; i++)
    {
        // TODO: we need to check timeout and error here
        BufferedUSART::transmit(data[i]);
    }

    return ESP_LOADER_SUCCESS;
}

esp_loader_error_t loader_port_read(uint8_t* data, uint16_t size, uint32_t timeout)
{
    std::memset(data, 0x22, size);

    for (uint32_t i=0; i<size; i++)
    {
        auto start = HAL_GetTick();
        while (true)
        {
            if (HAL_GetTick() - start < timeout)
            {
                auto thisData = BufferedUSART::receive();

                if (thisData)
                {
                    data[i] = *thisData;
                    break;
                }
            }
            else
            {
                return ESP_LOADER_ERROR_TIMEOUT;
            }
            
        }
    }

    serial_debug_print(data, size, false);

    return ESP_LOADER_SUCCESS;
}

void loader_port_init()
{
    BufferedUSART::init();

    resetPin.init(WifiBootloaderResetConfig, mdrivlib::PinMode::Output, mdrivlib::PinPull::Up);
    bootSelectPin.init(WifiBootloaderBootSelectConfig, mdrivlib::PinMode::Output, mdrivlib::PinPull::Up);
}

void loader_port_deinit()
{
    BufferedUSART::deinit();
    bootSelectPin.high();
}

// Set GPIO0 LOW, then
// assert reset pin for 100 milliseconds.
void loader_port_enter_bootloader(void)
{
    bootSelectPin.low();
    loader_port_reset_target();
    loader_port_delay_ms(SERIAL_FLASHER_BOOT_HOLD_TIME_MS);
    bootSelectPin.high();
}

void loader_port_reset_target(void)
{
    resetPin.low();
    loader_port_delay_ms(SERIAL_FLASHER_RESET_HOLD_TIME_MS);
    resetPin.high();
}

void loader_port_delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}

void loader_port_start_timer(uint32_t ms)
{
    s_time_end = HAL_GetTick() + ms;
}

uint32_t loader_port_remaining_time(void)
{
    auto now = HAL_GetTick();

    if (now < s_time_end)
    {
        return s_time_end - now;
    }
    else
    {
        return 0;
    }
}

void loader_port_debug_print(const char* str)
{
    pr_dbg("%s", str);
}

esp_loader_error_t loader_port_change_transmission_rate(uint32_t baudrate)
{
    // TODO: How can we dynamically set the baudrate on the uart periperhal?

    auto success = BufferedUSART::setBaudrate(baudrate);

    return success ? ESP_LOADER_SUCCESS : ESP_LOADER_ERROR_FAIL;
}
}