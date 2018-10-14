#include <stdint.h>
#include <stdio.h>

uint64_t gridempty = 0x0000000000000000;
uint64_t lastempty = 0x123456789abcdef0;
uint64_t outputseq = 0x08192a3b4c5d6e7f;
uint64_t noneempty = 0x1111222233334444;
uint64_t oddsempty = 0x1020304050607080;

extern void print4x4(uint64_t);

extern uint64_t empties(uint64_t);

extern uint64_t gamewon(uint64_t, uint64_t);

extern uint64_t logbase2(uint64_t);

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

  printf(" (0x%lx)\n\n", em);
  return em;
}

void print_test(void) {
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

extern uint64_t dropnew(uint64_t);
extern uint64_t move(int8_t, uint64_t);

void printnew(uint64_t old) {
  uint64_t new = dropnew(old);

  print4x4(old);
  printf("dropping 0x%016lx:\n", old ^ new);
  print4x4(new);
  printf("\n\n");
}

void printmov(int8_t mov, uint64_t old) {
  static char* dirname[] = {"up", "left", "flat", "right", "down"};
  uint64_t new = move(mov, old);
  uint64_t i = mov + 2;

  print4x4(old);
  printf("tilted %s (%d):\n", (i >= 0 && i < 5) ? dirname[i] : "INVALID", mov);
  print4x4(new);
  printf("\n\n");
}

void printwon(uint64_t exponent, uint64_t grid) {
  print4x4(grid);
  if (gamewon(exponent, grid))
    printf("WINNER!\n");
  else
    printf("not won\n");
}

void drop_test(void) {
  printnew(gridempty);
  printnew(lastempty);
  printnew(outputseq);
  printnew(noneempty);
  printnew(oddsempty);
}

void dir_test(int8_t dir) {
  printmov(dir, gridempty);
  printmov(dir, lastempty);
  printmov(dir, outputseq);
  printmov(dir, noneempty);
  printmov(dir, oddsempty);
}

void win_test(uint64_t exponent) {
  printwon(exponent, gridempty);
  printwon(exponent, lastempty);
  printwon(exponent, outputseq);
  printwon(exponent, noneempty);
  printwon(exponent, oddsempty);
}

void main(void) {
  printmov(2, oddsempty);
//  for (int8_t i = -1; i <= +3; i++)
//    dir_test(i);
//  drop_test();
//  win_test(logbase2(2048));
}
