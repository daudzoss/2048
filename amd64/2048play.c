#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

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

static inline void termsetup(int newsetup){   
  //http://stackoverflow.com/questions/1798511/how-to-avoid-press-enter-with-any-getchar
  static struct termios oldt, newt;

  if (newsetup) {
    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON);          

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

  } else 
    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

static inline void done(void) { termsetup(0); exit(0); }

char const* values[] = {"       ",
                        "[   2] ",
                        "[   4] ",
                        "[   8] ",
                        "[  16] ",
                        "[  32] ",
                        "[  64] ",
                        "[ 128] ",
                        "[ 256] ",
                        "[ 512] ",
                        "[1024] ",
                        "[2048] ",
                        "[2^12] ",
                        "[2^13] ",
                        "[2^14] ",
                        "[2^15] "};

void print4x4_C(register uint64_t di) {
 int n, i, j = 0;

 for (n = 0; n < 2; n++)
  for (i = 60 - 4*n; i >= 0; i -= 8)
   printf("%s%c", values[0xf & (di >> i)], ++j % 4 ? '\0' : '\n');
} // print4x4_()

int main(int argc, char* argv[]) {
  int moves = 0;
  grid_t grid = (argc > 1) ? strtol(argv[1], NULL, 16) : dropnew(gridempty);

  print4x4(grid);
  termsetup(1);
  while (1) {
    grid_t newgrid, grid_l, grid_d, grid_u, grid_r;

    grid_l = move(tilt_l, grid);
    grid_d = move(tilt_d, grid);
    grid_u = move(tilt_u, grid);
    grid_r = move(tilt_r, grid);
    if (grid ^ grid_l || grid ^ grid_d || grid ^ grid_u || grid ^ grid_r)
      switch (getchar()) {
      case 'h': case 'a': case '4': newgrid = grid_l; fputc('h', stderr); break;
      case 'j': case 's': case '2': newgrid = grid_d; fputc('j', stderr); break;
      case 'k': case 'w': case '8': newgrid = grid_u; fputc('k', stderr); break;
      case 'l': case 'd': case '6': newgrid = grid_r; fputc('l', stderr); break;
      case 'q': case '\033': done();
      case 'H':
      toggleH:
	if ((newgrid = grid_l) == grid)
	  break;
	fputc('h', stderr);
	moves++;
	grid_u = move(tilt_u, grid = dropnew(newgrid));
	putchar('\n');
	print4x4(grid);
      case 'K':
      toggleK:
	if ((newgrid = grid_u) == grid)
	  break;
	fputc('k', stderr);
	moves++;
	grid_l = move(tilt_l, grid = dropnew(newgrid));
	putchar('\n');
	print4x4(grid);
	goto toggleH;
      default: continue;
      }
    else
      done();

    if (newgrid != grid) {
      moves++;
      grid = dropnew(newgrid); 
      putchar('\n');
      print4x4(grid);
    }
    if (gamewon(/* 2 ^ */ 11, grid))
      break;
  }

  printf("total moves: %d\n", moves);
  done();
}
