#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class bishop : public piece
{
private:
    void movesHelper(vector<vector<piece *>> &board, pair<size_t,size_t> currPosition,int direction);
public:
    bishop(bool isWhite, pair<size_t,size_t> startingPosition);
    void checkMoves(vector<vector<piece *>> &board, pair<size_t,size_t> currPosition);
};

bishop::bishop(bool isWhite, pair<size_t,size_t> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♝":"♗");    
}

void bishop:: movesHelper(vector<vector<piece *>> &board, pair<size_t,size_t> currPosition,int direction) 
{
    size_t firstCoord, secondCoord;
    size_t i=1;
    
    switch (direction)
    {
    case 1://Right Diagonal Up
        firstCoord = currPosition.first + i;
        secondCoord = currPosition.second +i;
    break;
    
    case 2://Left Diagonal Down
        firstCoord = currPosition.first + i;
        secondCoord = currPosition.second -i;
    break;

    case 3://Right Diagonal Down
        firstCoord = currPosition.first-i;
        secondCoord = currPosition.second+i;
    break;

    case 4://left Diagonal Down
        firstCoord = currPosition.first-i;
        secondCoord = currPosition.second-i;
    break;


    default:
    return;
}

for ( ;i < 8; i++)
{
    if (secondCoord < 8 && firstCoord<8)
    {
        if ((board[firstCoord][secondCoord] == nullptr))
        {
            addPossibleMove({firstCoord,secondCoord});
        }
        else
        {
            if (board[firstCoord][secondCoord]->isWhite() != this->isWhite()){
            //capturable
            }
            break;
        }
        
    }
}      
}

void bishop :: checkMoves(vector<vector<piece *>> &board, pair<size_t,size_t> currPosition)
{
    movesHelper(board,currPosition,1);
    movesHelper(board,currPosition,2);
    movesHelper(board,currPosition,3);
    movesHelper(board,currPosition,4);
}
