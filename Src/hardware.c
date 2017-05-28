#include "hardware.h"

uint8_t deviceStatus = 0x00;


uint8_t button1Check()
{
	uint8_t buttonStatus = 0x01;
	static uint8_t buttonState = HIGH;
	static uint8_t buttonLastState = HIGH;
	uint32_t lastDeboundTime;
	uint32_t delayDebound = DEBOUND_TIME;
	uint8_t reading = gpioRead(BUTTON_1_PIN);
	if (reading != buttonLastState)
	{
		lastDeboundTime = HAL_GetTick();
	}
	if ((HAL_GetTick() - lastDeboundTime) > delayDebound)
	{
		if(reading != buttonState)
		{
			buttonState = reading;
			if (buttonState == LOW)
			{
				buttonStatus = 0x00;
			}
		}
	}
	buttonLastState = reading;
	return buttonStatus;
}

uint8_t button2Check()
{
	uint8_t buttonStatus = 0x01;
	static uint8_t buttonState = HIGH;
	static uint8_t buttonLastState = HIGH;
	uint32_t lastDeboundTime;
	uint32_t delayDebound = DEBOUND_TIME;
	uint8_t reading = gpioRead(BUTTON_2_PIN);
	if (reading != buttonLastState)
	{
		lastDeboundTime = HAL_GetTick();
	}
	if ((HAL_GetTick() - lastDeboundTime) > delayDebound)
	{
		if(reading != buttonState)
		{
			buttonState = reading;
			if (buttonState == LOW)
			{
				buttonStatus = 0x00;
			}
		}
	}
	buttonLastState = reading;
	return buttonStatus;
}

uint8_t button3Check()
{
	uint8_t buttonStatus = 0x01;
	static uint8_t buttonState = HIGH;
	static uint8_t buttonLastState = HIGH;
	uint32_t lastDeboundTime;
	uint32_t delayDebound = DEBOUND_TIME;
	uint8_t reading = gpioRead(BUTTON_3_PIN);
	if (reading != buttonLastState)
	{
		lastDeboundTime = HAL_GetTick();
	}
	if ((HAL_GetTick() - lastDeboundTime) > delayDebound)
	{
		if(reading != buttonState)
		{
			buttonState = reading;
			if (buttonState == LOW)
			{
				buttonStatus = 0x00;
			}
		}
	}
	buttonLastState = reading;
	return buttonStatus;
}

void deviceOn(uint8_t pDevicePin)
{
	gpioWrite(pDevicePin, HIGH);
	deviceStatus |= pDevicePin;
}

void deviceOff(uint8_t pDevicePin)
{
	gpioWrite(pDevicePin, LOW);
	deviceStatus &= (~pDevicePin);
}

void deviceToggle(uint8_t pDevicePin)
{
	HAL_GPIO_TogglePin(GPIOA, pDevicePin);
	deviceStatus ^= pDevicePin;
}

uint8_t deviceGetStatus(uint8_t pDevicePin)
{
	if ((deviceStatus & pDevicePin) == pDevicePin)
		return 100;
	else
		return 0;
}
