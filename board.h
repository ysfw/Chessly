
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
#include "piece.h"
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

board::board ()
:Board(8, vector<piece*>(8, nullptr)){
    whitePieces.insert({"a1", new rook(true,{0,0})});
    whitePieces.insert({"b1", new Knight(true,{0,1})});
    whitePieces.insert({"c1", new bishop(true,{0,2})});
    whitePieces.insert({"d1", new king(true,{0,3})});
    whitePieces.insert({"e1", new queen(true,{0,4})});
    whitePieces.insert({"f1", new bishop(true,{0,5})});
    whitePieces.insert({"g1", new Knight(true,{0,6})});
    whitePieces.insert({"h1", new rook(true,{0,7})});
    for (size_t i = 0; i < 8; i++)    whitePieces.insert({string(1, 'a' + i) + "2", new pawn(true,{1,i})});

    blackPieces.insert({"a8", new rook(false,{7,0})});
    blackPieces.insert({"b8", new Knight(false,{7,1})});
    blackPieces.insert({"c8", new bishop(false,{7,2})});
    blackPieces.insert({"d8", new king(false,{7,3})});
    blackPieces.insert({"e8", new queen(false,{7,4})});
    blackPieces.insert({"f8", new bishop(false,{7,5})});
    blackPieces.insert({"g8", new Knight(false,{7,6})});
    blackPieces.insert({"h8", new rook(false,{7,7})});
    for (size_t i = 0; i < 8; i++)    blackPieces.insert({string(1, 'a' + i) + "7", new pawn(false,{6,i})});

    for(size_t i=0; i < 8; i++){
        for(size_t j=0; j < 8; j++){
            if (i == 0 || i == 1) Board[i][j] = whitePieces[static_cast<char>('a' + j) + std::to_string(i+1)];
            else if (i == 6 || i == 7) Board[i][j] = blackPieces[static_cast<char>('a' + j) + std::to_string(i+1)];
        }
    }

}

piece* board :: getAt(pair<size_t,size_t> position){
    return Board[position.first][position.second];
}

void board :: setAt(pair<size_t,size_t> position,piece* Pointer2piece){
    Board[position.first][position.second] = Pointer2piece;
}


void board :: printBoardB (){
    for (size_t i = 0; i < 8; i++)
    {
        cout<< i+1<<' ';
        for (size_t j = 0; j < 8; j++)
        {
            if (Board[i][j] == nullptr ) (i+j) % 2 == 0 ? cout<<"■" <<' ': cout<<"□"<<' ';
            else cout<<Board[i][j]->getValue()<<' ';
        }
        cout<<'\n';
    }
    cout<<"  ";
    for (size_t i = 0; i < 8; i++)
        cout << static_cast<char>('h' - i) << ' ';   
    cout<<'\n';
}


void board :: printBoardW (){
    for (int i = 7; i >= 0; i--)
    {
        cout<< i+1<<' ';
        for (int j = 7; j >= 0; j--)
        {
            if (Board[i][j] == nullptr ) (i+j) % 2 == 0 ? cout<<"■" <<' ': cout<<"□"<<' ';
            else cout<<Board[i][j]->getValue()<<' ';
            
        }
        cout<<'\n';
    }
    cout<<"  ";
    for (size_t i = 0; i < 8; i++)
        cout << static_cast<char>('a' + i) << ' ';   
    cout<<'\n';
}