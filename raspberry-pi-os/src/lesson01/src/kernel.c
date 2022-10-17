#include "mini_uart.h"
#include "uart.h"

void kernel_main(void)
{
	uart_init();								// initialize mini_uart
	uart_send_string("Hello, world!\r\n");		// send string over mini_uart

	while (1) {
		uart_send(mini_uart_recv());					// stall program in loop
	}
}
