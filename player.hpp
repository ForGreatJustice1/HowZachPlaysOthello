#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"

#define NUM_OTHELLO_SQUARES 8

using namespace std;

static const short HEURISTIC[NUM_OTHELLO_SQUARES][NUM_OTHELLO_SQUARES] =
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

/**
 * @brief Tells what type of AI to use.
 */
typedef enum AI {
  RANDOM_AI,
  HEURISTIC_AI,
  MINIMAX_AI
} AI_t;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    int updateHeuristics(Board *board);
    int superDumbSuperSimpleHeuristic(Board *board);
    void updateMoves(Move *m);
    void updateOurMove(int index);
    void updateTheirMove(Move *m);
    void clearNeighborsFromMoves(int x, int y);

    int randomMove();
    int heuristicsAI();
    int miniMax();


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    // Type of AI to use normally
    AI_t AI_type;

private:
    // The Game Board
    Board *game_board;
    // The Player's side
    Side player_side;
    // The Opponent's side
    Side op_side;
    // Valid moves
    std::vector<Move> valid_moves;
    // Occupied spaces
    std::vector<Move *> occupied_spaces;
};

#endif
