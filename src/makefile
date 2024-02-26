# Variables
CC = gcc
CFLAGS = -Wall -std=c99 -g

# Targets
all: main minimaxAgent

main: main.o konane.o minimaxAgent.o
	$(CC) $^ -o $@

main.o: main.c konane.h minimaxAgent.h
	$(CC) $(CFLAGS) $< -c

konane.o: konane.c konane.h
	$(CC) $(CFLAGS) $< -c

minimaxAgent.o: minimaxAgent.c minimaxAgent.h
	$(CC) $(CFLAGS) $< -c

minimaxAgent: minimaxAgent.c
	$(CC) minimaxAgent.c -o minimaxAgent

# Phony targets
.PHONY: valgrind-main clean tar

valgrind-main:
	valgrind --leak-check=full ./main

clean:
	rm -f main konane minimaxAgent
	rm -f *.exe *.o *.out
	rm -f *.~ .*.swo .*.swp .nfo*

tar:
	tar -cvzf ../main.tar.gz -C ../ konane-term-project
