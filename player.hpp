#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"

#define NUM_OTHELLO_SQUARES 8

using namespace std;

static const short HUERISTIC[NUM_OTHELLO_SQUARES][NUM_OTHELLO_SQUARES] =
{
  {  127, -064,  064,  064,  064,  064, -064,  127},
  { -064, -127, -032,  000,  000, -032, -127, -064},
  {  064, -032,  016,  016,  016,  016, -032,  064},
  {  064,  000,  016,  032,  032,  016,  000,  064},
  {  064,  000,  016,  032,  032,  016,  000,  064},
  {  064, -032,  016,  016,  016,  016, -032,  064},
  { -064, -127, -032,  000,  000, -032, -127, -064},
  {  127, -064,  064,  064,  064,  064, -064,  127}
};

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int Player::updateHueristics(Board *board);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
    // Game board pointer
    Board game_board*;
    // The side of the player
    Side player_side;
    // Valid moves
    vector<Move> valid_moves;
    // Occupied spaces
    vector<Move *> occupied_spaces;
};

#endif
