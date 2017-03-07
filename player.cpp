#include "player.hpp"

/*
 * Beep! - Ray
 */

/*
 * Hello! - Karthik
 */

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    // Set player and opponent sides
    playerSide = side;

    if (side == WHITE)
        opponent = BLACK;
    else
        opponent = WHITE;

    boardState = new Board();

}

/*
 * Destructor for the player.
 */
Player::~Player() {
}


const int Player::heuristic_matrix[8][8] = {{120, -20, 20, 5, 5, 20, -20, 120},
                              {-20, -40, -5, -5, -5, -5, -40, -20},
                              {20, -5, 15, 3, 3, 15, -5, 20},
                              {5, -5, 3, 3, 3, 3, -5, 5},
                              {5, -5, 3, 3, 3, 3, -5, 5},
                              {20, -5, 15, 3, 3, 15, -5, 20},
                              {-20, -40, -5, -5, -5, -5, -40, -20},
                              {120, -20, 20, 5, 5, 20, -20, 120}};
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

    /*

    // Update internal board representation
    boardState->doMove(opponentsMove, opponent);

    // Make a random move
    vector<Move> possibleMoves;

    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            Move m(i, j);
            if (boardState->checkMove(&m, playerSide))
                possibleMoves.push_back(m);
        }
    }

    if (possibleMoves.size() == 0)
        return nullptr;

    srand(time(NULL));
    Move temp = possibleMoves[rand() % possibleMoves.size()];
    Move * theMove = new Move(temp.getX(), temp.getY());

    boardState->doMove(theMove, playerSide);
    
    return theMove;

    */

    ///////////////////////////////////////////////////
    // HEURISTIC IMPLEMENTATION ///////////////////////
    ///////////////////////////////////////////////////
    /*

    boardState -> doMove(opponentsMove, opponent);

    if (!boardState->hasMoves(playerSide))
    {
        return NULL;
    }

    Move * goodMove = NULL;

    int maxScore = -100;
    int currScore = 0;

    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            Move * m = new Move(i, j);
            if (boardState->checkMove(m, playerSide))
            {
                currScore = heuristic_matrix[i][j];

                if (currScore > maxScore)
                {
                    maxScore = currScore;
                    goodMove = m;
                }

                else
                {
                    delete m;
                }
            }
        }
    }

    boardState->doMove(goodMove, playerSide);
    
    return goodMove;

    */

    if (!boardState->hasMoves(playerSide))
    {
        return NULL;
    }

    vector <Move *> possibleMoves = boardState->getPossibleMoves(playerSide);
    int score = 0;
    Move * goodMove = possibleMoves[0];
    int maxScore = boardState->getScore(goodMove, playerSide);


    if (possibleMoves.size() == 0)
    {
        return NULL;
    }

    else
    {
        for (unsigned int i = 1; i < possibleMoves.size(); i++)
        {
            score = minimaxScore(boardState, 2, playerSide);

            if (score > maxScore)
            {
                goodMove = possibleMoves[i];
                maxScore = score;
            }

        }
    }

    for (unsigned int i = 0; i < possibleMoves.size(); i++)
    {
        if (possibleMoves[i] != goodMove)
        {
            delete possibleMoves[i];
        }
    }

    boardState->doMove(goodMove, playerSide);
    return goodMove;

}

int Player::minimaxScore(Board * board, int depth, Side side){

    vector <Move *> possibleMoves = board->getPossibleMoves(side);
    int score = 0;
    int maxScore = -65;

    Side other = side==BLACK? WHITE:BLACK;

    if (possibleMoves.size() == 0 || depth <= 0)
    {
        cerr << "testing base case" << endl;

        return board->getScore(nullptr, side);
    }

    else
    {
        for (unsigned int i = 0; i < possibleMoves.size(); i++)
        {
            cerr << "testing other cases" << endl;


            Board * tempBoard = board->copy();
            tempBoard->doMove(possibleMoves[i], side);

            score = -minimaxScore(tempBoard, depth - 1, other);

            delete tempBoard;

            if (score > maxScore)
            {
                maxScore = score;
            }


        }
    }

    cerr << "one level down" << endl;

    return maxScore;
}