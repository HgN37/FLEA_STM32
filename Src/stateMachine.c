#include "stateMachine.h"

static uint8_t gState = STATE_IDLE;
uint8_t gButtonStatus = BUTTON_STATUS_NONE;

uint8_t frameReceiveBuffer[12];
uint8_t frameTransmitBuffer[13] = {'*',0,0,0,0,0,0,0,0,0,0,0,'#'};

/* Private Functions */
bool cmdGet(void);
void cmdDo(void);
void cmdDoDim(void);
void cmdDoStatus(void);
void cmdFrameClear(void);
void stateUART(void);
void stateButton(void);
void stateIdle(void);

void stateUpdate()
{
	if(uartBufferAvailable()!=0)
	{
		if (uartRead() == '*')
		{
			frameReceiveBuffer[0] = '*'; 
			gState = STATE_UART;
		}
	}
	else if (button1Check() == 0x00)
	{
		gState = STATE_BUTTON;
		gButtonStatus = BUTTON_STATUS_1;
	}
	else if (button2Check() == 0x00)
	{
		gState = STATE_BUTTON;
		gButtonStatus = BUTTON_STATUS_2;
	}
	else if (button3Check() == 0x00)
	{
		gState = STATE_BUTTON;
		gButtonStatus = BUTTON_STATUS_3;
	}
}

void stateMachine()
{
	switch(gState)
	{
		case STATE_UART:
			stateUART();
		break;
		case STATE_BUTTON:
			stateButton();
		break;
		case STATE_IDLE:
			stateIdle();
		break;
		default:
		break;
	}
}

void stateUART()
{
	bool isCmdOK;
	isCmdOK = cmdGet();
	if (isCmdOK == true)
	{
		cmdDo();
	}
	cmdFrameClear();
	gState = STATE_IDLE;
}

void stateButton()
{
	uint8_t devicePin;
	switch(gButtonStatus)
	{
		case BUTTON_STATUS_1:
			devicePin = DEVICE_1_PIN;
		break;
		case BUTTON_STATUS_2:
			devicePin = DEVICE_2_PIN;
		break;
		case BUTTON_STATUS_3:
			devicePin = DEVICE_3_PIN;
		break;
		default:
		break;
	}
	deviceToggle(devicePin);
	gButtonStatus = BUTTON_STATUS_NONE;
	gState = STATE_IDLE;
}

void stateIdle()
{
	// Do nothing
}

bool cmdGet()
{
	bool isCmdOK = false;
	bool frameGetDone = false;
	uint32_t frameTimeOut = 0x0000;
	uint8_t index = 1;
	while (frameGetDone == false)
	{
		if(uartBufferAvailable() != 0)
		{
			frameReceiveBuffer[index] = uartRead();
			index++;
		}
		if(index > 11) // framReceiveBuffer full but no '#' found
		{
			frameGetDone = true;
		}
		else if(frameTimeOut > 0xFFFFF) // Time out
		{
			frameGetDone = true;
		}
		else
		{
			frameTimeOut++;
		}
	} //TODO: Kiem tra lai viec doc frame
	if (frameReceiveBuffer[11] == '#')
	{
		isCmdOK = true;
	}
	return isCmdOK;
}

void cmdDo()
{
	uint8_t function = frameReceiveBuffer[1];
	switch(function)
	{
		case FUNCTION_DIM:
			cmdDoDim();
		break;
		case FUNCTION_STATUS:
			cmdDoStatus();
		break;
		default:
		break;
	}
}

void cmdDoDim()
{
	uint8_t level = frameReceiveBuffer[10];
	uint8_t device = frameReceiveBuffer[2];
	uint8_t devicePin;
	switch(device)
	{
		case DEVICE_1:
			devicePin = DEVICE_1_PIN;
		break;
		case DEVICE_2:
			devicePin = DEVICE_2_PIN;
		break;
		case DEVICE_3:
			devicePin = DEVICE_3_PIN;
		break;
		default:
			devicePin = DEVICE_NONE;
		break;
	}
	if (devicePin != DEVICE_NONE)
	{
		if (level > 50)
		{
			deviceOn(devicePin);
		}
		else
		{
			deviceOff(devicePin);
		}
	}
	cmdDoStatus();
}

void cmdDoStatus()
{
	frameTransmitBuffer[0] = '*';
	frameTransmitBuffer[1] = FUNCTION_STATUS;
	frameTransmitBuffer[2] = DEVICE_1;
	frameTransmitBuffer[3] = 0x01;
	frameTransmitBuffer[11] = deviceGetStatus(DEVICE_1_PIN);
	frameTransmitBuffer[12] = '#';
	uartWrite(frameTransmitBuffer, 13);
	frameTransmitBuffer[0] = '*';
	frameTransmitBuffer[1] = FUNCTION_STATUS;
	frameTransmitBuffer[2] = DEVICE_2;
	frameTransmitBuffer[3] = 0x01;
	frameTransmitBuffer[11] = deviceGetStatus(DEVICE_2_PIN);
	frameTransmitBuffer[12] = '#';
	uartWrite(frameTransmitBuffer, 13);
	frameTransmitBuffer[0] = '*';
	frameTransmitBuffer[1] = FUNCTION_STATUS;
	frameTransmitBuffer[2] = DEVICE_3;
	frameTransmitBuffer[3] = 0x01;
	frameTransmitBuffer[11] = deviceGetStatus(DEVICE_3_PIN);
	frameTransmitBuffer[12] = '#';
	HAL_Delay(2);
	uartWrite(frameTransmitBuffer, 13);
}

void cmdFrameClear()
{
	uint8_t loop;
	for (loop = 0; loop < 12; loop++)
	{
		frameReceiveBuffer[loop] = 0;
	}
	for (loop = 0; loop < 13; loop++)
	{
		frameTransmitBuffer[loop] = 0;
	}
}
