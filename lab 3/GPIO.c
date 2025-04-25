#include "GPIO.h"
#include "stm32f4xx.h"
void GPIO_Init(void)
{
	RCC->AHB1ENR |= 0x1U;
	GPIOA->MODER |= 0x1U<<10;
	GPIOA->OSPEEDR |= 0X3u<<10;
}

void GPIO_ON(int pin_no)
{
	GPIOA->BSRR |= 0X1U<<pin_no;
}

void GPIO_OFF(int pin_no)
{
		GPIOA->BSRR |= 0X1U<<pin_no<<16;

}