#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <stdbool.h>
#include "gpio.h"
#include "uart.h"

#define BUTTON_1_PIN GPIO_PIN_5
#define BUTTON_2_PIN GPIO_PIN_6
#define BUTTON_3_PIN GPIO_PIN_7

#define DEVICE_1_PIN GPIO_PIN_1
#define DEVICE_2_PIN GPIO_PIN_0
#define DEVICE_3_PIN GPIO_PIN_2

#define DEBOUND_TIME 75

uint8_t button1Check(void);
uint8_t button2Check(void);
uint8_t button3Check(void);
void deviceOn(uint8_t pDevicePin);
void deviceOff(uint8_t pDevicePin);
void deviceToggle(uint8_t pDevicePin);
uint8_t deviceGetStatus(uint8_t pDevicePin);


#endif
