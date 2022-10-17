#ifndef	_P_MINI_UART_H
#define	_P_MINI_UART_H

#include "peripherals/base.h"

#define AUX_ENABLES     (PBASE+0x00215004) //Auxilary enables
#define AUX_MU_IO_REG   (PBASE+0x00215040) //Mini Uart I/O Data
#define AUX_MU_IER_REG  (PBASE+0x00215044) //Mini Uart Interrupt Enable
#define AUX_MU_IIR_REG  (PBASE+0x00215048) //Mini Uart Interrupt Identify
#define AUX_MU_LCR_REG  (PBASE+0x0021504C) //Mini Uart Line Control
#define AUX_MU_MCR_REG  (PBASE+0x00215050) //Mini Uart Modem Control
#define AUX_MU_LSR_REG  (PBASE+0x00215054) //Mini Uart Line Status
#define AUX_MU_MSR_REG  (PBASE+0x00215058) //Mini Uart Modem Status
#define AUX_MU_SCRATCH  (PBASE+0x0021505C) //Mini Uart Scratch
#define AUX_MU_CNTL_REG (PBASE+0x00215060) //Mini Uart Extra Control
#define AUX_MU_STAT_REG (PBASE+0x00215064) //Mini Uart Extra Status
#define AUX_MU_BAUD_REG (PBASE+0x00215068) //Mini Uart Baudrate

#endif  /*_P_MINI_UART_H */
