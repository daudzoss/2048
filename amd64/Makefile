2048 : 2048.o 2048game.o
	gcc 2048.o 2048game.o -o 2048

2048.o : 2048.c
	gcc -g -c 2048.c

2048game.o : 2048game.s
	yasm -felf64 -gdwarf2 -l2048game.lst 2048game.s

clean :
	rm 2048*.o
