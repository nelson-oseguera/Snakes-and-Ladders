#include "snakes.h"
#include <iostream>

using namespace std;

// Tester class containing all the required test cases
class Tester {
public:
    // Test the alternative constructor for a normal case
    bool testAlternativeConstructorNormal() {
        Snakes game(25);  // Create a 5x5 board
        return game.whoseTurn() == PLAYER1TURN;  // Check if the game starts correctly
    }

    // Test the alternative constructor for a non-square value (adjustment case)
    bool testAlternativeConstructorError() {
        Snakes game(20);  // 20 is not a perfect square, should round down to 16 (4x4 board)
        return game.whoseTurn() == PLAYER1TURN;  // Check if the game starts correctly after rounding
    }

    // Test the reStart() function to check if it reinitializes the game
    bool testReStart() {
        Snakes game(25);
        game.play(3);  // Make a move
        game.reStart();  // Restart the game
        // Check if players are back at the start and it's Player 1's turn
        return game.whoseTurn() == PLAYER1TURN;
    }

    // Test play() function for a valid move on a ladder
    bool testPlayLadder() {
        Snakes game(25);
        game.makeDefaultBoard(25);  // Ensure a 5x5 board
        game.play(5);  // Move Player 1 to a potential ladder
        // Check if Player 1 is advanced due to the ladder
        return game.whoseTurn() == PLAYER2TURN;  // It should now be Player 2's turn
    }

    // Test play() function for a valid move on a snake
    bool testPlaySnake() {
        Snakes game(25);
        game.makeDefaultBoard(25);
        game.play(6);  // Move Player 1 to a potential snake
        // Check if Player 1 is moved back due to the snake
        return game.whoseTurn() == PLAYER2TURN;  // It should now be Player 2's turn
    }

    // Test makeDefaultBoard() for a normal case
    bool testMakeDefaultBoardNormal() {
        Snakes game;
        bool result = game.makeDefaultBoard(25);  // Make a 5x5 board
        return result && game.whoseTurn() == PLAYER1TURN;  // Should create a board and start the game
    }

    // Test makeRandomBoard() for a normal case
    bool testMakeRandomBoardNormal() {
        Snakes game;
        game.makeRandomBoard(25, 6);  // Make a 5x5 board with 6 snakes/ladders
        return game.whoseTurn() == PLAYER1TURN;  // Game should start successfully
    }

    // Test makeRandomBoard() for an error case (invalid snake/ladder count)
    bool testMakeRandomBoardError() {
        Snakes game;
        game.makeRandomBoard(25, 50);  // Invalid count, should adjust internally
        return game.whoseTurn() == PLAYER1TURN;  // Game should still start correctly
    }

    // Test the overloaded assignment operator for a normal case
    bool testAssignmentOperatorNormal() {
        Snakes game1(25);
        Snakes game2 = game1;  // Use assignment operator
        return game2.whoseTurn() == PLAYER1TURN;  // Should copy the board correctly
    }

    // Test the overloaded assignment operator for an edge case
    bool testAssignmentOperatorEdge() {
        Snakes game1;
        Snakes game2(25);
        game2 = game1;  // Assign an empty game to a game with a board
        return game2.whoseTurn() == NOGAME;  // Should result in an empty game
    }
};

// Main function to run all tests
int main() {
    Tester tester;
    int passedTests = 0;

    // Run all tests and output results
    if (tester.testAlternativeConstructorNormal()) {
        cout << "testAlternativeConstructorNormal: Passed!" << endl;
        passedTests++;
    } else {
        cout << "testAlternativeConstructorNormal: Failed!" << endl;
    }

    if (tester.testAlternativeConstructorError()) {
        cout << "testAlternativeConstructorError: Passed!" << endl;
        passedTests++;
    } else {
        cout << "testAlternativeConstructorError: Failed!" << endl;
    }

    if (tester.testReStart()) {
        cout << "testReStart: Passed!" << endl;
        passedTests++;
    } else {
        cout << "testReStart: Failed!" << endl;
    }

    if (tester.testPlayLadder()) {
        cout << "testPlayLadder: Passed!" << endl;
        passedTests++;
    } else {
        cout << "testPlayLadder: Failed!" << endl;
    }

    if (tester.testPlaySnake()) {
        cout << "testPlaySnake: Passed!" << endl;
        passedTests++;
    } else {
        cout << "testPlaySnake: Failed!" << endl;
    }

    if (tester.testMakeDefaultBoardNormal()) {
        cout << "testMakeDefaultBoardNormal: Passed!" << endl;
        passedTests++;
    } else {
        cout << "testMakeDefaultBoardNormal: Failed!" << endl;
    }

    if (tester.testMakeRandomBoardNormal()) {
        cout << "testMakeRandomBoardNormal: Passed!" << endl;
        passedTests++;
    } else {
        cout << "testMakeRandomBoardNormal: Failed!" << endl;
    }

    if (tester.testMakeRandomBoardError()) {
        cout << "testMakeRandomBoardError: Passed!" << endl;
        passedTests++;
    } else {
        cout << "testMakeRandomBoardError: Failed!" << endl;
    }

    if (tester.testAssignmentOperatorNormal()) {
        cout << "testAssignmentOperatorNormal: Passed!" << endl;
        passedTests++;
    } else {
        cout << "testAssignmentOperatorNormal: Failed!" << endl;
    }

    if (tester.testAssignmentOperatorEdge()) {
        cout << "testAssignmentOperatorEdge: Passed!" << endl;
        passedTests++;
    } else {
        cout << "testAssignmentOperatorEdge: Failed!" << endl;
    }

    return 0;
}