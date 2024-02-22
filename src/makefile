# Variables
CC = gcc
CFLAGS = -Wall -std=c99 -g

# Targets
all: main 

main: main.o konane.o agent.o
	$(CC) $^ -o $@

main.o: main.c konane.h agent.h
	$(CC) $(CFLAGS) $< -c

konane.o: konane.c konane.h
	$(CC) $(CFLAGS) $< -c

agent.o: agent.c agent.h
	$(CC) $(CFLAGS) $< -c

# Phony targets
.PHONY: valgrind-main clean tar

valgrind-main:
	valgrind --leak-check=full ./main

clean:
	rm -f main konane
	rm -f *.exe *.o *.out
	rm -f *.~ .*.swo .*.swp .nfo*

tar:
	tar -cvzf ../main.tar.gz -C ../ konane-term-project
