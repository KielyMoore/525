#ifndef _P_UART_H
#define _P_UART_H

#include "peripherals/base.h"

#define UBASE (PBASE+0x00201000)

#define UART_DR     (UBASE+0x00)
#define UART_FR     (UBASE+0x18)
#define UART_IBRD   (UBASE+0x24)
#define UART_FBRD   (UBASE+0x28)
#define UART_LCRH   (UBASE+0x2C)
#define UART_CR     (UBASE+0x30)
#define UART_IFLS   (UBASE+0x34)
#define UART_IMSC   (UBASE+0x38)
#define UART_RIS    (UBASE+0x3C)
#define UART_MIS    (UBASE+0x40)
#define UART_ICR    (UBASE+0x44)
#define UART_DMACR  (UBASE+0x48)
#define UART_ITCR   (UBASE+0x80)
#define UART_ITIP   (UBASE+0x84)
#define UART_ITOP   (UBASE+0x88)
#define UART_TDR    (UBASE+0x8C)

#endif /* _P_UART_H */