/*
 * FreeModbus Libary: STM32F746 Demo Application
 * Copyright (C) 2020 https://TechNotes.pl
 */
#include "main.h"
#include "mbedtls.h"
#include "gpio.h"
#include "system_clock.h"
#include "mb.h"
#include "mbport.h"
#include "modbus_registers.h"
#include "led.h"
#include "UserButton.h"

int ModbusInitialize(void);

// LED blink delay times
const int DelayTimeHigh = 1000;
const int DelayTimeLow = 100;
int delay_time = DelayTimeHigh;

int main(void) {
	// Reset of all peripherals, initializes the Flash interface and the Systick.
	HAL_Init();

	// Configure the system clock
	SystemClock_Config();

	// Initialize all configured peripherals
	MX_GPIO_Init();
	MX_MBEDTLS_Init();

	Led led;

	bool modbus_ready = ModbusInitialize();

	for (;;) {
		if (modbus_ready) {
			// Handle Modbus messages if any
			(void) eMBPoll();
			ModbusRegsRefresh();
		}

		// Led blink
		led.Toggle();
		HAL_Delay(delay_time);
	}
}

/**
  * User button press callback function: switch led blink time.
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	delay_time = (delay_time == DelayTimeLow) ? DelayTimeHigh : DelayTimeLow;
}


/**
 * Initialize RTU mode
 * Returns 0 if everything is OK
 */
int ModbusInitialize(void) {
	eMBErrorCode eStatus;

	const UCHAR slave_address = 0x0A;
	const UCHAR port = 0;
	const ULONG baud_rate = 38400;

	if ((eStatus = eMBInit(MB_RTU, slave_address, port, baud_rate, MB_PAR_EVEN))
			!= MB_ENOERR)
		return eStatus;

	// Enable the Modbus Protocol Stack.
	return eMBEnable();
}
