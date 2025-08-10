#pragma once
#include <bits/stdc++.h>
#include "board.h"
using namespace std;
class player;

class piece
{
private:
    pair<size_t,size_t>  position;
    bool White;
    string value ;
    vector<pair<size_t,size_t>> possibleMoves;

public:
    piece();
    piece(bool isWhite, pair<size_t,size_t> startingPosition);
    virtual ~piece() {}
    bool isWhite(){return White;};
    void updatePos(pair<size_t,size_t> newPosition);
    pair<size_t,size_t> getPosition();
    string getValue();
    void setValue(string);
    void addPossibleMove(pair<size_t,size_t> move);
    void Move(board &Board,pair<size_t,size_t> oldPosition,pair<size_t,size_t> newPosition);
    void Capture(board &Board,pair<size_t,size_t> position,pair<size_t,size_t> capturedPosition);
    

};


class rook : public piece {
    private:
    bool canCastle;
    
    /*This Helper Function reduces redundancy in the checkmoves function
    by taking the direction either 'r'ight, 'l'eft, 'u'p or 'd'own and performing a loop on that direction
    taking into account that these directions will be reversed for black rooks, but still it does what it should be doing
    because by anymeans this will be called in all four directions, so it doesn't really matter. 
    Variations of this function will be used in other pieces for the same purpose of reducing redundancy. 
    */
   void movesHelper(board &Board, pair<size_t, size_t> currPos,char direction);
   public:
   rook(bool White, pair<size_t, size_t> startingPosition);
   bool checkRookCastle();
   void checkMoves(board &Board, pair<size_t, size_t> currPos);
};


class bishop : public piece
{
    private:
    void movesHelper(board &Board, pair<size_t,size_t> currPosition,int direction);
    public:
    bishop(bool isWhite, pair<size_t,size_t> startingPosition);
    void checkMoves(board &Board, pair<size_t,size_t> currPosition);
};


class king : public piece
{
    private:
    bool inCheck;    
    bool canCastle;
    bool IsCheck(board &Board,pair<int,int> position);
    public:
    king(bool White, pair<int, int> startingPosition);
    bool InCheck(){return inCheck;}
    void checkMoves(board &Board, pair<int, int> position);
    
};

class Knight : public piece
{
    private:
    void movesHelper(board &Board, pair<size_t,size_t> currPosition,char direction);
    public:
    Knight(bool White, pair<size_t,size_t> startingPosition);
    void checkMoves(board &Board, pair<size_t,size_t> currPosition);
};


class pawn : public piece
{
    private:
    
    bool enpassant = false;
    
    public:
    pawn(bool isWhite,pair<size_t,size_t> startingPosition);
    bool ISenpassant();
    void checkMoves(board &Board,pair<size_t,size_t> currPosition);
};

pawn::pawn(bool isWhite,pair<size_t,size_t> startingPosition)
: piece(isWhite, startingPosition)
{
    setValue(isWhite ?  "♟" : "♙");
}

bool pawn ::ISenpassant()
{
    return enpassant;
}

class queen : public piece
{
private:
void straightmovesHelper(board &Board, pair<size_t, size_t> currPosition,char direction);
void diagonalmovesHelper(board &Board, pair<size_t, size_t> currPosition,int direction);
public:
queen(bool White, pair<size_t, size_t> startingPosition);
void checkMoves(board &Board, pair<size_t, size_t> currPosition);
};



