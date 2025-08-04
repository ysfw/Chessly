#pragma once
#include <bits/stdc++.h>
#include "board.h"
using namespace std;
class piece
{
private:
    pair<int, int> position;
    vector<pair<int, int>> possibleMoves;
    bool White;
    string value ;

public:
    piece(bool White, pair<int, int> startingPosition);
    virtual ~piece() {}
    bool isWhite();
    void updatePos(pair<int, int> newPosition);
    string getValue();
    void setValue(string);
    void addPossibleMove(pair<int, int> move);
};

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




class emptySquare : piece
{
public:
    emptySquare(bool White, pair<int, int> position);
};

emptySquare::emptySquare(bool White, pair<int, int> position)
    : piece(White, position)
{
    setValue((White) ? "■" : "□");
}