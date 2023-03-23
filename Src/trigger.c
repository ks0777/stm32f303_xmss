#include "trigger.h"

void trigger_init(void)
{
	GPIO_InitTypeDef gpio_trigger = {0};

	TRIGGER_CLK_ENABLE();

	HAL_GPIO_WritePin(TRIGGER_PORT, TRIGGER_PIN, GPIO_PIN_RESET);

	gpio_trigger.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_trigger.Pull = GPIO_NOPULL;
	gpio_trigger.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_trigger.Pin = TRIGGER_PIN;

	HAL_GPIO_Init(TRIGGER_PORT, &gpio_trigger);
}

void trigger_set(bool state)
{
	HAL_GPIO_WritePin(TRIGGER_PORT, TRIGGER_PIN, state);
}

void toggle_pin()
{
	HAL_GPIO_TogglePin(TRIGGER_PORT, TRIGGER_PIN);
}
