#include "main.h"
#include "uart.h"

void main(void) {
  uart_init();
  put_string("boot\r\n");
  while (1) {
    char c = get_char();
    put_char(c);
    if (c == '\r')
      put_char('\n');
  }
}
