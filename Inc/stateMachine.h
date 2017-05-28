#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#include <stdbool.h>
#include "hardware.h"

#define STATE_IDLE 0x00
#define STATE_UART 0x01
#define STATE_BUTTON 0x02

#define FUNCTION_DIM 0x01
#define FUNCTION_STATUS 0x11

#define DEVICE_NONE 0xFF
#define DEVICE_1 0x01
#define DEVICE_2 0x02
#define DEVICE_3 0x03

#define BUTTON_STATUS_NONE 0x00
#define BUTTON_STATUS_1 0x01
#define BUTTON_STATUS_2 0x02
#define BUTTON_STATUS_3 0x03

void stateUpdate(void);
void stateMachine(void);


#endif
