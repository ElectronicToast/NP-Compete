#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

// For random move AI
#include <stdlib.h>     
#include <time.h>       
#include <algorithm>


class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

    Side playerSide;
    Side opponent;

    static const short heuristic_matrix[8][8];

    Board * boardState;

    int alphaBetaScore(Board * board, Move * move, int alpha, int beta, int depth, Side side);
    int minimaxScore(Board * board, int depth, Side side);

    int getNaiveScore(Board * board, Move * m, Side side);
    int getMobilityScore(Board* board, Move * m, Side side);

    int getNumMoves(Board * board, Side side);
    vector <Move*> getPossibleMoves(Board* board, Side side);

};

#endif
