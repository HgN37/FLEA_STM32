#include "gpio.h"

void gpioWrite(uint8_t pPin, uint8_t pOutput)
{
	HAL_GPIO_WritePin(GPIOA, pPin, pOutput);
}

uint8_t gpioRead(uint8_t pPin)
{
	return HAL_GPIO_ReadPin(GPIOA, pPin);
}

