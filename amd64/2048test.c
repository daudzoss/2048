#include <stdio.h>
#include <stdint.h>

extern void print4x4(uint64_t);

extern uint64_t empties(uint64_t);

uint64_t print_em(uint64_t grid) {
  uint64_t em = empties(grid);
  uint64_t mask = 0x000000000000000f;
  int i, count;

  count = em & mask;
  printf("0x%016lx\n%ld empty nybbles", grid, count ? count : (em ? 16 : 0));

  for (i = 0; i < 15; i++) {
    int empty;

    if (empty = ((em >> (4*(i+1))) & mask) ? 1 : 0)
      printf(" %d", i);
    count -= empty;
  }
  if (count)
    printf(" %d", i); // implicitly the 16th one also blank

  printf("\n\n");
  return em;
}

void print_test(void) {
  uint64_t gridempty = 0x0000000000000000;
  uint64_t lastempty = 0x123456789abcdef0;
  uint64_t outputseq = 0x08192a3b4c5d6e7f;
  uint64_t noneempty = 0x1111222233334444;
  uint64_t oddsempty = 0x1020304050607080;

  print4x4(gridempty);
  print_em(gridempty);
  print4x4(lastempty);
  print_em(lastempty);
  print4x4(outputseq);
  print_em(outputseq);
  print4x4(noneempty);
  print_em(noneempty);
  print4x4(oddsempty);
  print_em(oddsempty);
}

void move_test(void) {
}

void drop_test(void) {
}

void main(void) {
  print_test();
}
