#include "player.hpp"

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

    this->player_side = side;
    this->game_board = new Board();

    // Initialize the vector of adjacents
    static const Move init_adj[] = {Move(2,2), Move(3,2), Move(4,2), Move(5,2),
                                    Move(2,3),                       Move(5,3),
                                    Move(2,4),                       Move(5,4),
                                    Move(2,5), Move(3,5), Move(4,5), Move(5,5)};
    static const short NUM_ADJACENT_INITIAL = 12;

    // Only keep valid moves and add to vector of valid moves
    for(short i = 0; i < NUM_ADJACENT_INITIAL; i++) {
      if(this->game_board->checkMove(&init_adj[i], this->player_side)) {
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
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    return nullptr;
}

/**
 * @brief Makes a random move.
 *
 */
Move *Player::randomMove() {
    /*
     * Makes a ,,random,, move. Some moves are likelier to be made...don't
     * worry about it.
     */
    int randIndex = rand() % adjacent_sq.size();
    game_board.doMove(adjacent_sq[randIndex], side);
}

/**
 * @brief Makes a non-random move determined by using MiniMax.
 *
 */
Move *Player::miniMax() {

}

/**
 * @brief Updates the list of valid adjacent moves.
 *
 */
void Player::updateAdjacents(Move *m) {

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
int Player::updateHueristics(Board *board) {
    int our_score = 0;
    int their_score = 0;
    Side player = this->player_side;
    Side opponent = (this->player_side == BLACK)? WHITE : BLACK;
    for(int i = 0; i < (int)this->occupied_spaces.size(); i++) {
      int x = this->occupied_spaces[i]->getX();
      int y = this->occupied_spaces[i]->getY();
      if(this->game_board->get(player, x, y)) {
        our_score += HUERISTIC[x][y];
      }
      else if(this->game_board->get(opponent, x, y)) {
        their_score += HUERISTIC[x][y];
      }
    }

    return out_score - their_score;
}
