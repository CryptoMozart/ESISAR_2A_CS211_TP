main: main.o fonctions.o bitmap.h
		gcc -o $@ $^

%.o: %.c
		gcc -g -c $<

clean:
		rm -rf *.o
		rm -rf main
		rm -rf test
