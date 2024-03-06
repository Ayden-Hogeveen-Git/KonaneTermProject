# Variables
CC = gcc
CFLAGS = -Wall -std=c99
DEBUGFLAGS = $(CFLAGS) -g -MMD
RELEASEFLAGS = $(CFLAGS) -O2 -MMD

# Source files
SRC = gameDemo.c agentInterface.c konane.c minimaxAgent.c

# Executables, object files, and dependency files
EXE = gameDemo agentInterface gameDemo_alpha_beta agentInterface_alpha_beta
OBJ = $(SRC:.c=.o) minimaxAgent_alpha_beta.o
DEP = $(OBJ:.o=.d)

# Debug executables, debug object files, and debug dependency files
DEBUG = $(EXE:=_debug)
DEBUG_OBJ = $(OBJ:%.o=%_debug.o)
DEBUG_DEP = $(DEBUG_OBJ:.o=.d)

# Release Targets
all: $(EXE)

# Pattern rule for building executables
%: %.o konane.o minimaxAgent.o
	$(CC) $(RELEASEFLAGS) $^ -o $@

%_alpha_beta: %.o konane.o minimaxAgent_alpha_beta.o
	$(CC) $(RELEASEFLAGS) $^ -o $@

# Pattern rule for building object files
$(filter-out %_alpha_beta.o, $(OBJ)): %.o: %.c
	$(CC) $(RELEASEFLAGS) -c $< -o $@

$(filter %_alpha_beta.o, $(OBJ)): %_alpha_beta.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -D ALPHA_BETA

# Debug Targets
debug: $(DEBUG)

# Pattern rule for building debug executables
$(filter-out %_alpha_beta_debug, $(DEBUG)): %_debug: %_debug.o konane_debug.o minimaxAgent_debug.o
	$(CC) $(DEBUGFLAGS) $^ -o $@ -D DEBUG

$(filter %_alpha_beta_debug, $(DEBUG)): %_alpha_beta_debug: %_debug.o konane_debug.o minimaxAgent_alpha_beta_debug.o
	$(CC) $(DEBUGFLAGS) $^ -o $@ -D DEBUG -D ALPHA_BETA

# Pattern rule for building debug object files
$(filter-out %_alpha_beta_debug.o, $(DEBUG_OBJ)): %_debug.o: %.c
	$(CC) $(DEBUGFLAGS) -c $< -o $@ -D DEBUG

$(filter %_alpha_beta_debug.o, $(DEBUG_OBJ)): %_alpha_beta_debug.o: %.c
	$(CC) $(DEBUGFLAGS) -c $< -o $@ -D DEBUG -D ALPHA_BETA

# Pattern rule for building dependency files
# %.d: %.c
# $(CC) -MM $< -o $@

# Include dependency files
-include $(DEP)
-include $(DEBUG_DEP)

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
valgrind-gameDemo:
	valgrind --leak-check=full ./gameDemo

valgrind-agentInterface:
	valgrind --leak-check=full ./agentInterface ../test/board_states/newGameB.txt B

valgrind-mem-gameDemo:
	valgrind --tool=massif ./gameDemo

valgrind-mem-agentInterface:
	valgrind --tool=massif ./agentInterface ../test/board_states/newGameB.txt B

gdb-gameDemo:
	gdb --args gameDemo_debug

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

# Clean target
clean:
	rm -f $(EXE) $(OBJ) $(DEP)
	rm -f $(DEBUG) $(DEBUG_OBJ) $(DEBUG_DEP)
	rm -f *.exe *.o *.out
	rm -f *_debug
	rm -f *.d
	rm -f *.~ .*.swo .*.swp .nfo*

# Tar target
tar:
	tar -cvzf ../gameDemo.tar.gz -C ../ konane-term-project
	tar -cvzf ../agentInterface.tar.gz -C ../ konane-term-project
