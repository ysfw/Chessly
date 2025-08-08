#pragma once
#include <bits/stdc++.h>
#include "../board.h"
using namespace std;
class piece
{
private:
    pair<size_t,size_t>  position;
    bool White;
    string value ;
    vector<pair<size_t,size_t>> possibleMoves;

public:
    piece();
    piece(bool isWhite, pair<size_t,size_t> startingPosition);
    virtual ~piece() {}
    bool isWhite(){return White;};
    void updatePos(pair<size_t,size_t> newPosition);
    pair<size_t,size_t> getPosition();
    string getValue();
    void setValue(string);
    void addPossibleMove(pair<size_t,size_t> move);

};

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

