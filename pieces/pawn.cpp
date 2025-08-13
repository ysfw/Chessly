#include "piece.h"
#include "game.h"

pawn::pawn(bool isWhite,pair<size_t,size_t> startingPosition)
: piece(isWhite, startingPosition)
{
    setValue(isWhite ?  "♟" : "♙");
}

void pawn :: setenpassant (){
    enpassant = true;
}

void pawn :: resetenpassant () {
    enpassant = false;
}

bool pawn ::ISenpassant()
{
    return enpassant;
}

void pawn ::checkMoves(board &Board, pair<size_t, size_t> currPosition)
{
    clearMoves();
    if (this->isWhite())
    {
        int forwardOne = currPosition.first + 1;
        int forwardTwo = currPosition.first + 2;

        if (forwardOne < 8 && Board.getAt({(size_t)forwardOne, currPosition.second}) == nullptr)
        {
            addPossibleMove({(size_t)forwardOne, currPosition.second});
            if (currPosition.first == 1 && Board.getAt({(size_t)forwardTwo, currPosition.second}) == nullptr)
            {
                addPossibleMove({(size_t)forwardTwo, currPosition.second});
            }
        }

        if (forwardOne < 8 && currPosition.second + 1 < 8) {
            piece* target = Board.getAt({(size_t)forwardOne, currPosition.second + 1});
            if (target != nullptr && !target->isWhite()) {
                addPossibleMove({(size_t)forwardOne, currPosition.second + 1});
                addPossibleCapture({(size_t)forwardOne, currPosition.second + 1});
            }
        }
        if (forwardOne < 8 && currPosition.second > 0) {
            piece* target = Board.getAt({(size_t)forwardOne, currPosition.second - 1});
            if (target != nullptr && !target->isWhite()) {
                addPossibleMove({(size_t)forwardOne, currPosition.second - 1});
                addPossibleCapture({(size_t)forwardOne, currPosition.second - 1});
            }
        }
        
        if (currPosition.first == 4 && Board.isEnpassant()) {
            if (currPosition.second + 1 < 8) {
                piece* adjacent = Board.getAt({currPosition.first, currPosition.second + 1});
                if (adjacent != nullptr && !adjacent->isWhite()) {
                    if (pawn* p = dynamic_cast<pawn*>(adjacent)) {
                        if (p->ISenpassant()) {
                            addPossibleMove({(size_t)forwardOne, currPosition.second + 1});
                            addPossibleCapture({(size_t)forwardOne, currPosition.second + 1});
                        }
                    }
                }
            }
            if (currPosition.second > 0) {
                piece* adjacent = Board.getAt({currPosition.first, currPosition.second - 1});
                if (adjacent != nullptr && !adjacent->isWhite()) {
                    if (pawn* p = dynamic_cast<pawn*>(adjacent)) {
                        if (p->ISenpassant()) {
                            addPossibleMove({(size_t)forwardOne, currPosition.second - 1});
                            addPossibleCapture({(size_t)forwardOne, currPosition.second - 1});
                        }
                    }
                }
            }
        }
    }
    else
    {
        int forwardOne = currPosition.first - 1;
        int forwardTwo = currPosition.first - 2;

        if (forwardOne >= 0 && Board.getAt({(size_t)forwardOne, currPosition.second}) == nullptr) {
            addPossibleMove({(size_t)forwardOne, currPosition.second});
            if (currPosition.first == 6 && Board.getAt({(size_t)forwardTwo, currPosition.second}) == nullptr) {
                addPossibleMove({(size_t)forwardTwo, currPosition.second});
            }
        }
        
        if (forwardOne >= 0 && currPosition.second + 1 < 8) {
            piece* target = Board.getAt({(size_t)forwardOne, currPosition.second + 1});
            if (target != nullptr && target->isWhite()) {
                addPossibleMove({(size_t)forwardOne, currPosition.second + 1});
                addPossibleCapture({(size_t)forwardOne, currPosition.second + 1});
            }
        }
        if (forwardOne >= 0 && currPosition.second > 0) {
            piece* target = Board.getAt({(size_t)forwardOne, currPosition.second - 1});
            if (target != nullptr && target->isWhite()) {
                addPossibleMove({(size_t)forwardOne, currPosition.second - 1});
                addPossibleCapture({(size_t)forwardOne, currPosition.second - 1});
            }
        }

        if (currPosition.first == 3 && Board.isEnpassant()) {
            if (currPosition.second + 1 < 8) {
                piece* adjacent = Board.getAt({currPosition.first, currPosition.second + 1});
                if (adjacent != nullptr && adjacent->isWhite()) {
                     if (pawn* p = dynamic_cast<pawn*>(adjacent)) {
                        if (p->ISenpassant()) {
                            addPossibleMove({(size_t)forwardOne, currPosition.second + 1});
                            addPossibleCapture({(size_t)forwardOne, currPosition.second + 1});
                        }
                    }
                }
            }
            if (currPosition.second > 0) {
                 piece* adjacent = Board.getAt({currPosition.first, currPosition.second - 1});
                if (adjacent != nullptr && adjacent->isWhite()) {
                     if (pawn* p = dynamic_cast<pawn*>(adjacent)) {
                        if (p->ISenpassant()) {
                            addPossibleMove({(size_t)forwardOne, currPosition.second - 1});
                            addPossibleCapture({(size_t)forwardOne, currPosition.second - 1});
                        }
                    }
                }
            }
        }
    }
}