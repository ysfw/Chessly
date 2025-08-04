#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class rook : public piece
{
private:
    bool canCastle;

    /*This Helper Function reduces redundancy in the checkmoves function
    by taking the direction either 'r'ight, 'l'eft, 'u'p or 'd'own and performing a loop on that direction
    taking into accout that these directions will be reversed for black rooks, but still it does what it should be doing
    because by anymeans this will be called in all four directions, so it doesn't really matter. 
    Variations of this function will be used in other pieces for the same purpose of reducing redundancy. 
    */
    void movesHelper(vector<vector<piece *>> &board, pair<int, int> position,char direction);
public:
    rook(bool White, pair<int, int> position);
    bool checkRookCastle();
    void checkMoves(vector<vector<piece *>> &board, pair<int, int> position);
};

rook::rook(bool White, pair<int, int> startingPosition)
    : piece(White, startingPosition)
{
    setValue(White ? "♜" : "♖");
    canCastle = true;
}

bool rook::checkRookCastle()
{
    return canCastle;
}


void rook::movesHelper(vector<vector<piece *>> &board, pair<int, int> position,char direction)
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


void rook::checkMoves(vector<vector<piece *>> &board, pair<int, int> position)
{
    movesHelper(board,position,'r');
    movesHelper(board,position,'l');
    movesHelper(board,position,'u');
    movesHelper(board,position,'d');

}