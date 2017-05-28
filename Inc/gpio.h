#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f0xx_hal.h"

#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET

inline void gpioWrite(uint8_t pPin, uint8_t pOutput);
inline uint8_t gpioRead(uint8_t pPin);

#endif
