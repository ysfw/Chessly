#include "piece.h"
#include "player.h"
#include "helpers.h"

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
    possibleMoves.insert(move);
}


bool piece :: Move(player *player,board &Board,pair<size_t,size_t> oldPosition,pair<size_t,size_t> newPosition)
{
    piece* curr = (Board.getAt({oldPosition.first,oldPosition.second}));
    piece* next = (Board.getAt({newPosition.first,newPosition.second}));
    curr->checkMoves(Board,oldPosition);
    if(binary_search(curr->possibleMoves.begin(),curr->possibleMoves.end(),newPosition))
    {
        if(binary_search(curr->possibleCaptures.begin(),curr->possibleCaptures.end(),newPosition)){
            
            player->addMove({{curr,moveTOstring(oldPosition)},true});  
            player->addCapture({next,moveTOstring(newPosition)});
            curr->updatePos(newPosition);
            Board.setAt(oldPosition,nullptr);
        }
        else {
            player->addMove({{curr,moveTOstring(oldPosition)},false});  
            curr->updatePos(newPosition);
            Board.setAt(oldPosition,nullptr);
        }
        return true;
    }
    else return false; //can't move in that direction 
}