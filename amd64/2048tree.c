#include <stdint.h>
#include <stdio.h>

uint64_t gridempty = 0x0000000000000000;

extern void print4x4(uint64_t);

extern uint64_t empties(uint64_t);

extern uint64_t gamewon(uint64_t, uint64_t);

extern uint64_t logbase2(uint64_t);

extern uint64_t transpo(uint64_t);

extern uint64_t dropnew(uint64_t);
extern uint64_t move(int8_t, uint64_t);

printmov(int8_t mov, uint64_t old) {
  static char* dirname[] = {"up", "left", "flat", "right", "down"};
  uint64_t new = move(mov, old);
  uint64_t i = mov + 2;

  printf("tilted %s (%d):\n", (i >= 0 && i < 5) ? dirname[i] : "INVALID", mov);
  print4x4(new);
  printf("\n\n");
}

void main(void) {
  tran_test();
  for (int8_t i = -1; i <= +3; i++)
    dir_test(i);
  drop_test();
  win_test(logbase2(2048L));
}
