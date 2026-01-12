CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm

all: pso

pso: main.o map.o pso.o logger.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c map.h pso.h logger.h
	$(CC) $(CFLAGS) -c main.c -o main.o

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c -o map.o

pso.o: pso.c pso.h
	$(CC) $(CFLAGS) -c pso.c -o pso.o

logger.o: logger.c logger.h
	$(CC) $(CFLAGS) -c logger.c -o logger.o

clean:
	rm -f *.o pso

.PHONY: all clean