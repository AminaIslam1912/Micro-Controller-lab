#include "stm32f4xx.h"
#include "SYSINIT.h"



void ms_delay(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 10000; i++) {
        __NOP();
    }
}
