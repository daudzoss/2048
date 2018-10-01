#include <stdio.h>
#include <stdint.h>

extern void print4x4(uint64_t);

extern uint64_t empties(uint64_t);

void main(void) {
  uint64_t gridempty = 0x0000000000000000;
  uint64_t lastempty = 0x123456789abcdef0;
  uint64_t noneempty = 0x1111222233334444;

  print4x4(gridempty);
}
