#include "stm32f4xx.h"
#include "CLOCK.h"
#include "SYSINIT.h"
#include "GPIO.h"
#include <stdlib.h>

#define NORTH_SOUTH_RED    (1 << 0)
#define NORTH_SOUTH_YEL    (1 << 1)
#define NORTH_SOUTH_GRN    (1 << 2)
#define EAST_WEST_RED      (1 << 3)
#define EAST_WEST_YEL      (1 << 4)
#define EAST_WEST_GRN      (1 << 5)

#define NS_LOAD_LED        (1 << 6)  // PA6
#define EW_LOAD_LED        (1 << 7)  // PA7

typedef enum {
    NORTH_SOUTH_GREEN,
    YELLOW,
    EAST_WEST_GREEN,
  //  EAST_WEST_YELLOW
} TrafficState;

void traffic_init(void) {
   // RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOAEN;

    // PB0�PB5 as output (traffic signals)
   /* GPIOB->MODER &= ~(0x3FFF);
    GPIOB->MODER |= (0x1555);
    GPIOB->OTYPER &= ~(0x3F);
    GPIOB->OSPEEDR |= (0x3FFF);
    GPIOB->PUPDR &= ~(0x3FFF);

    // PA6�PA7 as output (load indicator LEDs)
    GPIOA->MODER &= ~(0xF << 12);
    GPIOA->MODER |=  (0x5 << 12);   // Set PA6 and PA7 as output
    GPIOA->OTYPER &= ~(NS_LOAD_LED | EW_LOAD_LED);
    GPIOA->OSPEEDR |=  (0xF << 12);
    GPIOA->PUPDR &= ~(0xF << 12);
	*/
	
	  RCC->AHB1ENR |= (1 << 0); // GPIOA
    RCC->AHB1ENR |= (1 << 1); // GPIOB

    /******** PB0�PB5 as Output ********/
    // Set mode to output (01)
    GPIOB->MODER &= ~(0b11 << 0);  // Clear PB0
    GPIOB->MODER |=  (0b01 << 0);  // Set PB0 as output
    GPIOB->MODER &= ~(0b11 << 2);  // PB1
    GPIOB->MODER |=  (0b01 << 2);
    GPIOB->MODER &= ~(0b11 << 4);  // PB2
    GPIOB->MODER |=  (0b01 << 4);
    GPIOB->MODER &= ~(0b11 << 6);  // PB3
    GPIOB->MODER |=  (0b01 << 6);
    GPIOB->MODER &= ~(0b11 << 8);  // PB4
    GPIOB->MODER |=  (0b01 << 8);
    GPIOB->MODER &= ~(0b11 << 10); // PB5
    GPIOB->MODER |=  (0b01 << 10);

   // GPIOB->OSPEEDR |=  (0x3FFF);   // High speed
	 
	 // PB0
   GPIOB->OSPEEDR &= ~(0b11 << 0);   // Clear bits
   GPIOB->OSPEEDR |=  (0b11 << 0);   // Set high speed

// PB1
  GPIOB->OSPEEDR &= ~(0b11 << 2);
  GPIOB->OSPEEDR |=  (0b11 << 2);

// PB2
  GPIOB->OSPEEDR &= ~(0b11 << 4);
  GPIOB->OSPEEDR |=  (0b11 << 4);

// PB3
  GPIOB->OSPEEDR &= ~(0b11 << 6);
  GPIOB->OSPEEDR |=  (0b11 << 6);

// PB4
  GPIOB->OSPEEDR &= ~(0b11 << 8);
  GPIOB->OSPEEDR |=  (0b11 << 8);

// PB5
  GPIOB->OSPEEDR &= ~(0b11 << 10);
  GPIOB->OSPEEDR |=  (0b11 << 10);

    GPIOA->MODER &= ~(0b11 << 12); // Clear PA6
    GPIOA->MODER |=  (0b01 << 12); // Set PA6 as output
    GPIOA->MODER &= ~(0b11 << 14); // Clear PA7
    GPIOA->MODER |=  (0b01 << 14); // Set PA7 as output

    GPIOA->OSPEEDR |=  (0b11 << 12) | (0b11 << 14); // High speed
}

void set_traffic_lights(TrafficState state) {
    //GPIOB->ODR &= ~(NORTH_SOUTH_RED | NORTH_SOUTH_YEL | NORTH_SOUTH_GRN |
    //                EAST_WEST_RED | EAST_WEST_YEL | EAST_WEST_GRN);

	GPIOB->BSRR = ((NORTH_SOUTH_RED | NORTH_SOUTH_YEL | NORTH_SOUTH_GRN |
                EAST_WEST_RED | EAST_WEST_YEL | EAST_WEST_GRN) << 16);  // Reset all

	
    switch (state) {
        case NORTH_SOUTH_GREEN:
            GPIO_WritePin(GPIOB, NORTH_SOUTH_GRN, 1);
            GPIO_WritePin(GPIOB, EAST_WEST_RED, 1);
            break;
        case YELLOW:
            GPIO_WritePin(GPIOB, NORTH_SOUTH_YEL, 1);
            GPIO_WritePin(GPIOB, EAST_WEST_YEL, 1); 
            break;
        case EAST_WEST_GREEN:
            GPIO_WritePin(GPIOB, EAST_WEST_GRN, 1);
            GPIO_WritePin(GPIOB, NORTH_SOUTH_RED, 1);
            break;
       /* case EAST_WEST_YELLOW:
            GPIO_WritePin(GPIOB, EAST_WEST_YEL, 1);
            GPIO_WritePin(GPIOB, NORTH_SOUTH_YEL, 1); 
            break;
				*/
    }
}

void simulate_random_load(uint8_t *ns_high, uint8_t *ew_high) {
    *ns_high = (rand() % 2);  // 0 or 1
    *ew_high = (rand() % 2);

    GPIO_WritePin(GPIOA, NS_LOAD_LED, *ns_high);
    GPIO_WritePin(GPIOA, EW_LOAD_LED, *ew_high);
}

void traffic_control(void) {
    uint8_t ns_high = 0;
    uint8_t ew_high = 0;

    while (1) {
        simulate_random_load(&ns_high, &ew_high);
			uint32_t green_delay_ns =0;
      uint32_t green_delay_ew=0;
        //uint32_t green_delay_ns = ns_high ? 20000 : 10000;
        //uint32_t green_delay_ew = ew_high ? 20000 : 10000;
			
				if(!ns_high && !ew_high){
						 green_delay_ns = 10000;
						 green_delay_ew = 10000;
			
				}
				
				if(!ns_high && ew_high){
						 green_delay_ns = 10000;
						 green_delay_ew = 20000;
			
				}

				if(ns_high && !ew_high){
						 green_delay_ns = 20000;
						 green_delay_ew = 10000;
			
				}

				if(ns_high && ew_high){
						 green_delay_ns = 10000;
						 green_delay_ew = 10000;
			
				}


        set_traffic_lights(NORTH_SOUTH_GREEN);
        ms_delay(green_delay_ns);
        set_traffic_lights(YELLOW);
        ms_delay(5000);

       // simulate_random_load(&ns_high, &ew_high); // Update before EW signal
				
       // green_delay_ew = ew_high ? 20000 : 10000;
				
				
			/*	if(!ns_high && !ew_high){
						// green_delay_ns = 10000;
						 green_delay_ew = 10000;
			
				}
				
				if(!ns_high && ew_high){
						// green_delay_ns = 20000;
						 green_delay_ew = 10000;
			
				}

				if(ns_high && !ew_high){
						// green_delay_ns = 20000;
						 green_delay_ew = 10000;
			
				}

				if(ns_high && ew_high){
						// green_delay_ns = 10000;
						 green_delay_ew = 10000;
			
				}
*/
        set_traffic_lights(EAST_WEST_GREEN);
        ms_delay(green_delay_ew);
        set_traffic_lights(YELLOW);
        ms_delay(5000);
    }
}

int main(void) {
    initClock();
    systemInit();
    traffic_init();
    traffic_control();
    return 0;
}
