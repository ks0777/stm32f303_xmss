#include "trigger.h"

void trigger_init(void)
{
	GPIO_InitTypeDef gpio_trigger = {0};

	TRIGGER_CLK_ENABLE();

	gpio_trigger.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_trigger.Pull = GPIO_NOPULL;
	gpio_trigger.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_trigger.Pin = TRIGGER_PIN;

	HAL_GPIO_Init(TRIGGER_PORT, &gpio_trigger);

	HAL_GPIO_WritePin(TRIGGER_PORT, TRIGGER_PIN, GPIO_PIN_RESET);

	gpio_trigger.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_trigger.Pull = GPIO_NOPULL;
	gpio_trigger.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_trigger.Pin = GPIO_PIN_11;

	HAL_GPIO_Init(TRIGGER_PORT, &gpio_trigger);

	HAL_GPIO_WritePin(TRIGGER_PORT, GPIO_PIN_11, GPIO_PIN_RESET);

	gpio_trigger.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_trigger.Pull = GPIO_NOPULL;
	gpio_trigger.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_trigger.Pin = GPIO_PIN_10;

	HAL_GPIO_Init(TRIGGER_PORT, &gpio_trigger);

	HAL_GPIO_WritePin(TRIGGER_PORT, GPIO_PIN_10, GPIO_PIN_RESET);
}

void trigger_set(bool state)
{
	HAL_GPIO_WritePin(TRIGGER_PORT, TRIGGER_PIN, state);
}

void tio3_set(bool state) {
	HAL_GPIO_WritePin(TRIGGER_PORT, GPIO_PIN_11, state);
}

void tio2_set(bool state) {
	HAL_GPIO_WritePin(TRIGGER_PORT, GPIO_PIN_10, state);
}

void toggle_pin()
{
	HAL_GPIO_TogglePin(TRIGGER_PORT, TRIGGER_PIN);
}
