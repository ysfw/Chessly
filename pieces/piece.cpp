#include "piece.h"
#include "player.h"


piece :: piece (bool isWhite, pair<size_t,size_t> startingPosition)
    : position(startingPosition), White(isWhite), value(""), possibleMoves() {}

piece::piece()
    : position({0,0}), White(false), value(""), possibleMoves() {}

pair<size_t,size_t> piece::getPosition()
{
    return this->position;
}

void piece::updatePos(pair<size_t,size_t> newPosition)
{
    this->position = newPosition;
}

string piece:: getValue(){
    return value;
}

void piece::setValue(string newValue){
    this->value = newValue;
}

void piece:: addPossibleMove(pair<size_t,size_t> move){
    possibleMoves.push_back(move);
}
