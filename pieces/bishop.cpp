#include "piece.h"
#include "game.h"
bishop::bishop(bool isWhite, pair<size_t,size_t> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♝":"♗");    
}

void bishop :: checkMoves(board &Board, pair<size_t,size_t> currPosition)
{
    clearMoves();
    for (size_t direction = 1; direction < 5; direction++)
    {
        for (size_t i=1;i < 8; i++)
        {
            size_t firstCoord, secondCoord;        
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
            break;
        }
    if (secondCoord < 8 && firstCoord<8)
    {
        if ((Board.getAt({firstCoord,secondCoord}) == nullptr))
        {
            addPossibleMove({firstCoord,secondCoord});
        }
        else
        {
            if (Board.getAt({firstCoord,secondCoord})->isWhite() != this->isWhite()){
            //capturable
            addPossibleMove({firstCoord,secondCoord});
            addPossibleCapture({firstCoord,secondCoord});
            }
            break;
        }
        
    }
    else break;
}      
    }
    
}
