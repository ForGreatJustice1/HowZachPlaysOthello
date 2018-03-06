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
    void validMoves();

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
    // Game board pointer
    Board game_board*;
    // The side of the player
    Side player_side;
    // Valid moves
    vector<Move> valid_moves;
};

#endif
