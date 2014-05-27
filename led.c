#include "led.h"
#include <stm32f401xe.h>

void led_init(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // enable clock for GPIOA
  GPIOA->MODER |= GPIO_MODER_MODER5_0; // PA5 OUTPUT
}

void led_on(void) {
  GPIOA->BSRRL = GPIO_BSRR_BS_5;
}

void led_off(void) {
  GPIOA->BSRRH = GPIO_BSRR_BS_5;
}

void led_toggle(void) {
  if (GPIOA->ODR & GPIO_ODR_ODR_5)
    led_off();
  else
    led_on();
}