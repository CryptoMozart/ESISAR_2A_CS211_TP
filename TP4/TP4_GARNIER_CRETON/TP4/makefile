OBJS	= AlgoGenetique.o main.o
SOURCE	= AlgoGenetique.c main.c
HEADER	= AlgoGenetique.h
OUT	= malefique
CC	 = gcc
FLAGS	 = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

AlgoGenetique.o: AlgoGenetique.c
	$(CC) $(FLAGS) AlgoGenetique.c 

main.o: main.c
	$(CC) $(FLAGS) main.c 


clean:
	rm -f $(OBJS) $(OUT)