#ifndef __TRIGGER_H__
#define __TRIGGER_H__

#include <stdbool.h>
#include <stm32f3xx_hal.h>

#define TRIGGER_PORT		GPIOA
#define TRIGGER_PIN 		GPIO_PIN_12
#define TRIGGER_CLK_ENABLE	__HAL_RCC_GPIOA_CLK_ENABLE

void trigger_init(void);
void trigger_set(bool state);
void tio3_set(bool state);
void tio2_set(bool state);
void toggle_pin();

#endif /* __TRIGGER_H__ */
