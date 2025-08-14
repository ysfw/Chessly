#include "piece.h"
#include "game.h"

Knight::Knight(bool isWhite, pair<size_t, size_t> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♞" : "♘");
}

void Knight ::checkMoves(board &Board, pair<size_t, size_t> currPosition)
{
    clearMoves();
    pair<int,int> directions [8]  = {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{-1,2},{1,-2},{-1,-2}};
    for(pair<int,int> direction : directions){
        int firstCoord =(int)this->getPosition().first + direction.first;
        int secondCoord = (int)this->getPosition().second + direction.second;
        if((firstCoord <8 &&firstCoord >= 0 && secondCoord < 8  && secondCoord >=0))
        {
            pair<size_t, size_t> targetSquare = {(size_t)firstCoord, (size_t)secondCoord};
            piece* pieceOnTarget = Board.getAt(targetSquare);

            if (pieceOnTarget != nullptr && pieceOnTarget->isWhite() == this->isWhite()) {
                continue;
            }

            board tempBoard = Board; 
            tempBoard.setAt(targetSquare,this);
            tempBoard.setAt(this->getPosition(),nullptr); 

            if (tempBoard.AttackedBy(tempBoard.getKingPosition(this->isWhite()), this->isWhite()).empty()) {
                addPossibleMove(targetSquare);
                if (pieceOnTarget != nullptr) {
                    addPossibleCapture(targetSquare);
                }
            }
        }
    }
   
}