/*
 * FreeModbus Libary: STM32F746 Demo Application
 * Copyright (C) 2020 https://TechNotes.pl
 */
#include "led.h"
#include "system_clock.h"
#include "mb.h"
#include "mbport.h"
#include "modbus_registers.h"
#include "UserButton.h"

int ModbusInitialize(void);

int main(void) {
	// Reset of all peripherals, initializes the Flash interface and the Systick.
	HAL_Init();

	// Configure the system clock
	SystemClock_Config();

	Led led;
	UserButton btn;

	const int DelayTimeHigh = 1000;
	const int DelayTimeLow = 100;
	int delay_time = DelayTimeHigh;

	bool modbus_ready = ModbusInitialize();

	for (;;) {
		if (modbus_ready) {
			// Handle Modbus messages if any
			(void) eMBPoll();
			ModbusRegsRefresh();
		}

		// Switch delay time to short or long if user button pressed.
		if (btn.IsPressed()) {
			delay_time =
					(delay_time == DelayTimeLow) ? DelayTimeHigh : DelayTimeLow;
		}

		led.Toggle();
		HAL_Delay(delay_time);
	}
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
