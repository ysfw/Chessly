#pragma once
#include <bits/stdc++.h>
using namespace std;
class player;
class board;
class game;

class piece
{
private:
    pair<size_t,size_t> position;
    bool White;
    string value ;
    set<pair<size_t,size_t>> possibleMoves;
    set<pair<size_t,size_t>> possibleCaptures;

public:
    piece();
    piece(bool isWhite, pair<size_t,size_t> startingPosition);
    virtual ~piece();
    bool isWhite();
    void updatePos(pair<size_t,size_t> newPosition);
    pair<size_t,size_t> getPosition();
    string getValue();
    void setValue(string);
    void addPossibleMove(pair<size_t,size_t> move);
    void addPossibleCapture(pair<size_t,size_t> move);
    set<pair<size_t,size_t>> getPossibleMoves ();
    set<pair<size_t,size_t>> getPossibleCaptures ();
    bool Move(player *player,board &Board,pair<size_t,size_t> newPosition);
    virtual void checkMoves(board &Board, pair<size_t,size_t> currPosition);
    void clearMoves();

};


class rook : public piece {
private:
    bool canCastle;
public:
   rook(bool White, pair<size_t, size_t> startingPosition);
   bool checkRookCastle();
   void checkMoves(board &Board, pair<size_t, size_t> currPos)override;
};


class bishop : public piece
{
public:
    bishop(bool isWhite, pair<size_t,size_t> startingPosition);
    void checkMoves(board &Board, pair<size_t,size_t> currPosition)override;
};


class king : public piece
{
private: 
    bool canCastle;
public:
    king(bool White, pair<int, int> startingPosition);
    void checkMoves(board &Board, pair<size_t, size_t> position)override;
    
};

class Knight : public piece
{
    public:
    Knight(bool White, pair<size_t,size_t> startingPosition);
    void checkMoves(board &Board, pair<size_t,size_t> currPosition)override;
};


class pawn : public piece
{
    private:
    
    bool enpassant = false;
    
    public:
    bool ISenpassant();
    void setenpassant();
    void resetenpassant();
    pawn(bool isWhite,pair<size_t,size_t> startingPosition);
    void checkMoves(board &Board,pair<size_t,size_t> currPosition)override;
};



class queen : public piece
{
public:
queen(bool White, pair<size_t, size_t> startingPosition);
void checkMoves(board &Board, pair<size_t, size_t> currPosition)override;
};



