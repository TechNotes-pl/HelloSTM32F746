/*
 * system_clock.h
 *
 *  Created on: 19 cze 2020
 *      Author: Technotes-pl
 */

#ifndef SYSTEM_CLOCK_H_
#define SYSTEM_CLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void);

/**
  * @brief  This function is executed in case of error occurrence, 
  * custom report the HAL error return state.
  * @retval None
  */
void Error_Handler(void);


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line);

#endif /* USE_FULL_ASSERT */
#ifdef __cplusplus
}
#endif
#endif /* SYSTEM_CLOCK_H_ */
