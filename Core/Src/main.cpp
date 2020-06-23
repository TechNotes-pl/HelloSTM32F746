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

int main(void)
{
  // Reset of all peripherals, initializes the Flash interface and the Systick.
  HAL_Init();

  // Configure the system clock
  SystemClock_Config();

  Led led;
  UserButton btn;

  const int DelayTimeHigh = 2000;
  const int DelayTimeLow = 50;
  int delay_time = DelayTimeHigh;

/*
  eStatus = eMBInit( MB_RTU, 0x0A, 0, 38400, MB_PAR_EVEN );

  // Enable the Modbus Protocol Stack.
  eStatus = eMBEnable(  );
*/
  for( ;; )
  {
/*
	  ( void )eMBPoll(  );

	 // Here we simply count the number of poll cycles.
	 usRegInputBuf[0]++;
*/

    if (btn.IsPressed())
      delay_time = (delay_time == DelayTimeLow) ? DelayTimeHigh : DelayTimeLow;

    led.Toggle();
    HAL_Delay(delay_time);
  }
}
