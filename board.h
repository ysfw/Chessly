//{R,N,B,K,Q,N,R}
//8*P
//4 checkered rows
//8*P
//{R,N,B,K,Q,N,R}

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



enum alpha {
    a=0,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
 };

class board
{
private:
    vector<vector<piece*>> Board;
    vector<piece> whitePieces;
    vector<piece> blackPieces;
public:
    board();
    vector<pair<int,int>> AttackedBy(pair<int,int> position); 
    //returns a vector containing positions of pieces attacking a given square

    void setAt(pair<int,int> position,piece* Pointer2piece);
    piece* getAt(pair<int,int> position);
    void printBoardW();
    void printBoardB();
};

board::board ()
:Board(8, vector<piece*>(8, nullptr)){
    
}

piece* board :: getAt(pair<int,int> position){
    return Board[position.first][position.second];
}

void board :: setAt(pair<int,int> position,piece* Pointer2piece){
    Board[position.first][position.second] = Pointer2piece;
}


void board :: printBoardB (){
    for (size_t i = 0; i < 8; i++)
    {
        cout<< i+1<<' ';
        for (size_t j = 0; j < 8; j++)
        {
            cout<<Board[i][j]->getValue()<<' ';
            
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
            cout<<Board[i][j]->getValue()<<' ';
            
        }
        cout<<'\n';
    }
    cout<<"  ";
    for (int i = 0; i < 8; i++)
        cout << static_cast<char>('a' + i) << ' ';   
    cout<<'\n';
}