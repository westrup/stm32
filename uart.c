#include "uart.h"
#include <stm32f401xe.h>

void uart_init(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // enable clock for GPIOA

  GPIOA->MODER |= GPIO_MODER_MODER2_1; // PA2 AF
  GPIOA->MODER |= GPIO_MODER_MODER3_1; // PA3 AF
  GPIOA->AFR[0] |= 7 << (2*4); //PA2 AF_USART2
  GPIOA->AFR[0] |= 7 << (3*4); //PA3 AF_USART2

  RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // enable clock for USART2
  USART2->BRR  = SystemCoreClock/115200L; // set baudrate
  USART2->CR1 |= USART_CR1_RE | USART_CR1_TE; // RX, TX enable
  USART2->CR1 |= USART_CR1_UE; // USART enable
}

void put_char(char c)  {
  while (!(USART2->SR & USART_SR_TXE));
  USART2->DR = c;
}

char get_char(void)  {
  while (!(USART2->SR & USART_SR_RXNE));
  return USART2->DR & 0xFF;
}

void put_string(char *s) {
  while (*s)
    put_char(*s++);
}
