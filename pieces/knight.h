#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class Knight : public piece
{
private:
    void movesHelper(vector<vector<piece *>> &board, pair<size_t,size_t> currPosition,char direction);
public:
    Knight(bool White, pair<size_t,size_t> startingPosition);
    void checkMoves(vector<vector<piece *>> &board, pair<size_t,size_t> currPosition);
};

Knight::Knight(bool isWhite, pair<size_t,size_t> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♞":"♘");    
}

void Knight :: movesHelper(vector<vector<piece *>> &board, pair<size_t,size_t> currPosition,char direction){

    switch (direction)
    {
    case 'r':
    if((currPosition.first+1 < 8 && currPosition.second+2 <8))    
    {
        if (board[currPosition.first +1][currPosition.second+2] == nullptr)
        {
            addPossibleMove({currPosition.first+1,currPosition.second+2});
        }
        else{
            if(board[currPosition.first +1][currPosition.second+2]->isWhite() != this->isWhite()){
                //capturable
            }
        }
    }

    if((currPosition.first-1<8 && currPosition.second+2 <8))    
    {
        if (board[currPosition.first -1][currPosition.second+2] == nullptr)
        {
            addPossibleMove({currPosition.first-1,currPosition.second+2});
        }
        else{
            if(board[currPosition.first -1][currPosition.second+2]->isWhite() != this->isWhite()){
                //capturable
            }
        }
    }
    break;
        
    case 'l':
        if((currPosition.first+1 < 8 && currPosition.second-2 <8))    
    {
        if ((board[currPosition.first +1][currPosition.second-2] == nullptr))
        {
            addPossibleMove({currPosition.first+1,currPosition.second-2});
        }
        else{
            if(board[currPosition.first +1][currPosition.second-2]->isWhite() != this->isWhite()){
                //capturable
            }
        }
    }

    if((currPosition.first-1<8 && currPosition.second-2 <8 ))    
    {
        if ((board[currPosition.first -1][currPosition.second-2] == nullptr))
        {
            addPossibleMove({currPosition.first-1,currPosition.second-2});
        }
        else{
            if(board[currPosition.first -1][currPosition.second-2]->isWhite() != this->isWhite()){
                //capturable
            }
        }
    }    
        break;
        
    case 'u':
        if(currPosition.first+2 < 8 && currPosition.second+1 <8){
            if ((board[currPosition.first + 2][currPosition.second+1] == nullptr))
            {
                addPossibleMove({currPosition.first+2,currPosition.second+1});
            }
            else{
                if(board[currPosition.first +2][currPosition.second+1]->isWhite() != this->isWhite()){
                //capturable
            }
            }
        }

        if(currPosition.first+2 < 8 && currPosition.second-1 <8)
        {
        if ((board[currPosition.first + 2][currPosition.second-1] == nullptr))
        {
            addPossibleMove({currPosition.first+2,currPosition.second-1});
        }
        else
        {
            if(board[currPosition.first +2][currPosition.second-1]->isWhite() != this->isWhite()){
                //capturable
            }
        }
        }
       break;

    case 'd':
    if (currPosition.second+1 <8 && currPosition.first-2 <8)
    {
        if ((board[currPosition.first - 2][currPosition.second+1]==nullptr))
        {
            addPossibleMove({currPosition.first-2,currPosition.second+1});
        }
        else
        {
            if(board[currPosition.first -2][currPosition.second+1]->isWhite() != this->isWhite()){
                //capturable
            }
        }
        
    }    

    if(currPosition.first-2 <8 && currPosition.second-1 <8)
    {
        if ((board[currPosition.first - 2][currPosition.second-1]==nullptr))
        {
            addPossibleMove({currPosition.first-2,currPosition.second-1});
        }
        else
        {
            if(board[currPosition.first -2][currPosition.second-1]->isWhite() != this->isWhite()){
                //capturable
            }
        }
    }
        break;


    default:
    return;
}
}

void Knight :: checkMoves(vector<vector<piece *>> &board, pair<size_t,size_t> currPosition)
{

    movesHelper(board,currPosition,'r');
    movesHelper(board,currPosition,'l');
    movesHelper(board,currPosition,'u');
    movesHelper(board,currPosition,'d');

}
