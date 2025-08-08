#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class pawn : public piece
{
private:
    
    bool enpassant = false;

public:
    pawn(bool isWhite,pair<size_t,size_t> startingPosition);
    bool ISenpassant();
    void checkMoves(vector<vector<piece*>>& board,pair<size_t,size_t> currPosition);
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

void pawn ::checkMoves(vector<vector<piece*>>& board,pair<size_t,size_t> currPosition)
{
    if (this->isWhite())
    {
        if (currPosition.first+1 < 8){
            if(currPosition.first==6){
                //Check promotion !!
            }
            if (currPosition.first == 2)
            {
                if (board[3][currPosition.second]==nullptr)
                    this->addPossibleMove({3, currPosition.second});
                if (board[4][currPosition.second]==nullptr)
                {
                    this->addPossibleMove({4, currPosition.second});
                    enpassant = true;
                }
            }
            else if (board[currPosition.first + 1][currPosition.second]==nullptr)
            {
                this->addPossibleMove({currPosition.first + 1, currPosition.second});
                enpassant = false;
            }

            if (currPosition.second+1<8 &&(board[currPosition.first + 1][currPosition.second+1] != nullptr))
            {
                if(!board[currPosition.first + 1][currPosition.second+1]->isWhite()){
                    //Capturable Diagonally to the right
                }
                if (pawn* p = dynamic_cast<pawn*>(board[currPosition.first][currPosition.second+1])) {
                    if(p->ISenpassant()){} //en passant , Capturable Diagonally to the right
                }
                    
            }

            if (currPosition.second-1 < 8 &&(board[currPosition.first + 1][currPosition.second-1]!= nullptr))
            {
                if(!board[currPosition.first + 1][currPosition.second-1]->isWhite()){
                    //Capturable Diagonally to the left
                }
                if (pawn* p = dynamic_cast<pawn*>(board[currPosition.first][currPosition.second-1])) {
                    if(p->ISenpassant()){} //en passant , Capturable Diagonally to the right
                }
            }
        }
    }
    else
    {
        if (currPosition.first-1 < 8){
            if(currPosition.first==1){
                //Check promotion !!
            }
            if (currPosition.first == 7)
            {
                if (board[6][currPosition.second] ==nullptr)
                    this->addPossibleMove({6, currPosition.second});
                if (board[5][currPosition.second]==nullptr)
                {
                    this->addPossibleMove({5, currPosition.second});
                    enpassant = true;
                }
            }
            else if (board[currPosition.first - 1][currPosition.second] == nullptr)
            {
                this->addPossibleMove({currPosition.first - 1, currPosition.second});
                enpassant = false; //reseting enpassant possiblity after 1 extra move if it was true
            }
            if (currPosition.second+1<8 &&(board[currPosition.first - 1][currPosition.second+1]!=nullptr))
            {
                if(!board[currPosition.first - 1][currPosition.second+1]->isWhite()){
                    //Capturable Diagonally to the left
                }
                if (pawn* p = dynamic_cast<pawn*>(board[currPosition.first][currPosition.second+1])) {
                    if(p->ISenpassant()){} //en passant , Capturable Diagonally to the left
                }
                    
            }

            if (currPosition.second-1 < 8 &&(board[currPosition.first - 1][currPosition.second-1]!=nullptr))
            {
                if(!board[currPosition.first - 1][currPosition.second-1]->isWhite()){
                    //Capturable Diagonally to the left
                }
                if (pawn* p = dynamic_cast<pawn*>(board[currPosition.first][currPosition.second-1])) {
                    if(p->ISenpassant()){} //en passant , Capturable Diagonally to the left
                }
            }

        }
       
    }
}