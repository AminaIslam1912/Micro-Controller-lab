#include "stm32f4xx.h"
#include "GPIO.h"

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state) {
    if (state)
        GPIOx->ODR |= pin;
    else
        GPIOx->ODR &= ~pin;
}
