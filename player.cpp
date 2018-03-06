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
    this->adjacent_sq = vector<Move>(init_adj,
      init_adj + sizeof(init_adj)/sizeof(init_adj[0]));

    return;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete game_board;
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
