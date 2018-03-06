#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"

#define NUM_OTHELLO_SQUARES 8

using namespace std;

static const short HEURISTIC[NUM_OTHELLO_SQUARES][NUM_OTHELLO_SQUARES] =
{
  {  255,  -64,   32,   16,   16,   32,  -64,  255},
  {  -64, -128,   32,    4,    4,   32, -128,  -64},
  {   32,   32,   32,    4,    4,   32,   32,   32},
  {   16,    4,    4,    4,    4,    4,    4,   16},
  {   16,    4,    4,    4,    4,    4,    4,   16},
  {   32,   32,   32,    4,    4,   32,   32,   32},
  {  -64, -128,   32,    4,    4,   32, -128,  -64},
  {  255,  -64,   32,   16,   16,   32,  -64,  255}
};

/**
 * @brief Tells what type of AI to use.
 */
typedef enum AI {
  RANDOM_AI,
  HEURISTIC_AI,
  MINIMAX_AI,
  FLAT_AI
} AI_t;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    int updateHeuristics(Board *board, vector<Move *> token_spaces);
    int superDumbSuperSimpleHeuristic(Board *board);
    void updateMoves(Move *m);
    void updateOurMove(int index);
    void updateTheirMove(Move *m);
    void clearNeighborsFromMoves(int x, int y);
    int flatHeuristic(int x, int y);

    int randomMove();
    int heuristicsAI();
    int flatEarthHeuristicAI();
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
