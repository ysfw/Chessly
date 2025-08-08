#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class queen : public piece
{
private:
    void straightmovesHelper(vector<vector<piece *>> &board, pair<size_t, size_t> currPosition,char direction);
    void diagonalmovesHelper(vector<vector<piece *>> &board, pair<size_t, size_t> currPosition,int direction);
public:
    queen(bool White, pair<size_t, size_t> startingPosition);
    void checkMoves(vector<vector<piece *>> &board, pair<size_t, size_t> currPosition);
};

queen::queen(bool isWhite, pair<size_t, size_t> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♛":"♕");
}



void queen:: straightmovesHelper(vector<vector<piece *>> &board, pair<size_t, size_t> currPosition,char direction)
{
    size_t firstCoord, secondCoord,i=1;
    
    switch (direction)
    {
    case 'r':
        firstCoord = currPosition.first;
        secondCoord = currPosition.second +i;
    break;
    
    case 'l':
        firstCoord = currPosition.first;
        secondCoord = currPosition.second -i;
    break;

    case 'u':
        firstCoord = currPosition.first+i;
        secondCoord = currPosition.second;
    break;

    case 'd':
        firstCoord = currPosition.first-i;
        secondCoord = currPosition.second;
    break;


    default:
    return;
}

for ( ;i < 8; i++)
{
    if (secondCoord < 8 && firstCoord<8 )
    {
        if ((board[firstCoord][secondCoord]==nullptr))
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


void queen:: diagonalmovesHelper(vector<vector<piece *>> &board, pair<size_t, size_t> currPosition,int direction) 
{
    size_t firstCoord, secondCoord,i=1;
    
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
        if ((board[firstCoord][secondCoord]==nullptr))
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


void queen::checkMoves(vector<vector<piece *>> &board, pair<size_t, size_t> currPosition)
{
    straightmovesHelper(board,currPosition,'r');
    straightmovesHelper(board,currPosition,'l');
    straightmovesHelper(board,currPosition,'u');
    straightmovesHelper(board,currPosition,'d');

    diagonalmovesHelper(board,currPosition,1);
    diagonalmovesHelper(board,currPosition,2);
    diagonalmovesHelper(board,currPosition,3);
    diagonalmovesHelper(board,currPosition,4);
}


