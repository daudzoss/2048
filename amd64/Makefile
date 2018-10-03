2048test : 2048test.o 2048game.o
	gcc 2048test.o 2048game.o -o 2048

2048test.o : 2048test.c
	gcc -g -c 2048test.c

2048game.o : 2048game.s
	yasm -felf64 -gdwarf2 -l2048game.lst 2048game.s

clean :
	rm 2048*.o
