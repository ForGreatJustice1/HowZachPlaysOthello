#include "player.hpp"

using namespace std;

// Constants
static const Move init_adj[] = {Move(2,2), Move(3,2), Move(4,2), Move(5,2),
                                Move(2,3),                       Move(5,3),
                                Move(2,4),                       Move(5,4),
                                Move(2,5), Move(3,5), Move(4,5), Move(5,5)};

static const short NUM_ADJACENT_INITIAL = 12;
static const short NUM_ADJACENT_MOVE = 8;

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 *
 * small change
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    // Set the AI type
    this->AI_type = HEURISTIC_AI;

    this->player_side = side;
    this->op_side = (side == BLACK)? WHITE : BLACK;
    this->game_board = new Board();

    // Only keep valid moves and add to vector of valid moves
    for(short i = 0; i < NUM_ADJACENT_INITIAL; i++) {
      Move m = Move(init_adj[i].x, init_adj[i].y);
      if(this->game_board->checkMove(&m, this->player_side)) {
        this->valid_moves.push_back(init_adj[i]);
      }
    }

    // Initialize list of occupied spaces
    for(short x = 0; x < NUM_OTHELLO_SQUARES; x++) {
      for(short y = 0; y < NUM_OTHELLO_SQUARES; y++) {
        if(this->game_board->get(WHITE, x, y) ||
         this->game_board->get(BLACK, x, y)) {
           this->occupied_spaces.push_back(new Move(x, y));
         }
      }
    }

    return;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete game_board;

    for(int i = 0; i < (int)this->occupied_spaces.size(); i++) {
      delete occupied_spaces[i];
    }
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {

    this->updateTheirMove(opponentsMove);

    // Case where no valid moves.
    if(valid_moves.size() == 0) {
      return nullptr;
    }

    int ourMoveIndex;

    // Figure out what AI to use
    if(testingMinimax) {
      ourMoveIndex = this->miniMax();
    }
    else {
      switch(this->AI_type) {
        case RANDOM_AI:
        {
          ourMoveIndex = this->randomMove();
          break;
        }
        case HEURISTIC_AI:
        {
          ourMoveIndex = this->heuristicsAI();
          break;
        }
        case MINIMAX_AI:
        {
          ourMoveIndex = this->miniMax();
          break;
        }
        case FLAT_AI:
        {
          ourMoveIndex = this->flatEarthHeuristicAI();
          break;
        }
        default:
        {
          ourMoveIndex = this->randomMove();
          break;
        }
      }
    }

    this->updateOurMove(ourMoveIndex);

    // Copy the move and return pointer.
    int move_x = this->valid_moves[ourMoveIndex].getX();
    int move_y = this->valid_moves[ourMoveIndex].getY();
    return new Move(move_x, move_y);
}

/**
 * @brief Makes a random move.
 *
 */
int Player::randomMove() {
    /*
     * Picks a ,,random,, move. Some moves are likelier to be made...don't
     * worry about it.
     */
    int randIndex = rand() % valid_moves.size();
    return randIndex;
}

/**
* @brief Uses heuristics to make the immediate best move.
*
*/
int Player::heuristicsAI() {
    int hScore = -1000;
    int currentScore;
    int hIndex;
    for(int i = 0; i < (int)valid_moves.size(); i++) {
      Board* newCopy = this->game_board->copy();
      newCopy->doMove(&valid_moves[i], this->player_side);
      this->occupied_spaces.push_back(&valid_moves[i]);
      currentScore = updateHeuristics(newCopy, this->occupied_spaces);
      this->occupied_spaces.pop_back();
      if(currentScore > hScore) {
        hIndex = i;
        hScore = currentScore;
      }
      delete newCopy;
    }

    return hIndex;
}

/**
* @brief Uses heuristics to make the immediate best move.
*
*/
int Player::flatEarthHeuristicAI() {
    int hScore = -1000;
    int currentScore;
    int hIndex;
    for(int i = 0; i < (int)valid_moves.size(); i++) {
      int x = valid_moves[i].getX();
      int y = valid_moves[i].getY();
      currentScore = flatHeuristic(x,y);
      if(currentScore > hScore) {
        hIndex = i;
        hScore = currentScore;
      }
    }

    return hIndex;
}

/**
 * @brief Makes a non-random move determined by using MiniMax.
 *
 */
int Player::miniMax() {
  return 0;
}

/**
 * @brief Updates the list of valid adjacent moves after our move.
 *
 */
void Player::updateOurMove(int index) {

    int x = valid_moves[index].getX();
    int y = valid_moves[index].getY();

    // Update Move List and board
    Move *m = new Move(x, y);
    this->game_board->doMove(m, this->player_side);
    this->updateMoves(m);
}

/**
 * @brief Updates the list of valid adjacent moves after their move.
 *
 */
void Player::updateTheirMove(Move *m) {

    // Clear valid moves
    this->valid_moves.erase(valid_moves.begin(), valid_moves.end());

    // Update moves
    if(m != nullptr) {

      int x = m->getX();
      int y = m->getY();

      Move *move = new Move(x, y);
      this->game_board->doMove(move, this->op_side);
      this->updateMoves(move);
    }

    // Update Move List

    for(short x = 0; x < NUM_OTHELLO_SQUARES; x++) {
      for(short y = 0; y < NUM_OTHELLO_SQUARES; y++) {
        Move *m = new Move(x, y);
        if(this->game_board->checkMove(m, this->player_side)) {
           this->valid_moves.push_back(Move(x, y));
        }
        delete m;
      }
    }
}

/**
 * @brief Updates the moves list.
 *
 */
void Player::updateMoves(Move *m) {
    this->occupied_spaces.push_back(new Move(m->getX(), m->getY()));
    return;
}

/**
 * @brief Calculates the heuristic
 *
 * @return The hueristic function's value given a board state.
 */
int Player::updateHeuristics(Board *board, vector<Move *> token_spaces) {
    int our_score = 0;
    int their_score = 0;

    for(int i = 0; i < (int)token_spaces.size(); i++) {

      int x = token_spaces[i]->getX();
      int y = token_spaces[i]->getY();

      if(board->get(this->player_side, x, y)) {
        our_score += HEURISTIC[x][y];
      }
      else if(board->get(this->op_side, x, y)) {
        their_score += HEURISTIC[x][y];
      }
    }

    return our_score - their_score;
}

int Player::flatHeuristic(int x, int y) {
    return HEURISTIC[x][y];
}

/**
 * @brief Calculates a simple heuristic
 *
 * @return The hueristic function's value given a board state.
 */
int Player::superDumbSuperSimpleHeuristic(Board *board) {
    if(this->player_side == BLACK){
      return board->countBlack() - board->countWhite();
    }
    return board->countWhite() - board->countBlack();
}
