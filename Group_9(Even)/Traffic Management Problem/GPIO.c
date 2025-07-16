#include "stm32f4xx.h"
#include "GPIO.h"

/*void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state) {
    if (state)
        GPIOx->ODR |= pin;
    else
        GPIOx->ODR &= ~pin;
}
*/

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state) {
    if (state)
        GPIOx->BSRR = pin;          // Set pin
    else
        GPIOx->BSRR = (pin << 16);  // Reset pin
}
