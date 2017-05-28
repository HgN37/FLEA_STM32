#ifndef __UART_H__
#define __UART_H__

#include "stm32f0xx_hal.h"

#define BUFFER_MAX 100
#define BUFFER_CURSOR 0

void uartBufferInit(void);
uint8_t uartBufferAvailable(void);
uint8_t uartRead(void);
void uartWrite(uint8_t* pData, uint8_t pLength);


#endif
