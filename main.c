#include "main.h"
#include "uart.h"
#include "led.h"

void main(void) {
  uart_init();
  led_init();
  put_string("boot\r\n");
  while (1) {
    led_toggle();
    char c = get_char();
    put_char(c);
    if (c == '\r')
      put_char('\n');
  }
}
