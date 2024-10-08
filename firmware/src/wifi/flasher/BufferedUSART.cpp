#include "BufferedUSART.h"

#include "conf/wifi_uart_conf.hh"
#include "drivers/uart.hh"
#include "drivers/uart_conf.hh"
#include "drivers/interrupt.hh"

#include <stm32mp1xx.h>
#include <stm32mp1xx_ll_usart.h>

#include <console/pr_dbg.hh>

static mdrivlib::Uart<WifiBootloaderUartConfig> commBoot;
LockFreeFifoSpsc<uint8_t,256> BufferedUSART::queue;

#define USART_PERIPH        USART6
#define USART_IRQ           USART6_IRQn
#define USART_IRQ_PRIO      3

void BufferedUSART::init()
{
    initPeripheral();
}

void BufferedUSART::deinit()
{
    LL_USART_DisableIT_RXNE_RXFNE(USART_PERIPH);
}

bool BufferedUSART::setBaudrate(uint32_t baudRate)
{
    return commBoot.set_baudrate(baudRate);
}

void BufferedUSART::initPeripheral()
{
    commBoot.init();

    mdrivlib::Interrupt::register_and_start_isr(USART_IRQ, USART_IRQ_PRIO, 0, []()
    {
        if (LL_USART_IsActiveFlag_RXNE_RXFNE(USART_PERIPH))
        {
            do
            {
                auto val = USART_PERIPH->RDR;

                auto result = queue.put(val);
                if (not result)
                {
                    pr_err("USART: RX Soft Overrun\n");
                }
            }
            while (LL_USART_IsActiveFlag_RXNE(USART_PERIPH));
        }
        else if (LL_USART_IsActiveFlag_ORE(USART_PERIPH))
		{
            pr_warn("USART1: FIFO Overrun\n");
			LL_USART_ClearFlag_ORE(USART_PERIPH);
		}
		else
		{
			pr_warn("USART1: ISR called with no flag\n");
			(void)USART_PERIPH->RDR;
		}
    });

    // read RX from hardware to clear RXNE flag
    (void)USART_PERIPH->RDR;

    LL_USART_EnableIT_RXNE_RXFNE(USART_PERIPH);    
}

void BufferedUSART::transmit(uint8_t val)
{
    commBoot.transmit(val);
}

std::optional<uint8_t> BufferedUSART::receive()
{
    return queue.get();
}


