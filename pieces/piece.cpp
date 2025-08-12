#include "piece.h"
#include "player.h"
#include "helpers.h"
#include "board.h"

bool piece::isWhite(){return White;}
set<pair<size_t,size_t>> piece :: getPossibleMoves () {return possibleMoves;};
set<pair<size_t,size_t>> piece :: getPossibleCaptures () {return possibleCaptures;};

piece :: piece (bool isWhite, pair<size_t,size_t> startingPosition)
    : position(startingPosition), White(isWhite), value(""), possibleMoves() {}

piece::piece()
    : position({0,0}), White(false), value(""), possibleMoves() {}

pair<size_t,size_t> piece::getPosition()
{
    return this->position;
}

piece :: ~piece(){
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

void piece:: addPossibleCapture(pair<size_t,size_t> move){
    possibleCaptures.insert(move);
}

void piece:: clearMoves(){
    possibleMoves.clear();
    possibleCaptures.clear();
}

void piece :: checkMoves(board &Board, pair<size_t,size_t> currPosition){}

bool piece :: Move(player *player,board &Board,pair<size_t,size_t> newPosition)
{
    piece* next = (Board.getAt({newPosition.first,newPosition.second}));
    this -> clearMoves();
    checkMoves(Board,position);
    
    //Debugging

        cout<< "Possible moves (Red is capturable): ";
        for(pair<size_t,size_t> move : possibleMoves){
            string moveString = moveTOstring(move);
            if(binary_search(possibleCaptures.begin(),possibleCaptures.end(),move)){
                moveString = "\x1b[31m" + moveString + "\x1b[0m";
            }
            cout<< moveString <<" , ";
        }

    //endofDebugging

    if(binary_search(this->possibleMoves.begin(),this->possibleMoves.end(),newPosition))
    {
        if(binary_search(this->possibleCaptures.begin(),this->possibleCaptures.end(),newPosition)){
            
            player->addMove({{this,moveTOstring(position)},true});  
            player->addCapture({next,moveTOstring(newPosition)});
            Board.setAt(newPosition,this);
            Board.setAt(position,nullptr);
            this->updatePos(newPosition);
        }
        else {
            player->addMove({{this,moveTOstring(position)},false});  
            Board.setAt(newPosition,this);
            Board.setAt(position,nullptr);
            this->updatePos(newPosition);
        }
        
        return true;
    }
    else return false; //can't move in that direction 
}

