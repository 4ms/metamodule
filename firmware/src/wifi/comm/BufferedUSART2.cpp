#include "BufferedUSART2.h"

#include "conf/wifi_uart_conf.hh"
#include "drivers/uart.hh"
#include "drivers/uart_conf.hh"
#include "drivers/interrupt.hh"

#include <stm32mp1xx.h>
#include <stm32mp1xx_ll_usart.h>
#include <stm32mp1xx_ll_usart.h>

#include <console/pr_dbg.hh>

static mdrivlib::Uart<WifiUartConfig> commMain;
LockFreeFifoSpsc<uint8_t,256> BufferedUSART2::queue;
std::atomic_bool BufferedUSART2::overrunDetected;

#define USART_PERIPH        UART5
#define USART_IRQ           UART5_IRQn
#define USART_IRQ_PRIO      3

void BufferedUSART2::init()
{
    initPeripheral();
}

void BufferedUSART2::deinit()
{
    LL_USART_DisableIT_RXNE_RXFNE(USART_PERIPH);
}

bool BufferedUSART2::setBaudrate(uint32_t baudRate)
{
    return commMain.set_baudrate(baudRate);
}

void BufferedUSART2::initPeripheral()
{
    commMain.init();

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
                    queue.reset();
                    pr_warn("USART2: RX Soft Overrun\n");
                    overrunDetected = true;
                    break;
                }
            }
            while (LL_USART_IsActiveFlag_RXNE(USART_PERIPH));
        }
        else if (LL_USART_IsActiveFlag_ORE(USART_PERIPH))
		{
            queue.reset();
            overrunDetected = true;
            pr_warn("USART2: FIFO Overrun\n");
			LL_USART_ClearFlag_ORE(USART_PERIPH);
		}
		else
		{
			pr_warn("USART2: ISR called with no flag\n");
			(void)USART_PERIPH->RDR;
		}
    });

    // read RX from hardware to clear RXNE flag
    (void)USART_PERIPH->RDR;

    LL_USART_EnableIT_RXNE_RXFNE(USART_PERIPH);    
}

void BufferedUSART2::transmit(uint8_t val)
{
    commMain.transmit(val);
}

std::optional<uint8_t> BufferedUSART2::receive()
{
    return queue.get();
}


