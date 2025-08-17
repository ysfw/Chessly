#pragma once
#include <bits/stdc++.h>
#include "pieces/piece.h"
using namespace std;

string moveTOstring(pair<size_t,size_t> Position);
pair<size_t,size_t> stringTOmove(string move);
void clearScreen();


struct AttackInfo {
    piece* attacker; // A pointer to the piece delivering the attack
    set<pair<size_t,size_t>> path; // The squares between the attacker and a given square.
    // This will be EMPTY for direct attackers like knights and pawns.
};

class board
{
private:
    vector<vector<piece*>> Board;
    map<string,piece*> whitePieces;
    map<string,piece*> blackPieces;
    pair<size_t,size_t> whiteKingPosition;
    pair<size_t,size_t> blackKingPosition;
    bool enpassant = false , check = false , 
    checkmate = false , stalemate = false ;
public:
    board();
    vector<AttackInfo> AttackedBy(pair<size_t,size_t> Position,bool isDefenderWhite); //returns a vector containing the path of attack of pieces (bishop, rook and queen) attacking a given square and a pointer to the attacking piece
    void setKingPosition(bool isWhite, pair<size_t,size_t> newPosition);
    pair<size_t,size_t> getKingPosition(bool isWhite);
    bool isEnpassant ();
    void setEnpassant();
    void resetEnpassant();
    bool isCheck();
    void setCheck();
    void resetCheck();
    bool isMate ();
    bool isStalemate ();
    bool isTrifoldDraw ();
    bool isPinned(piece* piece, pair<size_t,size_t> newPosition);
    void setAt(pair<size_t,size_t> position,piece* Pointer2piece);
    piece* getAt(pair<size_t,size_t> position);
    void printBoardW();
    void printBoardB();
};

class player
{
private:
    bool White;
    stack<pair<pair<piece*,string>,bool>> moves;
    /*the string is a representative of the old position
    since new position is updated within the piece after each move
    and the boolean is used to check whether the move was a capture or not*/
    stack<pair<piece*,string>> captured;
    pair<piece*,string> undoneMove;
    pair<piece*,string> undoneCapture;
    pair<int,int> time; //minute:second
    int rating;
public:
    player(bool isWhite);
    bool isWhite() {return White;};
    void addMove (pair<pair<piece*,string>,bool> move);
    void addCapture (pair<piece*,string> capture);
    void undo();
    void redo();
    ~player();

};


class Normalgame
{
public:
    Normalgame();
    void run (); 
    ~Normalgame();
};