# Variables
CC = gcc
CFLAGS = -Wall -std=c99
DEBUG_FLAGS = $(CFLAGS) -g -MMD -MP -D DEBUG
RELEASE_FLAGS = $(CFLAGS) -O2 -MMD -MP

# Source files
SRC = gameDemo.c agentInterface.c konane.c evaluation.c \
	  minimax.c minimaxAlphaBeta.c logging.c

# Executables
EXE = agentInterface agentInterfaceAlphaBeta T3

# Object files
OBJ = $(SRC:.c=.o)



# Release Executables
all: agentInterface agentInterfaceAlphaBeta

agentInterface: agentInterface.o konane.o minimax.o evaluation.o
	$(CC) $(RELEASE_FLAGS) $^ -o $@

agentInterfaceAlphaBeta: agentInterfaceAlphaBeta.o konane.o minimaxAlphaBeta.o evaluation.o
	$(CC) $(RELEASE_FLAGS) $^ -o $@ -D ALPHA_BETA



# Release Object files
agentInterface.o: agentInterface.c agentInterface.h structures.h konane.h
	$(CC) $(RELEASE_FLAGS) -c $< -o $@

agentInterfaceAlphaBeta.o: agentInterface.c agentInterface.h structures.h konane.h
	$(CC) $(RELEASE_FLAGS) -c $< -o $@ -D ALPHA_BETA

konane.o: konane.c konane.h structures.h
	$(CC) $(RELEASE_FLAGS) -c $< -o $@

minimax.o: minimax.c minimax.h structures.h konane.h evaluation.h
	$(CC) $(RELEASE_FLAGS) -c $< -o $@

minimaxAlphaBeta.o: minimaxAlphaBeta.c minimaxAlphaBeta.h structures.h konane.h evaluation.h
	$(CC) $(RELEASE_FLAGS) -c $< -o $@ -D ALPHA_BETA

evaluation.o: evaluation.c evaluation.h structures.h konane.h
	$(CC) $(RELEASE_FLAGS) -c $< -o $@



# Debug Executables
debug: agentInterface_debug agentInterfaceAlphaBeta_debug

agentInterface_debug: agentInterface_debug.o konane_debug.o minimax_debug.o evaluation_debug.o logging.o
	$(CC) $(DEBUG_FLAGS) $^ -o $@

agentInterfaceAlphaBeta_debug: agentInterfaceAlphaBeta_debug.o konane_debug.o minimaxAlphaBeta_debug.o evaluation_debug.o logging.o
	$(CC) $(DEBUG_FLAGS) $^ -o $@ -D ALPHA_BETA



# Debug Object files
agentInterface_debug.o: agentInterface.c agentInterface.h structures.h konane.h
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

agentInterfaceAlphaBeta_debug.o: agentInterface.c agentInterface.h structures.h konane.h
	$(CC) $(DEBUG_FLAGS) -c $< -o $@ -D ALPHA_BETA

konane_debug.o: konane.c konane.h structures.h
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

minimax_debug.o: minimax.c minimax.h structures.h konane.h evaluation.h
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

minimaxAlphaBeta_debug.o: minimaxAlphaBeta.c minimaxAlphaBeta.h structures.h konane.h evaluation.h
	$(CC) $(DEBUG_FLAGS) -c $< -o $@ -D ALPHA_BETA

evaluation_debug.o: evaluation.c evaluation.h structures.h konane.h
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

logging.o: logging.c logging.h
	$(CC) $(DEBUG_FLAGS) -c $< -o $@



# Phony targets
.PHONY: valgrind-gameDemo valgrind-agentInterface \
		gdb-gameDemo gdb-agentInterface \
		test \
		test-agentInterface-newGameB \
		test-agentInterface-newGameW \
		test-agentInterface-game1B \
		test-agentInterface-game1W \
		test-driver-random-random \
		test-driver-random-agent \
		test-driver-agent-random \
		test-driver-random-agent_ab \
		test-driver-agent-agent \
		test-driver-agent_ab-random \
		test-driver-agent-agent_ab \
		clean tar



# Debugging targets

valgrind-agentInterface:
	valgrind --leak-check=full ./agentInterface ../test/board_states/newGameB.txt B

valgrind-mem-agentInterface:
	valgrind --tool=massif ./agentInterface ../test/board_states/newGameB.txt B

gdb-agentInterface:
	gdb --args agentInterface_debug ../test/board_states/newGameB.txt B



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

test-agentInterface-blackWinsW:
	./agentInterface ../test/board_states/blackWinsW.txt W

test-agentInterface-whiteWinsB:
	./agentInterface ../test/board_states/whiteWinsB.txt B

test-agentInterface-blackDblJumpUpB:
	./agentInterface ../test/board_states/blackDblJumpUpB.txt B

test-driver-random-random:
	cd ../test && perl drivercheck.pl konanerandomplayer konanerandomplayer

test-driver-random-agent:
	cd ../test && perl drivercheck.pl konanerandomplayer ../src/agentInterface

test-driver-agent-random:
	cd ../test && perl drivercheck.pl ../src/agentInterface konanerandomplayer

test-driver-random-agent_ab:
	cd ../test && perl drivercheck.pl konanerandomplayer ../src/agentInterface_alpha_beta

test-driver-agent_ab-random:
	cd ../test && perl drivercheck.pl ../src/agentInterface_alpha_beta konanerandomplayer

test-driver-agent-agent:
	cd ../test && perl drivercheck.pl ../src/agentInterface ../src/agentInterface

test-driver-agent-agent_ab:
	cd ../test && perl drivercheck.pl ../src/agentInterface ../src/agentInterface_alpha_beta

test-driver-t3-t3:
	cd ../test && perl drivercheck.pl ../src/T3 ../src/T3



# Clean target
clean:
	rm -f $(EXE) $(OBJ) $(DEP)
	rm -f *.exe *.o *.out *_debug *.d
	rm -f *.~ .*.swo .*.swp .nfo*



# Tar target
tar:
	cd .. && tar -cvzf konane-agent-group-3.tar.gz \
	src test README.md
