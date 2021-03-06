/*
 * UserButton.h
 * Example of GPIO configuration, do not use in production environment.
 *
 *  Created on: Jun 23, 2020
 *      Author: Technotes-pl
 */

#ifndef USERBUTTON_H_
#define USERBUTTON_H_

#if defined STM32F746xx
	#include "stm32f7xx_hal.h"
	#define USER_BUTTON_PIN     GPIO_PIN_11
#endif

class UserButton {
private:
	void Setup();

public:
	UserButton();

	inline bool IsPressed() {
		return HAL_GPIO_ReadPin(GPIOI, USER_BUTTON_PIN) == GPIO_PIN_SET;
	}

	inline bool IsNotPressed() {
		return HAL_GPIO_ReadPin(GPIOI, USER_BUTTON_PIN) == GPIO_PIN_RESET;
	}

};

#endif /* USERBUTTON_H_ */
