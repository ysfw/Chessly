#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class bishop : public piece
{
private:
    void movesHelper(vector<vector<piece *>> &board, pair<int, int> position,int direction);
public:
    bishop(bool White, pair<int, int> startingPosition);
    void checkMoves(vector<vector<piece *>> &board, pair<int, int> position);
};

bishop::bishop(bool White, pair<int, int> startingPosition)
    : piece(White, startingPosition)
{
    setValue(White ? "♝":"♗");    
}

void bishop:: movesHelper(vector<vector<piece *>> &board, pair<int, int> position,int direction) 
{
    int firstCoord, secondCoord,i=1;
    
    switch (direction)
    {
    case 1://Right Diagonal Up
        firstCoord = position.first + i;
        secondCoord = position.second +i;
    break;
    
    case 2://Left Diagonal Down
        firstCoord = position.first + i;
        secondCoord = position.second -i;
    break;

    case 3://Right Diagonal Down
        firstCoord = position.first-i;
        secondCoord = position.second+i;
    break;

    case 4://left Diagonal Down
        firstCoord = position.first-i;
        secondCoord = position.second-i;
    break;


    default:
    return;
}

for ( ;i < 8; i++)
{
    if (secondCoord < 8 && secondCoord>=0 && firstCoord<8 && firstCoord>=0)
    {
        if ((board[firstCoord][secondCoord]->getValue() == "■"
        || board[firstCoord][secondCoord]->getValue() == "□"))
        {
            addPossibleMove({firstCoord,secondCoord});
        }
        else
        {
            //capturable
            break;
        }
        
    }
}      
}

void bishop :: checkMoves(vector<vector<piece *>> &board, pair<int, int> position)
{
    movesHelper(board,position,1);
    movesHelper(board,position,2);
    movesHelper(board,position,3);
    movesHelper(board,position,4);
}
