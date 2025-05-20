#include "GPIO.h"
#include "stm32f4xx.h"

void GPIO_Init(void)
{
    RCC->AHB1ENR |= 0x1U;           // Enable GPIOA clock
    GPIOA->MODER |= 0x1U << 10;     // PA5 as output (MODER[11:10] = 01)
    GPIOA->OSPEEDR |= 0x3U << 10;   // PA5 very high speed
}

void GPIO_ON(int pin_no)
{
    GPIOA->BSRR = 0x1U << pin_no;   // Set pin high
}

void GPIO_OFF(int pin_no)
{
    GPIOA->BSRR = 0x1U << (pin_no + 16); // Set pin low
}