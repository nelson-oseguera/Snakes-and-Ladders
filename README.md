# Snakes-and-Ladders

This project is a C++ implementation of the Snakes and Ladders game, designed as an object-oriented and fully dynamic system. The game board is modeled as a linked list of cells, with randomized placement of snakes and ladders, supporting 2-player gameplay, and full memory safety via deep copies and destructors. The code includes a custom Random generator, linked-cell board creation, and robust player movement logic.

Core Features

1. Dynamic Game Board (Linked List Design)
The board is created dynamically as a linked list of cells, where:
Each cell may contain a snake (down link) or a ladder (up link).
Each player advances on the board based on dice rolls.
Board size is customizable, automatically adjusting non-perfect square sizes to the nearest smaller square.

2. Object-Oriented Class Design (Snakes, Cell, Random)
Cell Class:
Represents each cell on the board.
Supports:
Links to next cell.
North (ladder) and South (snake) links.
Snakes Class:
Manages the game logic and players.
Attributes:
m_start: Pointer to the start of the board.
m_player1, m_player2: Pointers to player positions.
m_playerTurn: Enum tracking whose turn it is.
m_dice: Random dice roller.
Key Methods:
Snakes(), Snakes(int): Constructors (empty and board-creating).
~Snakes(): Destructor to free memory.
clear(): Deallocate current board.
makeDefaultBoard(int): Generates default board with balanced snakes and ladders.
makeRandomBoard(int, int): Custom board creation with user-defined snake/ladder count.
play(int): Moves the current player according to dice roll.
reStart(): Resets game without changing board.
dumpBoard(): Prints board with player positions, snakes, and ladders.
rollDice(): Returns a random dice roll (1-6).
operator=, Snakes(const Snakes&): Deep copy constructors and assignment operators for safe copying.
Random Class:
Custom random number generator for board creation and dice rolls.
Supports uniform integer/real and normal distributions.

3. Gameplay Mechanics
2 players, alternating turns.
Snakes and ladders dynamically positioned with proper constraints:
No overlaps, minimum gap distance, no snake/ladder to start or end cell.
Valid dice moves:
Advance by dice value.
If landing on a ladder's bottom, climb.
If landing on a snake's head, slide down.
Winning occurs when reaching the last cell.

4. Memory Safety and Copying
Deep copies for Snakes objects ensure independent game copies.
Destructor and clear() to prevent memory leaks.
Handles edge cases like empty games or assigning empty to filled games.

5. Testing Framework (Tester Class)
Includes automated unit tests for:

Test	Purpose
testAlternativeConstructorNormal	Standard board creation
testAlternativeConstructorError	Non-square size adjustment
testReStart	Game reset after moves
testPlayLadder	Correct climbing of ladders
testPlaySnake	Correct sliding down snakes
testMakeDefaultBoardNormal	Board creation success
testMakeRandomBoardNormal	Custom board creation with defined count
testMakeRandomBoardError	Error handling for excess snakes/ladders
testAssignmentOperatorNormal	Deep copy by assignment
testAssignmentOperatorEdge	Assign empty game over existing board
