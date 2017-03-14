#include "player.hpp"

/*
 * Beep! - Ray
 */

/*
 * Hello! - Karthik
 */

#define     USE_ABPRUNE         4

#define     ABPRUNE_DEPTH       2
#define     MINIMAX_DEPTH       2

#define     STONES_WT           -2
#define     MOBILITY_WT         -8
#define     HEURISTIC_MAT_WT    -10

#define     ENDGAME_STONES_WT    -15   
#define     ENDGAME_MOBILITY_WT  0
#define     ENDGAME_HEUR_MT_WT   -7

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    if (ABPRUNE_DEPTH)
        cerr << "Using alpha-beta pruning!" << endl;
    
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;

    // Set player and opponent sides
    playerSide = side;
    opponent = (side == BLACK) ? WHITE : BLACK;

    boardState = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}


const short Player::heuristic_matrix[8][8] = {{120, -20, 20, 5, 5, 20, -20, 120},
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
    ///////////////////////////////////////////////////
    // RANDOM IMPLEMENTATION //////////////////////////
    ///////////////////////////////////////////////////

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



    ///////////////////////////////////////////////////
    // ALPHA-BETA IMPLEMENTATION //////////////////////
    ///////////////////////////////////////////////////


    if (USE_ABPRUNE)
    {
        boardState -> doMove(opponentsMove, opponent);

        if (!boardState->hasMoves(playerSide))
            return NULL;

        vector <Move *> possibleMoves = getPossibleMoves(boardState, playerSide);
        int score = 0;
        Move * goodMove = possibleMoves[0];
        int maxScore = -10000000;

        if (possibleMoves.size() == 0)
            return NULL;

        else
        {
            for (unsigned int i = 1; i < possibleMoves.size(); i++)
            {
                score = alphaBetaScore(boardState, possibleMoves[i],
                    -10000000, 10000000, ABPRUNE_DEPTH, playerSide);

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



    ///////////////////////////////////////////////////
    // MINIMAX IMPLEMENTATION /////////////////////////
    ///////////////////////////////////////////////////


    if (testingMinimax)
    {
        boardState -> doMove(opponentsMove, opponent);

        if (!boardState->hasMoves(playerSide))
            return NULL;

        vector <Move *> possibleMoves = getPossibleMoves(boardState, playerSide);
        int score = 0;
        Move * goodMove = possibleMoves[0];
        int maxScore = getMobilityScore(boardState, goodMove, playerSide);


        if (possibleMoves.size() == 0)
        {
            return NULL;
        }

        else
        {
            for (unsigned int i = 1; i < possibleMoves.size(); i++)
            {
                score = minimaxScore(boardState, MINIMAX_DEPTH, playerSide);

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

    ///////////////////////////////////////////////////
    // HEURISTIC IMPLEMENTATION ///////////////////////
    ///////////////////////////////////////////////////

    else{
        boardState -> doMove(opponentsMove, opponent);

        if (!boardState->hasMoves(playerSide))
        {
            return NULL;
        }

        Move * goodMove = NULL;

        int maxScore = -100000;
        int currScore = 0;

        for (int i = 0; i < 8; i++) 
        {
            for (int j = 0; j < 8; j++) 
            {
                Move * m = new Move(i, j);

                if (boardState->checkMove(m, playerSide))
                {
                    Board * tempBoard = boardState->copy();

                    tempBoard->doMove(m, playerSide);

                    currScore = (HEURISTIC_MAT_WT * heuristic_matrix[i][j])
                        + (STONES_WT * getNaiveScore(tempBoard, nullptr, playerSide))
                        + (MOBILITY_WT * getMobilityScore(tempBoard, nullptr, playerSide));

                    if (currScore > maxScore)
                    {
                        maxScore = currScore;
                        goodMove = m;
                    }

                    else
                    {
                        delete m;
                    }

                    delete tempBoard;
                }
            }
        }

        boardState->doMove(goodMove, playerSide);

        return goodMove;    
    }
}

int Player::alphaBetaScore(Board * board, Move * move, int alpha, int beta, int depth, Side side)
{
    Board * newBoard = board->copy();
    newBoard->doMove(move, side);

    Side other = (side == BLACK) ? WHITE : BLACK;

    vector <Move *> possibleMoves = getPossibleMoves(newBoard, other);
    int score = -10000000;
    int bestScore = 0;

    int cutoff = 5;

    int movesLeft = 64 - newBoard->numFreeSquares();

    if (depth == 0)
    {
        if (movesLeft < cutoff)
        {
            score = ENDGAME_STONES_WT + ENDGAME_MOBILITY_WT + ENDGAME_HEUR_MT_WT;
            return score;
        }

        if(possibleMoves.size() == 0)
        {
            score = (HEURISTIC_MAT_WT * heuristic_matrix[move->x][move->y]) 
                + (MOBILITY_WT * getMobilityScore(newBoard, nullptr, other))
                + (STONES_WT * getNaiveScore(newBoard, nullptr, other));

            delete newBoard;
            return score;
        }

        int minScore = 100000;

        for (unsigned int i = 0; i < possibleMoves.size(); i++)
        {
            score = (HEURISTIC_MAT_WT * heuristic_matrix[possibleMoves[i]->x]
                [possibleMoves[i]->y]) 
                + (MOBILITY_WT * getMobilityScore(newBoard, nullptr, other))
                + (STONES_WT * getNaiveScore(newBoard, nullptr, other));

            if (score < minScore)
                minScore = score;
        }

        delete newBoard;

        return minScore;
    }

    // If it's our turn (last move was opponent's)
    if (side == opponent)
    {
        bestScore = -10000000;

        for (unsigned int i = 0; i < possibleMoves.size(); i++)
        {
            score = alphaBetaScore(newBoard, possibleMoves[i], alpha, beta, 
                depth - 1, other);

            if (score > bestScore)
                bestScore = score;

            if (bestScore > alpha)
                alpha = bestScore;

            if (beta <= alpha)
                break;
        }
    }
    // If it's our opponent's turn (last move was ours)
    else
    {
        bestScore = 10000000;

        for (unsigned int i = 0; i < possibleMoves.size(); i++)
        {
            score = alphaBetaScore(newBoard, possibleMoves[i], alpha, beta, 
                depth - 1, other);

            if (score < bestScore)
                bestScore = score;

            if (bestScore < beta)
                beta = bestScore;

            if (beta <= alpha)
                break;
        }
    }

    delete newBoard;
    return bestScore;
}

/*
 * Recursively computes the minimum score with minimax
 */
int Player::minimaxScore(Board * board, int depth, Side side){

    vector <Move *> possibleMoves = getPossibleMoves(board, side);
    int score = 0;
    int bestScore = 0;

    //Side other = side==BLACK? WHITE:BLACK;

    // Base case - if we are at a terminal node of our tree, or
    // there are no possible moves, simply return the value of the heuristic
    if (depth == 0)
    {
        if(possibleMoves.size() == 0)
            return getMobilityScore(board, nullptr, side);

        int minScore = 100000;

        for (unsigned int i = 0; i < possibleMoves.size(); i++)
        {
            score = (HEURISTIC_MAT_WT * heuristic_matrix[possibleMoves[i]->x]
                [possibleMoves[i]->y]) + (MOBILITY_WT * getMobilityScore(board, nullptr, side))
                + (STONES_WT * getNaiveScore(board, nullptr, side));

            if (score < minScore)
                minScore = score;
        }

        return minScore;
    }

    // Recursive case
    else
    {
        // If the current player is us, try to maximize our minimum score
        if (playerSide == side)
        {
            bestScore = -100000;

            for (unsigned int i = 0; i < possibleMoves.size(); i++)
            {
                Board * tempBoard = board->copy();
                tempBoard->doMove(possibleMoves[i], side);

                //score = (HEURISTIC_MAT_WT * heuristic_matrix[possibleMoves[i]->x]
                //    [possibleMoves[i]->y]) + minimaxScore(tempBoard, depth - 1, opponent);
                score = minimaxScore(tempBoard, depth - 1, opponent);

                delete tempBoard;

                if (score > bestScore)
                    bestScore = score;
            }
        }

        // Assume that the opponent will try to minimize our score
        else
        {
            bestScore = 100000;

            for (unsigned int i = 0; i < possibleMoves.size(); i++)
            {
                Board * tempBoard = board->copy();
                tempBoard->doMove(possibleMoves[i], side);

                //score = (HEURISTIC_MAT_WT * heuristic_matrix[possibleMoves[i]->x]
                //    [possibleMoves[i]->y]) + minimaxScore(tempBoard, depth - 1, playerSide);
                score = minimaxScore(tempBoard, depth - 1, opponent);

                delete tempBoard;

                if (score < bestScore)
                    bestScore = score;
            }
        }

    }

    return bestScore;
}

/*
 * For a specified side and move, return the value of the
 * naive heuristic (number of own stones - number of opponent
 * stones)
 */
int Player::getNaiveScore(Board * board, Move * m, Side side){

    Board * copyBoard = board->copy();

    copyBoard->doMove(m, side);

    Side other = side==BLACK? WHITE:BLACK;

    int score = copyBoard->count(side) - copyBoard->count(other);

    delete copyBoard;

    return score;
}



int Player::getMobilityScore(Board * board, Move * m, Side side){

    Board * copyBoard = board->copy();

    copyBoard->doMove(m, side);

    Side other = side==BLACK? WHITE:BLACK;

    int score;

    // if (getNumMoves(copyBoard, side) + getNumMoves(copyBoard, other) != 0)
    // {
    //     score = int(100 * ((float) (getNumMoves(copyBoard, side) - getNumMoves(copyBoard, other)))/((float) ((getNumMoves(copyBoard, side) + getNumMoves(copyBoard, other)))));
    // }

    // else
    // {
    //     score = 0;
    // }

    int playerMoves = getNumMoves(copyBoard, side);
    int oppMoves = getNumMoves(copyBoard, other);

    if (playerMoves > oppMoves)
    {
        score = int(((float)(100) * playerMoves / ((float) playerMoves + oppMoves)));
    }

    else if (playerMoves < oppMoves)
    {
        score = -int(((float)(100) * playerMoves / ((float) playerMoves + oppMoves)));
    }

    else{
        score = 0;
    }

    delete copyBoard;

    return score;
}

/*
 * For a specified side, return the number of possible moves in the
 * current game state
 */
int Player::getNumMoves(Board * board, Side side)
{
    int moves = 0;

    if (board->hasMoves(side))
    {    
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move * move = new Move(i, j);

                if (board->checkMove(move, side))
                    moves++;

                delete move;
            }
        }
    }

    return moves;
}


/*
 * For a specified side, return a vector of all the possible moves
 * in the current game state
 */
vector <Move*> Player::getPossibleMoves(Board* board, Side side){

    vector <Move*> possibleMoves = vector <Move*>();

    if (board->hasMoves(side))
    {    
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move * move = new Move(i, j);
                if (board->checkMove(move, side)){
                    possibleMoves.push_back(move);
                }

                else{

                    delete move;
                }
            }
        }
    }

    return possibleMoves;
}