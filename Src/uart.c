#include "uart.h"

extern UART_HandleTypeDef huart1;
uint8_t uartBuffer[BUFFER_MAX];
uint8_t uartBufferWritePointer = 0x01;
uint8_t uartBufferReadPointer = 0x00;
uint8_t uartBufferOverflow = 0;

void uartBufferInit()
{
	uint8_t index;
	for(index = 0; index < BUFFER_MAX; index++)
	{
		uartBuffer[index] = 0;
	}
	HAL_UART_Receive_IT(&huart1, &uartBuffer[uartBufferWritePointer], 1);
}

uint8_t uartBufferAvailable()
{
	uint8_t result;
	if (uartBufferWritePointer > uartBufferReadPointer)
	{
		result = uartBufferWritePointer - uartBufferReadPointer - 1;
	}
	else
	{
		result = BUFFER_MAX + uartBufferWritePointer - uartBufferReadPointer - 1;
	}
	return result;
}


uint8_t uartRead()
{
	uint8_t temp;
	temp = uartBufferReadPointer + 1;
	if(temp == BUFFER_MAX)
	{
		temp = 0;
	}
	if(temp != uartBufferWritePointer)
	{
		uartBufferReadPointer = temp;
	}
	return uartBuffer[uartBufferReadPointer];
}

void uartWrite(uint8_t* pData, uint8_t pLength)
{
	HAL_UART_Transmit(&huart1, pData, pLength, 1000);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == huart1.Instance)
	{
		if(uartBufferWritePointer != uartBufferReadPointer) //Not full yet
		{
			uartBufferWritePointer++;
			if (uartBufferWritePointer == BUFFER_MAX)
			{
				uartBufferWritePointer = 0;
			}
			HAL_UART_Receive_IT(huart, &uartBuffer[uartBufferWritePointer], 1);
		}
		else
		{
			HAL_UART_Receive_IT(huart, &uartBufferOverflow, 1);
		}
	}
}
