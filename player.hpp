#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"

#define CORNER_WT       3
#define X_WT            -5
#define C_WT            -2
#define EDGE_WT         1
                  
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

protected:
    Side opponent;
    Board boardState;

    char[][] weights;
};

#endif
