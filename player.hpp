#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int randomMove();
    Move *miniMax();
    void updateOurMove(int index);
    void updateTheirMove(Move *m)

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
    Board game_board*;
    Side player_side;
    vector<Move> adjacent_sq;
};

#endif
