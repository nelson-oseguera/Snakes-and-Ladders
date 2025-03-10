#include "snakes.h"

// Default constructor
Snakes::Snakes()
    : m_start(nullptr), m_player1(nullptr), m_player2(nullptr), m_playerTurn(NOGAME), m_dice(1, 6, UNIFORMINT) {}

// Copy constructor
Snakes::Snakes(const Snakes& rhs)
    : m_start(nullptr), m_player1(nullptr), m_player2(nullptr), m_playerTurn(rhs.m_playerTurn), m_dice(1, 6, UNIFORMINT) {
    if (rhs.m_start) {
        // Deep copy of the board structure
        m_start = new Cell(rhs.m_start->getID());
        Cell* src = rhs.m_start->getNext();
        Cell* dest = m_start;
        while (src != nullptr) {
            Cell* newCell = new Cell(src->getID());
            dest->setNext(newCell);
            dest = newCell;
            src = src->getNext();
        }

        // Set player positions in the copied board
        m_player1 = m_start;
        m_player2 = m_start;
        Cell* srcPlayer1 = rhs.m_start;
        Cell* srcPlayer2 = rhs.m_start;
        while (srcPlayer1 != rhs.m_player1) {
            srcPlayer1 = srcPlayer1->getNext();
            m_player1 = m_player1->getNext();
        }
        while (srcPlayer2 != rhs.m_player2) {
            srcPlayer2 = srcPlayer2->getNext();
            m_player2 = m_player2->getNext();
        }
    }
}

// Destructor to clean up dynamically allocated memory
Snakes::~Snakes() {
    clear();
}

// Clear method to deallocate all dynamically allocated memory
void Snakes::clear() {
    Cell* temp;
    while (m_start != nullptr) {
        temp = m_start;
        m_start = m_start->getNext();
        delete temp;
    }
    m_start = nullptr;
    m_player1 = nullptr;
    m_player2 = nullptr;
    m_playerTurn = NOGAME;
}

// Assignment operator with deep copy logic
const Snakes& Snakes::operator=(const Snakes& rhs) {
    if (this != &rhs) {
        clear();  // Clear current contents
        if (rhs.m_start) {
            // Deep copy of the board structure
            m_start = new Cell(rhs.m_start->getID());
            Cell* src = rhs.m_start->getNext();
            Cell* dest = m_start;
            while (src != nullptr) {
                Cell* newCell = new Cell(src->getID());
                dest->setNext(newCell);
                dest = newCell;
                src = src->getNext();
            }

            // Set player positions in the copied board
            m_player1 = m_start;
            m_player2 = m_start;
            Cell* srcPlayer1 = rhs.m_start;
            Cell* srcPlayer2 = rhs.m_start;
            while (srcPlayer1 != rhs.m_player1) {
                srcPlayer1 = srcPlayer1->getNext();
                m_player1 = m_player1->getNext();
            }
            while (srcPlayer2 != rhs.m_player2) {
                srcPlayer2 = srcPlayer2->getNext();
                m_player2 = m_player2->getNext();
            }

            // Copy player turn state
            m_playerTurn = rhs.m_playerTurn;
        }
    }
    return *this;
}

// Dice roll function using the existing Random object
int Snakes::rollDice() {
    return m_dice.getRandNum();
}

// Constructor with board size parameter (modification to handle non-perfect square)
Snakes::Snakes(int boardSize)
    : m_start(nullptr), m_player1(nullptr), m_player2(nullptr), m_playerTurn(NOGAME) {
    
    // Find the largest perfect square smaller than or equal to boardSize
    int largestPerfectSquare = std::floor(std::sqrt(boardSize));
    int adjustedBoardSize = largestPerfectSquare * largestPerfectSquare;

    if (!makeDefaultBoard(adjustedBoardSize)) {
        clear();  // Clear if board creation failed
    }
}

// Make default board with random placement of snakes and ladders
bool Snakes::makeDefaultBoard(int boardSize) {
    // Find the largest perfect square smaller than or equal to boardSize
    int largestPerfectSquare = std::floor(std::sqrt(boardSize));
    boardSize = largestPerfectSquare * largestPerfectSquare;

    if (boardSize < 9) {
        return false;  // Smallest board should be 3x3
    }

    if (m_start != nullptr) {
        return false;  // Do not modify an existing board
    }

    // Create the linked list for the board
    m_start = new Cell(1);  // First cell
    Cell* current = m_start;
    for (int i = 2; i <= boardSize; i++) {
        Cell* newCell = new Cell(i);
        current->setNext(newCell);
        current = newCell;
    }

    m_player1 = m_start;
    m_player2 = m_start;
    m_playerTurn = PLAYER1TURN;  // Ensure the game starts with Player 1's turn

    // Calculate the number of snakes and ladders based on board size
    int numSnakesLadders = boardSize / 4;
    int numSnakes = numSnakesLadders / 2;
    int numLadders = numSnakesLadders - numSnakes;

    Random randPos(2, boardSize - 1);  // Snakes/Ladders between 2 and (size - 1)
    std::vector<int> usedPositions;

    // Add snakes
    for (int i = 0; i < numSnakes; i++) {
        int start, end;
        do {
            start = randPos.getRandNum();
            end = randPos.getRandNum();
        } while (start <= end || (start - end) < 3 ||
                 std::find(usedPositions.begin(), usedPositions.end(), start) != usedPositions.end() ||
                 std::find(usedPositions.begin(), usedPositions.end(), end) != usedPositions.end());

        Cell* startCell = m_start;
        Cell* endCell = m_start;
        for (int j = 1; j < start; j++) startCell = startCell->getNext();
        for (int j = 1; j < end; j++) endCell = endCell->getNext();

        if (startCell->getNorth() == nullptr && endCell->getSouth() == nullptr) {
            startCell->setSouth(endCell);
            usedPositions.push_back(start);
            usedPositions.push_back(end);
        }
    }

    // Add ladders
    for (int i = 0; i < numLadders; i++) {
        int start, end;
        do {
            start = randPos.getRandNum();
            end = randPos.getRandNum();
        } while (start >= end || (end - start) < 3 ||
                 std::find(usedPositions.begin(), usedPositions.end(), start) != usedPositions.end() ||
                 std::find(usedPositions.begin(), usedPositions.end(), end) != usedPositions.end());

        Cell* startCell = m_start;
        Cell* endCell = m_start;
        for (int j = 1; j < start; j++) startCell = startCell->getNext();
        for (int j = 1; j < end; j++) endCell = endCell->getNext();

        if (startCell->getSouth() == nullptr && endCell->getNorth() == nullptr) {
            startCell->setNorth(endCell);
            usedPositions.push_back(start);
            usedPositions.push_back(end);
        }
    }

    return true;
}

// Make random board with given number of snakes and ladders
void Snakes::makeRandomBoard(int boardSize, int numSnakesLadders) {
    clear();  // Clear current board

    int gridSize = std::sqrt(boardSize);
    if (gridSize * gridSize != boardSize) {
        return;  // Only proceed if boardSize is a perfect square
    }

    if (boardSize < 9) {
        return;  // Invalid board size
    }

    // Create the linked list for the board
    m_start = new Cell(1);  // First cell
    Cell* current = m_start;
    for (int i = 2; i <= boardSize; i++) {
        Cell* newCell = new Cell(i);
        current->setNext(newCell);
        current = newCell;
    }

    m_player1 = m_start;
    m_player2 = m_start;
    m_playerTurn = PLAYER1TURN;  // Ensure the game starts with Player 1's turn

    // Validate the number of snakes and ladders
    int minSnakesLadders = 2;
    int maxSnakesLadders = (boardSize / 2) - 2;
    if (numSnakesLadders < minSnakesLadders) numSnakesLadders = minSnakesLadders;
    if (numSnakesLadders > maxSnakesLadders) numSnakesLadders = maxSnakesLadders;

    int numSnakes = numSnakesLadders / 2;
    int numLadders = numSnakesLadders - numSnakes;

    Random randPos(2, boardSize - 1);  // Snakes/Ladders between 2 and (size - 1)
    std::vector<int> usedPositions;

    // Add snakes
    for (int i = 0; i < numSnakes; i++) {
        int start, end;
        do {
            start = randPos.getRandNum();
            end = randPos.getRandNum();
        } while (start <= end || (start - end) < 3 ||
                 std::find(usedPositions.begin(), usedPositions.end(), start) != usedPositions.end() ||
                 std::find(usedPositions.begin(), usedPositions.end(), end) != usedPositions.end());

        Cell* startCell = m_start;
        Cell* endCell = m_start;
        for (int j = 1; j < start; j++) startCell = startCell->getNext();
        for (int j = 1; j < end; j++) endCell = endCell->getNext();

        if (startCell->getNorth() == nullptr && endCell->getSouth() == nullptr) {
            startCell->setSouth(endCell);
            usedPositions.push_back(start);
            usedPositions.push_back(end);
        }
    }

    // Add ladders
    for (int i = 0; i < numLadders; i++) {
        int start, end;
        do {
            start = randPos.getRandNum();
            end = randPos.getRandNum();
        } while (start >= end || (end - start) < 3 ||
                 std::find(usedPositions.begin(), usedPositions.end(), start) != usedPositions.end() ||
                 std::find(usedPositions.begin(), usedPositions.end(), end) != usedPositions.end());

        Cell* startCell = m_start;
        Cell* endCell = m_start;
        for (int j = 1; j < start; j++) startCell = startCell->getNext();
        for (int j = 1; j < end; j++) endCell = endCell->getNext();

        if (startCell->getSouth() == nullptr && endCell->getNorth() == nullptr) {
            startCell->setNorth(endCell);
            usedPositions.push_back(start);
            usedPositions.push_back(end);
        }
    }
}

// Play function to handle dice rolls and player movement
bool Snakes::play(int dice) {
    if (m_playerTurn == NOGAME) return false;

    Cell* currentPlayer = (m_playerTurn == PLAYER1TURN) ? m_player1 : m_player2;

    for (int i = 0; i < dice && currentPlayer->getNext() != nullptr; i++) {
        currentPlayer = currentPlayer->getNext();
    }

    if (currentPlayer->getNorth() != nullptr) {
        currentPlayer = currentPlayer->getNorth();
    } else if (currentPlayer->getSouth() != nullptr) {
        currentPlayer = currentPlayer->getSouth();
    }

    if (m_playerTurn == PLAYER1TURN) {
        m_player1 = currentPlayer;
    } else {
        m_player2 = currentPlayer;
    }

    if (currentPlayer->getNext() == nullptr) {
        m_playerTurn = NOGAME;
        return false;
    }

    m_playerTurn = (m_playerTurn == PLAYER1TURN) ? PLAYER2TURN : PLAYER1TURN;
    return true;
}

// Re-initialize the game
void Snakes::reStart() {
    m_player1 = m_start;
    m_player2 = m_start;
    m_playerTurn = PLAYER1TURN;
}

// Dump board method for debugging purposes
void Snakes::dumpBoard() {
    if (m_start != nullptr) {
        int ladderCode, snakeCode;
        Cell* temp = m_start;
        cout << "START => ";
        while (temp != nullptr) {
            cout << temp->m_cellID;

            if (temp == m_player1) cout << " (Player 1)";
            if (temp == m_player2) cout << " (Player 2)";
            if (temp->m_north != nullptr) ladderCode = temp->m_north->m_cellID;
            else ladderCode = -1;
            if (temp->m_south != nullptr) snakeCode = temp->m_south->m_cellID;
            else snakeCode = -1;
            if (ladderCode != -1 || snakeCode != -1) {
                cout << " (";
                if (ladderCode != -1) cout << "\033[1;32mLadder to: " << ladderCode << "\033[0m";
                if (snakeCode != -1) cout << "\033[1;31mSnake to: " << snakeCode << "\033[0m";
                cout << ")";
            }
            cout << " => ";
            temp = temp->getNext();
        }
        cout << "END" << endl;
    }
}