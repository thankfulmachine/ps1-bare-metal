
#include "ps1/registers.h"
#include <stdio.h>

extern int32_t OpenEvent(uint32_t, int32_t, int32_t, void *);
extern int32_t EnableEvent(uint32_t);
extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern void __attribute__((noreturn)) ReturnFromException(void);
uint32_t frame = 0;

static void vblankHandler()
{
  frame++;
  ReturnFromException();
}

int main(int argc, const char **argv)
{
  SIO_CTRL(1) = SIO_CTRL_RESET;
  SIO_MODE(1) = SIO_MODE_BAUD_DIV16 | SIO_MODE_DATA_8 | SIO_MODE_STOP_1;
  SIO_BAUD(1) = (F_CPU / 16) / 115200;
  SIO_CTRL(1) = SIO_CTRL_TX_ENABLE | SIO_CTRL_RX_ENABLE | SIO_CTRL_RTS;

  EnterCriticalSection();
  uint32_t event = OpenEvent(
    /* vblank = DescRC | RCntCNT3*/ 0xf2000003,
    /* type/spec = interrupted */ 0x0002,
    /* mode = interrupt/callback */ 0x1000,
    /* callback */ vblankHandler
  );
  EnableEvent(event);
  ExitCriticalSection();
  char buf[81] = {0};
  for (;;)
  {
    if (frame)
    {
      snprintf(buf, 80, "Frame count = %lu\n", frame);
      puts(buf);
    }
  }

  return 0;
}
