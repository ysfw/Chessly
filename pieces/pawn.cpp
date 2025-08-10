#include "piece.h"


void pawn ::checkMoves(board &Board,pair<size_t,size_t> currPosition)
{
    if (this->isWhite())
    {
        if (currPosition.first+1 < 8){
            if(currPosition.first==6){
                //Check promotion !!
            }
            if (currPosition.first == 2)
            {
                if (Board.getAt({3,currPosition.second})==nullptr)
                    this->addPossibleMove({3, currPosition.second});
                if (Board.getAt({4,currPosition.second})==nullptr)
                {
                    this->addPossibleMove({4, currPosition.second});
                    enpassant = true;
                }
            }
            else if (Board.getAt({currPosition.first + 1,currPosition.second})==nullptr)
            {
                this->addPossibleMove({currPosition.first + 1, currPosition.second});
                enpassant = false;
            }

            if (currPosition.second+1<8 &&(Board.getAt({currPosition.first + 1,currPosition.second+1}) != nullptr))
            {
                if(!Board.getAt({currPosition.first + 1,currPosition.second+1})->isWhite()){
                    //Capturable Diagonally to the right
                }
                if (pawn* p = dynamic_cast<pawn*>(Board.getAt({currPosition.first,currPosition.second+1}))) {
                    if(p->ISenpassant()){} //en passant , Capturable Diagonally to the right
                }
                    
            }

            if (currPosition.second-1 < 8 &&(Board.getAt({currPosition.first + 1,currPosition.second-1})!= nullptr))
            {
                if(!Board.getAt({currPosition.first + 1,currPosition.second-1})->isWhite()){
                    //Capturable Diagonally to the left
                }
                if (pawn* p = dynamic_cast<pawn*>(Board.getAt({currPosition.first,currPosition.second-1}))) {
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
                if (Board.getAt({6,currPosition.second}) ==nullptr)
                    this->addPossibleMove({6, currPosition.second});
                if (Board.getAt({5,currPosition.second})==nullptr)
                {
                    this->addPossibleMove({5, currPosition.second});
                    enpassant = true;
                }
            }
            else if (Board.getAt({currPosition.first - 1,currPosition.second}) == nullptr)
            {
                this->addPossibleMove({currPosition.first - 1, currPosition.second});
                enpassant = false; //reseting enpassant possiblity after 1 extra move if it was true
            }
            if (currPosition.second+1<8 &&(Board.getAt({currPosition.first-1,currPosition.second+1})!=nullptr))
            {
                if(!Board.getAt({currPosition.first - 1,currPosition.second+1})->isWhite()){
                    //Capturable Diagonally to the left
                }
                if (pawn* p = dynamic_cast<pawn*>(Board.getAt({currPosition.first,currPosition.second+1}))) {
                    if(p->ISenpassant()){} //en passant , Capturable Diagonally to the left
                }
                    
            }

            if (currPosition.second-1 < 8 &&(Board.getAt({currPosition.first-1,currPosition.second-1})!=nullptr))
            {
                if(!Board.getAt({currPosition.first-1,currPosition.second-1})->isWhite()){
                    //Capturable Diagonally to the left
                }
                if (pawn* p = dynamic_cast<pawn*>(Board.getAt({currPosition.first,currPosition.second-1}))) {
                    if(p->ISenpassant()){} //en passant , Capturable Diagonally to the left
                }
            }

        }
       
    }
}