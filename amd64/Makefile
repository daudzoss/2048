AS = yasm
ASFLAGS = -felf64 -gdwarf2

CC = gcc
CCFLAGS = -g -c -std=c99

LD = gcc
LDFLAGS = 

ME = Makefile

2048play : 2048play.o 2048drop.o 2048game.o $(ME)
	$(LD) 2048play.o 2048drop.o 2048game.o -o 2048play

2048play.o : 2048play.c $(ME)
	$(CC) $(CCFLAGS) 2048play.c

2048auto : 2048auto.o 2048drop.o 2048game.o logbase2.o $(ME)
	$(LD) 2048auto.o 2048drop.o 2048game.o logbase2.o -o 2048auto

2048auto.o : 2048auto.c $(ME)
	$(CC) $(CCFLAGS) 2048auto.c

2048test : 2048test.o 2048drop.o 2048game.o logbase2.o $(ME)
	$(LD) 2048test.o 2048drop.o 2048game.o logbase2.o -o 2048test

2048test.o : 2048test.c $(ME)
	$(CC) $(CCFLAGS) 2048test.c

2048drop.o : 2048drop.s macrodef.s $(ME)
	$(AS) $(ASFLAGS) -l2048drop.lst 2048drop.s

2048game.o : 2048game.s macrodef.s $(ME)
	$(AS) $(ASFLAGS) -l2048game.lst 2048game.s

logbase2.o : logbase2.s $(ME)
	$(AS) $(ASFLAGS) -llogbase2.lst logbase2.s

clean :
	rm *.o
