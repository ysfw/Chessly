#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class rook : public piece {
private:
    bool canCastle;

    /*This Helper Function reduces redundancy in the checkmoves function
    by taking the direction either 'r'ight, 'l'eft, 'u'p or 'd'own and performing a loop on that direction
    taking into accout that these directions will be reversed for black rooks, but still it does what it should be doing
    because by anymeans this will be called in all four directions, so it doesn't really matter. 
    Variations of this function will be used in other pieces for the same purpose of reducing redundancy. 
    */
    void movesHelper(vector<vector<piece *>> &Board, pair<size_t, size_t> currPos,char direction);
public:
    rook(bool White, pair<size_t, size_t> startingPosition);
    bool checkRookCastle();
    void checkMoves(vector<vector<piece *>> &Board, pair<size_t, size_t> currPos);
};

rook::rook(bool isWhite, pair<size_t, size_t> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♜" : "♖");
    canCastle = true;
}

bool rook::checkRookCastle()
{
    return canCastle;
}


void rook::movesHelper(vector<vector<piece *>> &Board, pair<size_t, size_t> currPos,char direction)
{
    size_t firstCoord, secondCoord,i=1;
    
    switch (direction)
    {
        case 'r':
        firstCoord = currPos.first;
        secondCoord = currPos.second +i;
    break;
    
    case 'l':
        firstCoord = currPos.first;
        secondCoord = currPos.second -i;
    break;

    case 'u':
        firstCoord = currPos.first+i;
        secondCoord = currPos.second;
    break;

    case 'd':
        firstCoord = currPos.first-i;
        secondCoord = currPos.second;
    break;


    default:
    return;
}

for ( ;i < 8; i++)
{
    if (secondCoord < 8 && firstCoord<8 )
    {
        if (Board[firstCoord][secondCoord] == nullptr)
        {
            addPossibleMove({firstCoord,secondCoord});
        }
        else
        {
            if (Board[firstCoord][secondCoord]->isWhite() != this->isWhite()){
            //capturable
            }
            break;
        }
        
    }
}      
}


void rook::checkMoves(vector<vector<piece *>> &board, pair<size_t, size_t> currPos)
{
    movesHelper(board,currPos,'r');
    movesHelper(board,currPos,'l');
    movesHelper(board,currPos,'u');
    movesHelper(board,currPos,'d');

}