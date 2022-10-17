#include "printf.h"
#include "utils.h"
#include "mini_uart.h"

void kernel_main_el2(void)
{
	uart_init();
	init_printf(0, putc);
	int el = get_el();
	printf("Exception level: %d \r\n", el);
}

void kernel_main_el1(void)
{
	int el = get_el();
	printf("Exception level: %d \r\n", el);

	float num = 1.2;
	num ++;
	printf("Floating Numbers work");

	while (1) {
		uart_send(uart_recv());
	}
}
