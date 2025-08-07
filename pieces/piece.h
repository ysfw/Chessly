#pragma once
#include <bits/stdc++.h>
#include "../board.h"
using namespace std;
class piece
{
private:
    pair<int, int> position;
    bool White;
    string value ;
    /// @brief 
    vector<pair<int, int>> possibleMoves;

public:
    piece();
    piece(bool isWhite, pair<int, int> startingPosition);
    virtual ~piece() {}
    bool isWhite(){return White;};
    void updatePos(pair<int, int> newPosition);
    pair<int, int> getPosition();
    string getValue();
    void setValue(string);
    void addPossibleMove(pair<int, int> move);

};

piece :: piece (bool white, pair<int, int> startingPosition)
    : position(startingPosition), White(white), value(""), possibleMoves() {}

piece::piece()
    : position({-1, -1}), White(false), value(""), possibleMoves() {}

pair<int, int> piece::getPosition()
{
    return position;
}

void piece::updatePos(pair<int, int> newPosition)
{
    position = newPosition;
}

string piece:: getValue(){
    return value;
}

void piece::setValue(string value){
    value = value;
}

void piece:: addPossibleMove(pair<int, int> move){
    possibleMoves.push_back(move);
}

