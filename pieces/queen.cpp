#include "piece.h"
queen::queen(bool isWhite, pair<size_t, size_t> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♛":"♕");
}



void queen:: straightmovesHelper(board &Board, pair<size_t, size_t> currPosition,char direction)
{
    size_t firstCoord, secondCoord,i=1;
    
    switch (direction)
    {
    case 'r':
        firstCoord = currPosition.first;
        secondCoord = currPosition.second +i;
    break;
    
    case 'l':
        firstCoord = currPosition.first;
        secondCoord = currPosition.second -i;
    break;

    case 'u':
        firstCoord = currPosition.first+i;
        secondCoord = currPosition.second;
    break;

    case 'd':
        firstCoord = currPosition.first-i;
        secondCoord = currPosition.second;
    break;


    default:
    return;
}

for ( ;i < 8; i++)
{
    if (secondCoord < 8 && firstCoord<8 )
    {
        if ((Board.getAt({firstCoord,secondCoord})==nullptr))
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


void queen:: diagonalmovesHelper(board &Board, pair<size_t, size_t> currPosition,int direction) 
{
    size_t firstCoord, secondCoord,i=1;
    
    switch (direction)
    {
    case 1://Right Diagonal Up
        firstCoord = currPosition.first + i;
        secondCoord = currPosition.second +i;
    break;
    
    case 2://Left Diagonal Down
        firstCoord = currPosition.first + i;
        secondCoord = currPosition.second -i;
    break;

    case 3://Right Diagonal Down
        firstCoord = currPosition.first-i;
        secondCoord = currPosition.second+i;
    break;

    case 4://left Diagonal Down
        firstCoord = currPosition.first-i;
        secondCoord = currPosition.second-i;
    break;


    default:
    return;
}

for ( ;i < 8; i++)
{
    if (secondCoord < 8 && firstCoord<8)
    {
        if ((Board.getAt({firstCoord,secondCoord})==nullptr))
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


void queen::checkMoves(board &Board, pair<size_t, size_t> currPosition)
{
    straightmovesHelper(Board,currPosition,'r');
    straightmovesHelper(Board,currPosition,'l');
    straightmovesHelper(Board,currPosition,'u');
    straightmovesHelper(Board,currPosition,'d');

    diagonalmovesHelper(Board,currPosition,1);
    diagonalmovesHelper(Board,currPosition,2);
    diagonalmovesHelper(Board,currPosition,3);
    diagonalmovesHelper(Board,currPosition,4);
}


