# <u>Konane Agent Term Project</u>

KonaneTermProject is a Grant MacEwan CMPT 355 AS01 2024 Term Project designed by Aiden Lumley, Ayden Hogeveen, Davin Han, and Kevin Ulliac, with Course Instructor Calin Anton. This term project consists of designing an agent that plays a hawaiian board game. Using adversarial search taught in class, such as the min max algorithm and alpha beta pruning, to design an efficient and rational agent. The agent takes performance measure from winning game states, number of jumps possible, the number of valid moves, the number of nodes, and the number of pieces to perform moves that are strategically the best.


### <u>make commands</u>:

**all:** Builds the release version of the executables (agentInterface, agentInterfaceAlphaBeta). The release version includes optimization and no debugging symbols, thus no logging features.

- Usage: `make all`

**debug**: Builds the debug version of the executables (agentInterface_debug, agentInterfaceAlphaBeta_debug). The debug version does not include optimization, but includes debugging symbols (such as the -g flag for use with gdb) and logging features.

- Usage: `make debug`

**valgrind-agentInterface**: Runs valgrind for memory leak checking on agentInterface.

- Usage: `make valgrind-agentInterface`

**gdb-agentInterface**: Runs gdb for debugging agentInterface_debug.

- Usage: `make gdb-agentInterface`

**test**: Runs a test case.

- Usage: `make test`

**test-agentInterface-***: Runs specific test cases for agentInterface with different board states.

- Usage: `make test-agentInterface-newGameB`

**test-driver-***: Runs test drivers for various combinations of players and agents.

- Usage: `make test-driver-random-random`

**clean**: Removes all generated files and executables.

- Usage: `make clean`

**tar**: Creates a compressed tarball of your project.

- Usage: `make tar`
<br></br>
---

### <u>Project Structure</u>:

The project is structured as follows:
- **`src/`**: Contains the source code for the project.
- **`test/`"**: Contains the driver, konanerandomplayer, knmv (Konane Move Validator), and test cases for the project, which is separated into two folders:
    - `board_states/`: A collection of board states at different points in the game. Some board states have a clear best move (such as double jumps), while others are simply a new board, or two moves away from a certain win.
    - `demo_files/`: A collection of board states supplied with the driver and knmv and random player.
<br></br>
---
### <u>Reference List</u>

1. Anton, C. (2024, Jan 21-28) Heuristic Search [Slide Presentation]. CMPT 355: Introduction to Artificial Intelligence, Edmonton, AB. Canada
2. Anton, C. (2024, Feb 1-7) Adversarial Search [Slide Presentation]. CMPT 355: Introduction to Artificial Intelligence, Edmonton, AB. Canada
3. Ernst, M. D. (1995). Playing Konane Mathematically: A Combinatorial Game-Theoretic Analysis. UMAP Journal, 16(2). https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=532fc4499a110b79b190e62e23de49c1c51b3f6f
4. pthreads explained. (n.d.). ai-jobs.net. https://ai-jobs.net/insights/pthreads-explained/ 
5. Ting, G., & Winters, K. (1991). Konane. Cricket, 18(5), 21.