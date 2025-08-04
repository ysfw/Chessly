#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class queen : public piece
{
private:
    void straightmovesHelper(vector<vector<piece *>> &board, pair<int, int> position,char direction);
    void diagonalmovesHelper(vector<vector<piece *>> &board, pair<int, int> position,int direction);
public:
    queen(bool White, pair<int, int> startingPosition);
    void checkMoves(vector<vector<piece *>> &board, pair<int, int> position);
};

queen::queen(bool White, pair<int, int> startingPosition)
    : piece(White, startingPosition)
{
    setValue(White ? "♛":"♕");
}



void queen:: straightmovesHelper(vector<vector<piece *>> &board, pair<int, int> position,char direction)
{
    int firstCoord, secondCoord,i=1;
    
    switch (direction)
    {
        case 'r':
        firstCoord = position.first;
        secondCoord = position.second +i;
    break;
    
    case 'l':
        firstCoord = position.first;
        secondCoord = position.second -i;
    break;

    case 'u':
        firstCoord = position.first+i;
        secondCoord = position.second;
    break;

    case 'd':
        firstCoord = position.first-i;
        secondCoord = position.second;
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


void queen:: diagonalmovesHelper(vector<vector<piece *>> &board, pair<int, int> position,int direction) 
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


void queen::checkMoves(vector<vector<piece *>> &board, pair<int, int> position)
{
    straightmovesHelper(board,position,'r');
    straightmovesHelper(board,position,'l');
    straightmovesHelper(board,position,'u');
    straightmovesHelper(board,position,'d');

    diagonalmovesHelper(board,position,1);
    diagonalmovesHelper(board,position,2);
    diagonalmovesHelper(board,position,3);
    diagonalmovesHelper(board,position,4);
}


