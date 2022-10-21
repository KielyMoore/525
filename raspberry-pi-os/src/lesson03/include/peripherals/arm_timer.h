#ifndef _P_ARM_TIMER_H
#define _P_ARM_TIMER_H

#include "peripherals/base.h"

#define TBASE (PBASE+0x0000B000)

//******************************************************************************
// Timer (ARM side) described in pg 196 of the BCM2835 ARM Peripherals Manual
//******************************************************************************

#define ARM_TIMER_LOAD      (TBASE+0x400)
#define ARM_TIMER_VALUE     (TBASE+0x404)
#define ARM_TIMER_CONTROL   (TBASE+0x408)
#define ARM_TIMER_IRQ_CA    (TBASE+0x40C)
#define ARM_TIMER_RAW_IRQ   (TBASE+0x410)
#define ARM_TIMER_MASK_IRQ  (TBASE+0x414)
#define ARM_TIMER_RELOAD    (TBASE+0x418)


#define ATCTRL_32BIT        (1 << 1)
#define ATCTRL_IR_EN        (1 << 5)
#define ATCTRL_ENABLE       (1 << 7)
#define ARM_TIMER_CTRL_VAL  (ATCTRL_32BIT | ATCTRL_IR_EN | ATCTRL_ENABLE)

#endif