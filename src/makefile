# Variables
CC = gcc
CFLAGS = -Wall -std=c99 -MMD
DEBUGFLAGS = -g
RELEASEFLAGS = -O2

# Files and dependencies
EXE = gameDemo agentInterface gameDemo_count_bw agentInterface_count_bw
DBG = $(EXE:=_debug)
SRC = gameDemo.c agentInterface.c konane.c minimaxAgent.c
OBJ = $(SRC:.c=.o) minimaxAgent_count_bw.o
DEBUG_OBJ = $(OBJ:%.o=%_debug.o)
DEP = $(OBJ:.o=.d)

# Release Targets
all: CFLAGS += $(RELEASEFLAGS)
all: $(EXE)

# Pattern rule for building executables
%: %.o konane.o minimaxAgent.o
	$(CC) $(CFLAGS) $^ -o $@

# Pattern rule for building executables with the count_bw evaluation function
%_count_bw: %.o konane.o minimaxAgent_count_bw.o
	$(CC) $(CFLAGS) $^ -o $@

# Debug Targets
debug: CFLAGS += $(DEBUGFLAGS)
debug: $(DBG)

# Pattern rule for building debug executables
$(filter-out %_count_bw_debug, $(DBG)): %_debug: %.o konane.o minimaxAgent.o
	$(CC) $(CFLAGS) $^ -o $@

$(filter %_count_bw_debug, $(DBG)): %_count_bw_debug: %.o konane.o minimaxAgent_count_bw.o
	$(CC) $(CFLAGS) $^ -o $@

# Pattern rule for building object files
$(filter-out %_count_bw.o, $(OBJ)): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rule for building object files with the count_bw evaluation function
$(filter %_count_bw.o, $(OBJ)): %_count_bw.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -D EVAL_COUNT_BW

# Pattern rule for building debug object files
$(filter-out %_count_bw_debug.o, $(DEBUG_OBJ)): %_debug.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -D DEBUG

# Pattern rule for building debug object files with the count_bw evaluation function
$(filter %_count_bw_debug.o, $(DEBUG_OBJ)): %_count_bw_debug.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -D DEBUG -D EVAL_COUNT_BW

# Pattern rule for building dependency files
%.d: %.c
	$(CC) -MM $< -o $@

# Include dependency files
-include $(DEP)

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

test-driver-agent-agent-count-bw:
	cd ../test && perl drivercheck.pl ../src/agentInterface ../src/agentInterface_count_bw

# Clean target
clean:
	rm -f $(EXE) $(OBJ) $(DEP)
	rm -f *.exe *.o *.out
	rm -f *_debug
	rm -f *.d
	rm -f *.~ .*.swo .*.swp .nfo*

# Tar target
tar:
	tar -cvzf ../gameDemo.tar.gz -C ../ konane-term-project
	tar -cvzf ../agentInterface.tar.gz -C ../ konane-term-project
