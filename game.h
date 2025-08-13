#pragma once
#include <bits/stdc++.h>
#include "pieces/piece.h"
using namespace std;

string moveTOstring(pair<size_t,size_t> Position);
pair<size_t,size_t> stringTOmove(string move);
void clearScreen();


class board
{
private:
    vector<vector<piece*>> Board;
    map<string,piece*> whitePieces;
    map<string,piece*> blackPieces;
    bool enpassant = false , check = false , 
    checkmate = false , stalemate = false ;
public:
    board();
    vector<pair<unsigned int,unsigned int>> AttackedBy(pair<size_t,size_t> position); 
    //returns a vector containing positions of pieces attacking a given square
    bool isEnpassant ();
    void setEnpassant();
    void resetEnpassant();
    bool isMate ();
    bool isStalemate ();
    bool isTrifoldDraw ();

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