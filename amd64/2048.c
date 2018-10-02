#include <stdio.h>
#include <stdint.h>

extern void print4x4(uint64_t);

extern uint64_t empties(uint64_t);

uint64_t print_em(uint64_t grid){
  uint64_t em = empties(grid);
  uint64_t mask = 0x000000000000000f;
  int i, count;

  printf("%ld empty nybbles", count = em & mask);

  for (i = 0; i < 16; i++) {
    int empty;

    if (empty = ((em >> (4*(i+1))) & mask) ? 1 : 0)
      printf(" %d", i);
    count -= empty;
  }
  if (count)
    printf(" %d", i); // implicitly the 16th one also blank

  printf("\n");
  return em;
}

void main(void) {
  uint64_t gridempty = 0x0000000000000000;
  uint64_t lastempty = 0x123456789abcdef0;
  uint64_t noneempty = 0x1111222233334444;

  print4x4(gridempty);
  print_em(gridempty);
  print4x4(lastempty);
  print_em(lastempty);
  print4x4(noneempty);
  print_em(noneempty);
}
