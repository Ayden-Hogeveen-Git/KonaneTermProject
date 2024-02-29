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
.PHONY: valgrind-gameDemo valgcoordTind-agentInterface
		test-agentInterface-newGameB
		test-agentInterface-newGameW
		test-agentInterface-game1B
		test-agentInterface-game1W
		test-driver-random-random
		test-driver-random-agent
		test-driver-agent-random
		test-driver-agent-agent
		clean tar

valgrind-gameDemo:
	valgrind --leak-check=full ./gameDemo

valgrind-agentInterface:
	valgrind --leak-check=full ./agentInterface

test-agentInterface-newGameB:
	./agentInterface ../test/board_states/newGameB.txt B

test-agentInterface-newGameW:
	./agentInterface ../test/board_states/newGameW.txt W

test-agentInterface-game1B:
	./agentInterface ../test/board_states/game1B.txt B

test-agentInterface-game1W:
	./agentInterface ../test/board_states/game1W.txt W

test-driver-random-random:
	perl ../test/drivercheck.pl ../test/konanerandomplayer ../test/konanerandomplayer

test-driver-random-agent:
	perl ../test/drivercheck.pl ../test/konanerandomplayer ./agentInterface

test-driver-agent-random:
	perl ../test/drivercheck.pl ./agentInterface ../test/konanerandomplayer

test-driver-agent-agent:
	perl ../test/drivercheck.pl ./agentInterface ./agentInterface

clean:
	rm -f gameDemo agentInterface konane
	rm -f *.exe *.o *.out
	rm -f *.~ .*.swo .*.swp .nfo*

tar:
	tar -cvzf ../gameDemo.tar.gz -C ../ konane-term-project
	tar -cvzf ../agentInterface.tar.gz -C ../ konane-term-project
