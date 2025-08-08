#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class king : public piece
{
private:
    bool inCheck;    
    bool canCastle;
    bool IsCheck(vector<vector<piece *>> &board,pair<int,int> position);
public:
    king(bool White, pair<int, int> startingPosition);
    bool InCheck(){return inCheck;}
    void checkMoves(vector<vector<piece *>> &board, pair<int, int> position);

};

king::king(bool isWhite, pair<int, int> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♚":"♔");
    inCheck = false;
    canCastle = true;
}

bool king:: IsCheck (vector<vector<piece *>> &board,pair<int,int> currPosition)
{
    //Needs to see if there is a piece that has a possible move to that square, if so the king can't move to that square

    return false; // Placeholder for actual check logic
}

