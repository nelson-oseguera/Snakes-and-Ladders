#ifndef SNAKES_H
#define SNAKES_H

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>     // Used to get the current time
using namespace std;

class Grader; // This class is for grading purposes, no need to do anything
class Tester; // This is your tester class, you add your test functions in this class
class Snakes;

const int NOGAME = 0;
const int PLAYER1TURN = 1;
const int PLAYER2TURN = 2;
enum RANDOM { UNIFORMINT, UNIFORMREAL, NORMAL, SHUFFLE };

class Random {
public:
    Random() {}
    Random(int min, int max, RANDOM type = UNIFORMINT, int mean = 50, int stdev = 20)
        : m_min(min), m_max(max), m_type(type) {
        if (type == NORMAL) {
            m_generator = std::mt19937(m_device());
            m_normdist = std::normal_distribution<>(mean, stdev);
        } else if (type == UNIFORMINT) {
            m_generator = std::mt19937(10); // 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min, max);
        } else if (type == UNIFORMREAL) {
            m_generator = std::mt19937(10); // 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min, (double)max);
        } else {
            m_generator = std::mt19937(m_device());
        }
    }
    void setSeed(int seedNum) {
        m_generator = std::mt19937(seedNum);
    }
    void init(int min, int max) {
        m_min = min;
        m_max = max;
        m_type = UNIFORMINT;
        m_generator = std::mt19937(10);
        m_unidist = std::uniform_int_distribution<>(min, max);
    }
    void getShuffle(vector<int>& array) {
        for (int i = m_min; i <= m_max; i++) {
            array.push_back(i);
        }
        shuffle(array.begin(), array.end(), m_generator);
    }
    void getShuffle(int array[]) {
        vector<int> temp;
        for (int i = m_min; i <= m_max; i++) {
            temp.push_back(i);
        }
        std::shuffle(temp.begin(), temp.end(), m_generator);
        vector<int>::iterator it;
        int i = 0;
        for (it = temp.begin(); it != temp.end(); it++) {
            array[i] = *it;
            i++;
        }
    }
    int getRandNum() {
        int result = 0;
        if (m_type == NORMAL) {
            result = m_min - 1;
            while (result < m_min || result > m_max)
                result = m_normdist(m_generator);
        } else if (m_type == UNIFORMINT) {
            result = m_unidist(m_generator);
        }
        return result;
    }
    double getRealRandNum() {
        double result = m_uniReal(m_generator);
        result = std::floor(result * 100.0) / 100.0;
        return result;
    }
    string getRandString(int size) {
        string output = "";
        for (int i = 0; i < size; i++) {
            output = output + (char)getRandNum();
        }
        return output;
    }
    int getMin() { return m_min; }
    int getMax() { return m_max; }
private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;
    std::uniform_int_distribution<> m_unidist;
    std::uniform_real_distribution<double> m_uniReal;
};

class Cell {
public:
    friend class Grader;
    friend class Tester;
    friend class Snakes;
    Cell() : m_cellID(0), m_next(nullptr), m_north(nullptr), m_south(nullptr) {}
    Cell(int id) : m_cellID(id), m_next(nullptr), m_north(nullptr), m_south(nullptr) {}
    ~Cell() {}
    void setID(int id) { m_cellID = id; }
    int getID() { return m_cellID; }
    void setNorth(Cell* aNode) { m_north = aNode; }
    Cell* getNorth() { return m_north; }
    void setSouth(Cell* aNode) { m_south = aNode; }
    Cell* getSouth() { return m_south; }
    void setNext(Cell* aNode) { m_next = aNode; }
    Cell* getNext() { return m_next; }
private:
    int m_cellID;
    Cell* m_next;
    Cell* m_north;
    Cell* m_south;
};

class Snakes {
public:
    friend class Grader;
    friend class Tester;
    Snakes();
    Snakes(int boardSize);
    Snakes(const Snakes& rhs); // Copy constructor
    ~Snakes();
    void clear();
    int rollDice();
    bool play(int dice);
    void reStart();
    bool makeDefaultBoard(int boardSize);
    void makeRandomBoard(int boardSize, int numSnakesLadders);
    int whoseTurn() { return m_playerTurn; }
    void dumpBoard();
    const Snakes& operator=(const Snakes& rhs); // Assignment operator
private:
    Cell* m_start;
    Random m_dice;
    Cell* m_player1;
    Cell* m_player2;
    int m_playerTurn;

    /******************************************
    * Private function declarations go here! *
    ******************************************/

};

#endif