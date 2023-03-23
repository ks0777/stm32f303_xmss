#include "trigger.h"

GPIO_TypeDef gpio_typedef;

void trigger_init(void)
{
	TRIGGER_CLK_ENABLE();

	GPIO_InitTypeDef gpio_trigger = {0};
	gpio_trigger.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_trigger.Pull = GPIO_NOPULL;
	gpio_trigger.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_trigger.Pin = TRIGGER_PIN;

	HAL_GPIO_Init(&gpio_typedef, &gpio_trigger);
}

void trigger_set(bool state)
{
	HAL_GPIO_WritePin(&gpio_typedef, TRIGGER_PIN, state);
}

void toggle_pin()
{
	HAL_GPIO_TogglePin(&gpio_typedef, TRIGGER_PIN);
}
