#include <unistd.h>
#include <uart.h>
#include "py/mpconfig.h"

#include "mpducky.h"

/*
 * Core UART functions to implement for a port
 */

int mp_hal_stdin_rx_chr(void)
{
  return __uart_read_rbr();
  /*
  u8_t c;

  while (1) {
    c = *kbd_mmio_address;

    if (c == 0xFF) {
      idle();
      continue;
    }

    return c;
  }
  */
  return 0;
}

void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len)
{
  while(len--)
    __uart_write_thr(*str++);
}
