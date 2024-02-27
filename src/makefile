# Variables
CC = gcc
CFLAGS = -Wall -std=c99 -g

# Targets
all: gameDemo agentInterface

gameDemo: gameDemo.o konane.o minimaxAgent.o
	$(CC) $^ -o $@

gameDemo.o: gameDemo.c structures.h konane.h minimaxAgent.h
	$(CC) $(CFLAGS) $< -c

agentInterface: agentInterface.o konane.o minimaxAgent.o
	$(CC) $^ -o $@

agentInterface.o: agentInterface.c structures.h agentInterface.h minimaxAgent.h

minimaxAgent.o: minimaxAgent.c structures.h konane.h minimaxAgent.h
	$(CC) $(CFLAGS) $< -c

konane.o: konane.c structures.h konane.h
	$(CC) $(CFLAGS) $< -c

# Phony targets
.PHONY: valgrind-gameDemo valgrind-agentInterface clean tar

valgrind-gameDemo:
	valgrind --leak-check=full ./gameDemo

valgrind-agentInterface:

clean:
	rm -f gameDemo agentInterface konane 
	rm -f *.exe *.o *.out
	rm -f *.~ .*.swo .*.swp .nfo*

tar:
	tar -cvzf ../gameDemo.tar.gz -C ../ konane-term-project
	tar -cvzf ../agentInterface.tar.gz -C ../ konane-term-project
