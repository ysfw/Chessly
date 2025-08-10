#include "piece.h"

king::king(bool isWhite, pair<int, int> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♚":"♔");
    inCheck = false;
    canCastle = true;
}

bool king:: IsCheck (board &Board,pair<int,int> currPosition)
{
    //Needs to see if there is a piece that has a possible move to that square, if so the king can't move to that square

    return false; // Placeholder for actual check logic
}
