#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class Knight : public piece
{
private:
    void movesHelper(vector<vector<piece *>> &board, pair<int, int> position,char direction);
public:
    Knight(bool White, pair<int, int> startingPosition);
    void checkMoves(vector<vector<piece *>> &board, pair<int, int> position);
};

Knight::Knight(bool White, pair<int, int> startingPosition)
    : piece(White, startingPosition)
{
    setValue(White ? "♝":"♗");    
}

void Knight :: movesHelper(vector<vector<piece *>> &board, pair<int, int> position,char direction){

    switch (direction)
    {
    case 'r':
    if((position.first+1 < 8 && position.second+2 <8))    
    {
        if (board[position.first +1][position.second+2] == nullptr)
        {
            addPossibleMove({position.first+1,position.second+2});
        }
        else{
            if(board[position.first +1][position.second+2]->isWhite() != this->isWhite()){
                //capturable
            }
        }
    }
    
    if((position.first-1 >=0 && position.second+2 <8))    
    {
        if (board[position.first -1][position.second+2] == nullptr)
        {
            addPossibleMove({position.first-1,position.second+2});
        }
        else{
            if(board[position.first -1][position.second+2]->isWhite() != this->isWhite()){
                //capturable
            }
        }
    }
    break;
        
    case 'l':
        if((position.first+1 < 8 && position.second-2 >=0))    
    {
        if ((board[position.first +1][position.second-2] == nullptr))
        {
            addPossibleMove({position.first+1,position.second-2});
        }
        else{
            if(board[position.first +1][position.second-2]->isWhite() != this->isWhite()){
                //capturable
            }
        }
    }
    
    if((position.first-1 >=0 && position.second-2 >=0))    
    {
        if ((board[position.first -1][position.second-2] == nullptr))
        {
            addPossibleMove({position.first-1,position.second-2});
        }
        else{
            if(board[position.first -1][position.second-2]->isWhite() != this->isWhite()){
                //capturable
            }
        }
    }    
        break;
        
    case 'u':
        if(position.first+2 < 8 && position.second+1 <8){
            if ((board[position.first + 2][position.second+1] == nullptr))
            {
                addPossibleMove({position.first+2,position.second+1});
            }
            else{
                if(board[position.first +2][position.second+1]->isWhite() != this->isWhite()){
                //capturable
            }
            }
        }   
        
        if(position.first+2 < 8 && position.second-1 >=0)
        {
        if ((board[position.first + 2][position.second-1] == nullptr))
        {
            addPossibleMove({position.first+2,position.second-1});
        }
        else
        {
            if(board[position.first +2][position.second-1]->isWhite() != this->isWhite()){
                //capturable
            }
        }
        }
       break;

    case 'd':
    if (position.first-2 >=0 && position.second+1 <8)
    {
        if ((board[position.first - 2][position.second+1]==nullptr))
        {
            addPossibleMove({position.first-2,position.second+1});
        }
        else
        {
            if(board[position.first -2][position.second+1]->isWhite() != this->isWhite()){
                //capturable
            }
        }
        
    }    

    if(position.first-2 >=0 && position.second-1 >=0)
    {
        if ((board[position.first - 2][position.second-1]==nullptr))
        {
            addPossibleMove({position.first-2,position.second-1});
        }
        else
        {
            if(board[position.first -2][position.second-1]->isWhite() != this->isWhite()){
                //capturable
            }
        }
    }
        break;


    default:
    return;
}
}

void Knight :: checkMoves(vector<vector<piece *>> &board, pair<int, int> position)
{

    movesHelper(board,position,'r');
    movesHelper(board,position,'l');
    movesHelper(board,position,'u');
    movesHelper(board,position,'d');

}
