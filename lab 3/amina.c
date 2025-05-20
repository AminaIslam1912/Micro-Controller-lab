#include "stm32f4xx.h" // Device header
#include "CLOCK.h"
#include "GPIO.h"

int main(void)
{
    initClock();
    GPIO_Init();
    while(1)
    {
        GPIO_ON(5); // Turn LED on (PA5 high)
        for(volatile int i = 0; i < 1000000; i++); // Delay
        GPIO_OFF(5); // Turn LED off (PA5 low)
        for(volatile int i = 0; i < 1000000; i++); // Delay
    }
}