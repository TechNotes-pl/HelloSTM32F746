/*
 * UserButton.cpp
 *
 *  Created on: Jun 23, 2020
 *      Author: Technotes-pl
 */

#include "UserButton.h"

//namespace Technotes {

UserButton::UserButton() {
	Setup();
}

void UserButton::Setup() {
	// Connect clock to activate port I
	__HAL_RCC_GPIOI_CLK_ENABLE();

	// GPIO configuration for user button
	GPIO_InitTypeDef gpio = { USER_BUTTON_PIN, GPIO_MODE_INPUT, GPIO_PULLUP,
			GPIO_SPEED_FREQ_LOW, 0 };
	HAL_GPIO_Init(GPIOI, &gpio);
}

//} /* namespace Technotes */
