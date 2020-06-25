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
#include "rtc.h"
#include "tim.h"

int ModbusInitialize(void);

int main(void) {
	// Reset of all peripherals, initializes the Flash interface and the Systick.
	HAL_Init();

	// Configure the system clock
	SystemClock_Config();

	// Initialize all configured peripherals
	MX_GPIO_Init();
	MX_MBEDTLS_Init();
	MX_RTC_Init();
	MX_TIM7_Init();
	HAL_TIM_Base_Start_IT(&htim7);

	// Handle Modbus messages if any
	bool modbus_ready = ModbusInitialize();
	for (;;) {
		if (modbus_ready) {
			(void) eMBPoll();
			ModbusRegsRefresh();
		}
	}
}


/**
 * Timer period is the combination of the PCS (prescaller) and ARR (auto reload register).
 * The period is calculated as (ARR + 1) * (PSC + 1) / TimerClockFreq.
 *
 * When you try to change the period when the timer is running you need to make sure
 * that it is done in the safe moment to prevent glitches. The safest moment is then the UG event happens.
 *
 * You have to ways of archiving it:
 *
 *      UG interrupt. In the interrupt routine if the ARR or PSC have changed - you should update the register.
 *      Bare in mind that the change may happen in the next cycle if the registers are shadowed.
 *
 *      Using the timers DMA burst more. It is more complicated to config -
 *      but the hardware take care of the registers update on the selected event.
 *      The change is instant and register shadowing does not affect it.
 *      More details read RM chapter about the timers DMA burst mode.
 *
 * At the moment we can use custom MX_TIM7_Init(void) function.
 */
void MY_MX_TIM7_Switch(uint32_t t1, uint32_t t2)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim7.Instance = TIM7;
  htim7.Init.Prescaler = (htim7.Init.Prescaler == t1) ? t2 : t1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 15999;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * User button press callback function: switch led blink time.
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	MY_MX_TIM7_Switch(999, 99);
}

/**
  * Timer7 callback function: switch led on or off.
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);
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
