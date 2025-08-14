#include "piece.h"
#include "game.h"
king::king(bool isWhite, pair<int, int> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♚":"♔");
    canCastle = true;
}

void king::checkMoves(board &Board, pair<size_t, size_t> position) {
    clearMoves();
    pair<int, int> directions[8] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (pair<int, int> direction : directions) {
        int firstCoord = (int)this->getPosition().first + direction.first;
        int secondCoord = (int)this->getPosition().second + direction.second;

        if ((firstCoord < 8 && firstCoord >= 0 && secondCoord < 8 && secondCoord >= 0)) {
            pair<size_t, size_t> targetSquare = {(size_t)firstCoord, (size_t)secondCoord};
            piece* pieceOnTarget = Board.getAt(targetSquare);

            if (pieceOnTarget != nullptr && pieceOnTarget->isWhite() == this->isWhite()) {
                continue;
            }

            board tempBoard = Board; 
            tempBoard.setAt(targetSquare,this);
            tempBoard.setAt(this->getPosition(),nullptr); 

            if (tempBoard.AttackedBy(targetSquare, this->isWhite()).empty()) {
                addPossibleMove(targetSquare);
                if (pieceOnTarget != nullptr) {
                    addPossibleCapture(targetSquare);
                }
            }
        }
    }
}