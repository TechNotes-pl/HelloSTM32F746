/*
 * led.cpp
 * Example of GPIO configuration, do not use in production environment.
 *
 *  Created on: Jun 22, 2020
 *      Author: Technotes-pl
 */

#include <led.h>

const uint32_t pin_number = GPIO_PIN_1;

Led::Led() {
	Setup();
}

Led::~Led() {
}

void Led::On(void) {
	HAL_GPIO_WritePin(GPIOI, pin_number, GPIO_PIN_SET);
}

void Led::Off(void) {
	HAL_GPIO_WritePin(GPIOI, pin_number, GPIO_PIN_RESET);
}

void Led::Toggle(void) {
	HAL_GPIO_TogglePin(GPIOI, pin_number);
}

void Led::Setup(void) {
	// Connect clock to activate port I
	__HAL_RCC_GPIOI_CLK_ENABLE();

	// Create GPIO port configuration structure for LED1, fields :
	// 	                      Pin=1,      Mode=OUTPUT,         Pool=NO,     Speed=LOW,           Alternate=NOT SET
	GPIO_InitTypeDef gpio = { pin_number, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 };

	// Initialize GPIOI - put data to MCU registers
	HAL_GPIO_Init(GPIOI, &gpio);

	Off();
}
