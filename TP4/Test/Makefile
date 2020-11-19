OBJS	= AlgoGenetique.o main.o
SOURCE	= AlgoGenetique.c main.c
HEADER	= AlgoGenetique.h
OUT	= executable
CC	 = gcc
FLAGS	 = -g -c -ln -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

AlgoGenetique.o: AlgoGenetique.c
	$(CC) $(FLAGS) AlgoGenetique.c 

main.o: main.c
	$(CC) $(FLAGS) main.c 


clean:
	rm -f $(OBJS)
