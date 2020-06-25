/*
 * led.h
 * Example of GPIO configuration, do not use in production environment.
 *
 *  Created on: Jun 22, 2020
 *      Author: Technotes-pl
 */


#ifndef LED_H_
#define LED_H_

#if defined STM32F746xx
	#include "stm32f7xx_hal.h"
	#define USER_BUTTON_PIN     GPIO_PIN_11
#endif

class Led
{
	protected:
		void Setup(void);

	public:
		Led();
		virtual ~Led();
		void On(void);
		void Off(void);
		void Toggle(void);
};

#endif /* LED_H_ */
