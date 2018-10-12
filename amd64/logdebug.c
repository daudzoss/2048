#include <stdio.h>
#include <stdlib.h>

extern int logbase2(long);

int main(int argc, char** argv) {
  int i, l = -1;
  
  for (i = 1; i < argc; i++) {
    long x = atol(argv[i]);
    l = logbase2(x);

    printf("log2(%ld) == %d\n", x, l);
  }

  exit(l);
}
