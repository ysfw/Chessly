#include "piece.h"
#include "game.h"
king::king(bool isWhite, pair<int, int> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♚":"♔");
    canCastle = true;
}

void king:: checkMoves(board &Board, pair<size_t, size_t> position){
    
    clearMoves();
    pair<int,int> directions [8]  = {{0,1},{0,-1},{-1,0},{1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
    for(pair<int,int> direction : directions){
        int firstCoord =(int)this->getPosition().first + direction.first;
        int secondCoord = (int)this->getPosition().second + direction.second;
        if((firstCoord <8 &&firstCoord >= 0 && secondCoord < 8  && secondCoord >=0))
        {
            vector<AttackInfo> attackingTheSquare = Board.AttackedBy({firstCoord,secondCoord},this->isWhite());
            if (Board.getAt({firstCoord,secondCoord}) == nullptr)
                {
                    
                    if(attackingTheSquare.empty()) 
                    {
                        addPossibleMove({firstCoord,secondCoord});
                    }
                }
                else
                {
                    if (Board.getAt({firstCoord,secondCoord})->isWhite() != this->isWhite())
                    {
                        // capturable
                        if(attackingTheSquare.empty()) 
                    {
                        addPossibleMove({firstCoord,secondCoord});
                        addPossibleCapture({firstCoord,secondCoord});
                    }
                }
                }
        }
    }
}


