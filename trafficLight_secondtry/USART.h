#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"

/* Function prototypes */
void USART_Init(void);
void UART_SendChar(uint8_t c);
void UART_SendString(char *str);
uint8_t UART_GetChar(void);
void UART_GetString(char *str, uint8_t size);

#endif /* __USART_H */