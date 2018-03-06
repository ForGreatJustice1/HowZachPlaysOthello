#include "player.hpp"

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
    this->AI_type = RANDOM_AI;

    this->player_side = side;
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
        }
        case HEURISTIC_AI:
        {
          ourMoveIndex = this->heuristicsAI();
        }
        case MINIMAX_AI:
        {
          ourMoveIndex = this->miniMax();
        }
        default:
        {
          ourMoveIndex = this->randomMove();
          break;
        }
      }
    }

    this->updateOurMove(ourMoveIndex);
    return &(this->valid_moves[ourMoveIndex]);
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
    int hScore = -10000;
    int currentScore;
    int hIndex;
    for(int i = 0; i < (int)valid_moves.size(); i++) {
      Board* newCopy = this->game_board->copy();
      newCopy->doMove(&valid_moves[i], this->player_side);
      currentScore = updateHeuristics(newCopy);
      if(currentScore > hScore) {
        hIndex = i;
        hScore = currentScore;
      }
      delete newCopy;
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

    // Update Move List
    this->updateMoves(new Move(x, y));

    // Update Adj.
    valid_moves.erase(valid_moves.begin() + index);
    Move adj[] = {Move(x-1,y-1), Move(x,y-1), Move(x+1,y-1),
                  Move(x-1,y),                Move(x+1,y),
                  Move(x-1,y+1), Move(x,y+1), Move(x+1,y+1)};
    for(short i = 0; i < NUM_ADJACENT_MOVE; i++) {
      if(game_board->onBoard(adj[i].getX(), adj[i].getY())) {
        if(game_board->checkMove(&adj[i], this->player_side)) {
          this->valid_moves.push_back(adj[i]);
        }
      }
    }
}

/**
 * @brief Updates the list of valid adjacent moves after their move.
 *
 */
void Player::updateTheirMove(Move *m) {
    int x = m->getX();
    int y = m->getY();

    // Update Move List
    this->updateMoves(new Move(x, y));

    // Update adjacents
    Move adj[] = {Move(x-1,y-1), Move(x,y-1), Move(x+1,y-1),
                  Move(x-1,y),                Move(x+1,y),
                  Move(x-1,y+1), Move(x,y+1), Move(x+1,y+1)};
    for(short i = 0; i < NUM_ADJACENT_MOVE; i++) {
      if(game_board->onBoard(adj[i].getX(), adj[i].getY())) {
        if(game_board->checkMove(&adj[i], this->player_side)) {
          this->valid_moves.push_back(adj[i]);
        }
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
int Player::updateHeuristics(Board *board) {
    int our_score = 0;
    int their_score = 0;
    Side player = this->player_side;
    Side opponent = (this->player_side == BLACK)? WHITE : BLACK;
    for(int i = 0; i < (int)this->occupied_spaces.size(); i++) {
      int x = this->occupied_spaces[i]->getX();
      int y = this->occupied_spaces[i]->getY();
      if(this->game_board->get(player, x, y)) {
        our_score += HEURISTIC[x][y];
      }
      else if(this->game_board->get(opponent, x, y)) {
        their_score += HEURISTIC[x][y];
      }
    }

    return our_score - their_score;
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
