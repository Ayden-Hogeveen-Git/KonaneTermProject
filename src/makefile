# Variables
CC = gcc
CFLAGS = -Wall -std=c99
DEBUGFLAGS = -g -o $@_debug
RELEASEFLAGS = -O2 -o $@
MODE = RELEASE

# Files and dependencies
EXE = gameDemo agentInterface
SRC = gameDemo.c agentInterface.c konane.c minimaxAgent.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

# Conditional statements

# Run 'make MODE=DEBUG' to compile in debug mode
ifeq ($(MODE), DEBUG)
	CFLAGS += $(DEBUGFLAGS)
else
	CFLAGS += $(RELEASEFLAGS)
endif

# Targets
all: $(EXE)

gameDemo: gameDemo.o konane.o minimaxAgent.o
	$(CC) $(CFLAGS) $^

agentInterface: agentInterface.o konane.o minimaxAgent.o
	$(CC) $(CFLAGS) $^

# Pattern rule for building object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files
-include $(DEP)

# Phony targets
.PHONY: valgrind-gameDemo valgrind-agentInterface \
		gdb-gameDemo gdb-agentInterface \
		test-agentInterface-newGameB \
		test-agentInterface-newGameW \
		test-agentInterface-game1B \
		test-agentInterface-game1W \
		test-driver-random-random \
		test-driver-random-agent \
		test-driver-agent-random \
		test-driver-agent-agent \
		clean tar

# Debugging targets
valgrind-gameDemo:
	valgrind --leak-check=full ./gameDemo

valgrind-agentInterface:
	valgrind --leak-check=full ./agentInterface ../test/board_states/newGameB.txt B

gdb-gameDemo:
	gdb ./gameDemo

gdb-agentInterface:
	gdb ./agentInterface ../test/board_states/newGameB.txt B

# Test targets
test: test-driver-random-agent

test-agentInterface-newGameB:
	./agentInterface ../test/board_states/newGameB.txt B

test-agentInterface-newGameW:
	./agentInterface ../test/board_states/newGameW.txt W

test-agentInterface-game1B:
	./agentInterface ../test/board_states/game1B.txt B

test-agentInterface-game1W:
	./agentInterface ../test/board_states/game1W.txt W

test-driver-random-random:
	cd ../test && perl drivercheck.pl konanerandomplayer konanerandomplayer

test-driver-random-agent:
	cd ../test && perl drivercheck.pl konanerandomplayer ../src/agentInterface

test-driver-agent-random:
	cd ../test && perl drivercheck.pl ../src/agentInterface konanerandomplayer

test-driver-agent-agent:
	cd ../test && perl drivercheck.pl ../src/agentInterface ../src/agentInterface

# Clean target
clean:
	rm -f $(EXE) $(OBJ) $(DEP)
	rm -f *_debug
	rm -f *.exe *.o *.out
	rm -f *.~ .*.swo .*.swp .nfo*

# Tar target
tar:
	tar -cvzf ../gameDemo.tar.gz -C ../ konane-term-project
	tar -cvzf ../agentInterface.tar.gz -C ../ konane-term-project
