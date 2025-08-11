#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

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

void player :: addMove (pair<pair<piece*,string>,bool> move){
    moves.push(move);
}

void player:: addCapture (pair<piece*,string> capture)
{
    captured.push(capture);
}
player::player(bool isWhite)
{
    this->White=isWhite;
}


player::~player()
{
}
