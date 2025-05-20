#include "USART.h"

/**
 * @brief  Initialize USART2 for communication (PA2=TX, PA3=RX)
 * @param  None
 * @retval None
 */
void USART_Init(void)
{
  /* Enable GPIOA clock */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  
  /* Enable USART2 clock */
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  
  /* Configure PA2 (USART2_TX) as alternate function */
  GPIOA->MODER &= ~GPIO_MODER_MODER2;
  GPIOA->MODER |= GPIO_MODER_MODER2_1;  /* Alternate function mode */
  GPIOA->AFR[0] &= ~(0xF << (2 * 4));   /* Clear AF bits for pin 2 */
  GPIOA->AFR[0] |= (7 << (2 * 4));      /* AF7 (USART2) - 4 bits per pin, pin 2 */
  GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2;  /* High speed */
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR2;   /* No pull-up, no pull-down */
  
  /* Configure PA3 (USART2_RX) as alternate function */
  GPIOA->MODER &= ~GPIO_MODER_MODER3;
  GPIOA->MODER |= GPIO_MODER_MODER3_1;  /* Alternate function mode */
  GPIOA->AFR[0] &= ~(0xF << (3 * 4));   /* Clear AF bits for pin 3 */
  GPIOA->AFR[0] |= (7 << (3 * 4));      /* AF7 (USART2) - 4 bits per pin, pin 3 */
  GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;  /* High speed */
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR3;   /* No pull-up, no pull-down */
  
  /* Configure USART2 */
  USART2->CR1 = 0;  /* Clear CR1 register */
  USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;  /* Enable transmitter and receiver */
  
  /* Configure baudrate (9600 baud) */
  /* With PCLK1 = 45MHz, BRR = 45000000/9600 = 4687.5 = 0x1250 */
  USART2->BRR = 0x1250;
  
  /* Enable USART2 */
  USART2->CR1 |= USART_CR1_UE;
}

/**
 * @brief  Send a character through USART2
 * @param  c: character to send
 * @retval None
 */
void UART_SendChar(uint8_t c)
{
  /* Wait until transmit data register is empty */
  while (!(USART2->SR & USART_SR_TXE));
  
  /* Send character */
  USART2->DR = c;
}

/**
 * @brief  Send a string through USART2
 * @param  str: string to send
 * @retval None
 */
void UART_SendString(char *str)
{
  while (*str)
  {
    UART_SendChar(*str++);
  }
}

/**
 * @brief  Receive a character from USART2
 * @param  None
 * @retval Received character
 */
uint8_t UART_GetChar(void)
{
  /* Wait until receive data register is not empty */
  while (!(USART2->SR & USART_SR_RXNE));
  
  /* Return received character */
  return (uint8_t)USART2->DR;
}

/**
 * @brief  Receive a string from USART2
 * @param  str: buffer to store received string
 * @param  size: maximum size of the buffer
 * @retval None
 */
void UART_GetString(char *str, uint8_t size)
{
  uint8_t i = 0;
  uint8_t c = 0;
  
  do
  {
    c = UART_GetChar();
    str[i++] = c;
    
    /* Echo character */
    UART_SendChar(c);
  } while ((c != '\r') && (i < size - 1));
  
  /* Add null terminator */
  str[i] = '\0';
}