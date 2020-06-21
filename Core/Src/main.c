/*
 * FreeModbus Libary: STM32F746 Demo Application
 * Copyright (C) 2020 https://TechNotes.pl
 */

#include "system_clock.h"
#include "mb.h"
#include "mbport.h"
#include "modbus_registers.h"


#define LED_GREEN           GPIO_PIN_1


int main(void)
{
	// eMBErrorCode    eStatus;

  // Reset of all peripherals, initializes the Flash interface and the Systick.
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();


  __HAL_RCC_GPIOI_CLK_ENABLE();

  // Create GPIO port configuration structure for LED1, fields :
  // 	Pin=1, Mode=OUTPUT, Pool=NO, Speed=LOW, Alternate=NOT SET
  GPIO_InitTypeDef gpio_led1 = {LED_GREEN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 };
  // Initialize GPIOI
  HAL_GPIO_Init(GPIOI, &gpio_led1);



  for( ;; )
  {
    HAL_GPIO_TogglePin(GPIOI, LED_GREEN);
    HAL_Delay(1000);
  }
}

//  eStatus = eMBInit( MB_RTU, 0x0A, 0, 38400, MB_PAR_EVEN );

//  /* Enable the Modbus Protocol Stack. */
//  eStatus = eMBEnable(  );

//  for( ;; )
//  {
//      ( void )eMBPoll(  );

//      /* Here we simply count the number of poll cycles. */
//      usRegInputBuf[0]++;
//  }
//}

