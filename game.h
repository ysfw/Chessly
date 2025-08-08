#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class player
{
private:
    bool White;
    stack<pair<pair<piece*,string>,bool>> moves; //the boolean is used to check whether the move was a capture or not
    stack<pair<piece*,string>> captured;
    pair<piece*,string> undoneMove;
    pair<piece*,string> undoneCapture;
    pair<int,int> time; //minute:second
    int rating;
public:
    player(bool isWhite);
    bool isWhite() {return White;};
    void addMove(pair<pair<piece*,string>,bool> move);
    void addCapture(pair<piece*,string> capture);
    void undo();
    void redo();
    ~player();

};

player::player(bool isWhite)
{
    this->White=isWhite;
}

void player :: addMove (pair<pair<piece*,string>,bool> move){
    this -> moves.push(move);
}

void player :: addCapture(pair<piece*,string> capture) {
    this -> captured.push(capture);
}



player::~player()
{
}
