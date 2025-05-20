#include "stm32f4xx.h"
#include "SYSINIT.h"

void systemInit(void) {
    // Placeholder for other system initialization
}

void ms_delay(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 8000; i++) {
        __NOP();
    }
}
