#define STACK_SIZE 1024
unsigned int stack[STACK_SIZE];

void reset_handler() {
  while (1);
}

void *reset_vector[] __attribute__ ((section ("vectors")))= {
  &stack[STACK_SIZE-1],
  reset_handler
};
