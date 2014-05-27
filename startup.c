#include <stm32f401xe.h>
#include "main.h"

#define STACK_SIZE 1024
uint32_t stack[STACK_SIZE];
uint32_t SystemCoreClock = 16000000;

extern uint32_t flash_start_data, ram_start_data, ram_end_data, start_bss, end_bss;

void reset_handler() __attribute__ ((naked));
void reset_handler() {
  uint32_t *flash_data = &flash_start_data, *ram_data = &ram_start_data, *bss = &start_bss;
  for (uint32_t i=0; i < (&ram_end_data - &ram_start_data); i++) {
    ram_data[i] = flash_data[i];
  }
  for (uint32_t i=0; i < (&end_bss - &start_bss); i++) {
    bss[i] = 0;
  }

  main();
}

void error_handler() {
  while(1);
}

struct vector_table {
  void* cortex[16];
  void* stm32[62];
};

struct vector_table reset_vector __attribute__ ((section ("vectors"))) = {
  .cortex = {
    [0] = &stack[STACK_SIZE-1],
    [1] = reset_handler, // startup
    [2 ... 6] = error_handler, // NMI, ..., MPU Fault, Bus Fault, Usage Fault
    //[15] = systick_handler,
  },
  .stm32 = {
    //[EXTI0_IRQn ... EXTI4_IRQn] = exti_handler,
  }
};
