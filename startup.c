#define STACK_SIZE 1024
unsigned int stack[STACK_SIZE];

extern unsigned int flash_start_data, ram_start_data, ram_end_data, start_bss, end_bss;

void reset_handler() __attribute__ ((naked));
void reset_handler() {
  unsigned int *flash_data = &flash_start_data, *ram_data = &ram_start_data, *bss = &start_bss;
  for (unsigned int i=0; i < (&ram_end_data - &ram_start_data); i++) {
    ram_data[i] = flash_data[i];
  }
  for (unsigned int i=0; i < (&end_bss - &start_bss); i++) {
    bss[i] = 0;
  }

  while (1);
}

void *reset_vector[] __attribute__ ((section ("vectors")))= {
  &stack[STACK_SIZE-1],
  reset_handler
};
