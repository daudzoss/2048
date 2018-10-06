ASM = nasm
ASMFLAGS = -felf64 -gdwarf

2048test : 2048test.o 2048drop.o 2048game.o
	gcc 2048test.o 2048drop.o 2048game.o -o 2048

2048test.o : 2048test.c
	gcc -g -c 2048test.c

2048drop.o : 2048drop.s macrodef.s
	$(ASM) $(ASMFLAGS) -l2048drop.lst 2048drop.s

2048game.o : 2048game.s macrodef.s
	$(ASM) $(ASMFLAGS) -l2048game.lst 2048game.s

clean :
	rm 2048*.o
