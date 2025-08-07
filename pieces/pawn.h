#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class pawn : public piece
{
private:
    
    bool enpassant = false;

public:
    pawn(bool White, pair<int, int> startingPosition);
    bool ISenpassant();
    void checkMoves(vector<vector<piece*>>& board, pair<int, int> position);
};

pawn::pawn(bool White, pair<int, int> startingPosition)
    : piece(White, startingPosition)
{
    setValue(White ?  "♟" : "♙");
}

bool pawn ::ISenpassant()
{
    return enpassant;
}

void pawn ::checkMoves(vector<vector<piece*>>& board, pair<int, int> position)
{
    if (this->isWhite())
    {
        if (position.first+1 < 8){
            if(position.first==6){
                //Check promotion !!
            }
            if (position.first == 2)
            {
                if (board[3][position.second]==nullptr)
                    this->addPossibleMove({3, position.second});
                if (board[4][position.second]==nullptr)
                {
                    this->addPossibleMove({4, position.second});
                    enpassant = true;
                }
            }
            else if (board[position.first + 1][position.second]==nullptr)
            {
                this->addPossibleMove({position.first + 1, position.second});
                enpassant = false;
            }
            
            if (position.second+1<8 &&(board[position.first + 1][position.second+1] != nullptr))
            {
                if(!board[position.first + 1][position.second+1]->isWhite()){
                    //Capturable Diagonally to the right
                }
                if (pawn* p = dynamic_cast<pawn*>(board[position.first][position.second+1])) {
                    if(p->ISenpassant()) //en passant , Capturable Diagonally to the right
                    ; 
                }
                    
            }

            if (position.second-1>=0 &&(board[position.first + 1][position.second-1]!= nullptr))
            {
                if(!board[position.first + 1][position.second-1]->isWhite()){
                    //Capturable Diagonally to the left
                }
                if (pawn* p = dynamic_cast<pawn*>(board[position.first][position.second-1])) {
                    if(p->ISenpassant()) //en passant , Capturable Diagonally to the right
                    ; 
                }
            }
        }
    }
    else
    {
        if (position.first-1 >=0){
            if(position.first==1){
                //Check promotion !!
            }
            if (position.first == 7)
            {
                if (board[6][position.second] ==nullptr)
                    this->addPossibleMove({6, position.second});
                if (board[5][position.second]==nullptr)
                {
                    this->addPossibleMove({5, position.second});
                    enpassant = true;
                }
            }
            else if (board[position.first - 1][position.second] == nullptr)
            {
                this->addPossibleMove({position.first - 1, position.second});
                enpassant = false; //reseting enpassant possiblity after 1 extra move if it was true
            }
            if (position.second+1<8 &&(board[position.first - 1][position.second+1]!=nullptr))
            {
                if(!board[position.first - 1][position.second+1]->isWhite()){
                    //Capturable Diagonally to the left
                }
                if (pawn* p = dynamic_cast<pawn*>(board[position.first][position.second+1])) {
                    if(p->ISenpassant()) //en passant , Capturable Diagonally to the left
                    ; 
                }
                    
            }

            if (position.second-1>=0 &&(board[position.first - 1][position.second-1]!=nullptr))
            {
                if(!board[position.first - 1][position.second-1]->isWhite()){
                    //Capturable Diagonally to the left
                }
                if (pawn* p = dynamic_cast<pawn*>(board[position.first][position.second-1])) {
                    if(p->ISenpassant()) //en passant , Capturable Diagonally to the left
                    ; 
                }
            }

        }
       
    }
}