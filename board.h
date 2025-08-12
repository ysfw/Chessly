
//     string Board[8][8] = {
//     {"♜","♞","♝","♚","♛","♝","♞","♜"},
//     {"♟","♟","♟","♟","♟","♟","♟","♟"},
//     {"■","□","■","□","■","□","■","□"},
//     {"□","■","□","■","□","■","□","■"},
//     {"■","□","■","□","■","□","■","□"},
//     {"□","■","□","■","□","■","□","■"},
//     {"♙","♙","♙","♙","♙","♙","♙","♙"},
//     {"♖","♘","♗","♔","♕","♗","♘","♖"}
// };




#pragma once
#include <bits/stdc++.h>
#include "pieces/piece.h"
using namespace std;


class board
{
private:
    vector<vector<piece*>> Board;
    map<string,piece*> whitePieces;
    map<string,piece*> blackPieces;
public:
    board();
    vector<pair<unsigned int,unsigned int>> AttackedBy(pair<size_t,size_t> position); 
    //returns a vector containing positions of pieces attacking a given square

    void setAt(pair<size_t,size_t> position,piece* Pointer2piece);
    piece* getAt(pair<size_t,size_t> position);
    void printBoardW();
    void printBoardB();
};

