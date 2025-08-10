#include "piece.h"

rook::rook(bool isWhite, pair<size_t, size_t> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♜" : "♖");
    canCastle = true;
}

bool rook::checkRookCastle()
{
    return canCastle;
}


void rook::movesHelper(board &Board, pair<size_t, size_t> currPos,char direction)
{
    size_t firstCoord, secondCoord,i=1;
    
    switch (direction)
    {
        case 'r':
        firstCoord = currPos.first;
        secondCoord = currPos.second +i;
    break;
    
    case 'l':
        firstCoord = currPos.first;
        secondCoord = currPos.second -i;
    break;

    case 'u':
        firstCoord = currPos.first+i;
        secondCoord = currPos.second;
    break;

    case 'd':
        firstCoord = currPos.first-i;
        secondCoord = currPos.second;
    break;


    default:
    return;
}

for ( ;i < 8; i++)
{
    if (secondCoord < 8 && firstCoord<8 )
    {
        if (Board.getAt({firstCoord,secondCoord}) == nullptr)
        {
            addPossibleMove({firstCoord,secondCoord});
        }
        else
        {
            if (Board.getAt({firstCoord,secondCoord})->isWhite() != this->isWhite()){
            //capturable
            }
            break;
        }
        
    }
}      
}


void rook::checkMoves(board &Board, pair<size_t, size_t> currPos)
{
    movesHelper(Board,currPos,'r');
    movesHelper(Board,currPos,'l');
    movesHelper(Board,currPos,'u');
    movesHelper(Board,currPos,'d');

}