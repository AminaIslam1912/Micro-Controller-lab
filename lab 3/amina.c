#include "stm32f4xx.h"                  // Device header
#include "CLOCK.h"
#include "GPIO.h"

int main(void){
	initClock();
	GPIO_Init();
	while(1)
	{
		GPIO_ON(5);
		for(int i=0;i < 100000000;i++);
		GPIO_OFF(5);
		for(int i=0;i < 100000000;i++);

	}
}