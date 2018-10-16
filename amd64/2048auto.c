#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint64_t grid_t;
const grid_t gridempty = 0L;

typedef int64_t tilt_t;
const tilt_t tilt_begin = -2;
const tilt_t tilt_u = -2;
const tilt_t tilt_l = -1;
const tilt_t notilt = 0;
const tilt_t tilt_r = +1;
const tilt_t tilt_d = +2;
const tilt_t tilt_end = +3;

extern void print4x4(grid_t);

extern grid_t empties(grid_t);

extern grid_t gamewon(uint64_t, grid_t);

extern int64_t logbase2(uint64_t);

extern grid_t dropnew(grid_t);

extern grid_t move(tilt_t, grid_t);

void printmov(tilt_t mov, grid_t old, grid_t new) {
  static char* dirname[] = {"up", "left", "flat", "right", "down"};
  tilt_t i = mov + 2;

  printf("----------------------------\n");
  print4x4(new);
  printf("was tilted %s (%d) from:\n", (i>=0 && i<5) ? dirname[i] : "???", mov);
  print4x4(old);
  printf("----------------------------\n\n");
}

tilt_t other_tilt(tilt_t tilt) { return (tilt < 0) ? (-3 - tilt) : tilt_begin; }

int moves_to(uint64_t target, grid_t prev_grid, tilt_t prev_tilt) {
  tilt_t curr_tilt;
  grid_t curr_grid;
  int win = 0, temp;

  if (gamewon(logbase2(target), prev_grid))
    return 1;

  // we're assuming prev_grid is neither won (target reached) nor seized up
  prev_grid = dropnew(prev_grid);

  // try to repeat previous tilt if possible for maximum coalescing
  if ((curr_grid = move(prev_tilt, prev_grid)) != prev_grid) {
    curr_tilt = prev_tilt;
    if ((temp = moves_to(target, curr_grid, curr_tilt)) > 0)
	win = temp;
  } else
    for (curr_tilt = other_tilt(prev_tilt);
         curr_tilt < tilt_end;
	 curr_tilt++)
      if ((curr_grid = move(curr_tilt, prev_grid)) == prev_grid) // no move
	continue;
      else if ((temp = moves_to(target, curr_grid, curr_tilt)) > 0) {
	win = temp;
	break; // grid is seized up; no possible move
      }

  if (win) {
    printmov(curr_tilt, prev_grid, curr_grid);
    return 1 + win;
  } else
    return 1<<(sizeof(int)*8-1); // minimum negative integer
}

int main(int argc, char* argv[]) {
  int moves;
  grid_t start = (argc > 1) ? strtol(argv[1], NULL, 16) : gridempty;
  print4x4(start);
  fflush(stdout);
  moves = moves_to(2048L, start, notilt);
  printf("total moves: %d\n", moves);
  moves = (moves < 256) ? moves : 255;
  exit(moves);
}
