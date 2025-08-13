#pragma once
#include <bits/stdc++.h>
#include "piece.h"
#include "game.h"
using namespace std;

bool piece::isWhite(){return White;}
set<pair<size_t,size_t>> piece :: getPossibleMoves () {return possibleMoves;};
set<pair<size_t,size_t>> piece :: getPossibleCaptures () {return possibleCaptures;};

piece :: piece (bool isWhite, pair<size_t,size_t> startingPosition)
    : position(startingPosition), White(isWhite), value(""), possibleMoves() {}

piece::piece()
    : position({0,0}), White(false), value(""), possibleMoves() {}

pair<size_t,size_t> piece::getPosition()
{
    return this->position;
}

piece :: ~piece(){
}

void piece::updatePos(pair<size_t,size_t> newPosition)
{
    this->position = newPosition;
}

string piece:: getValue(){
    return value;
}

void piece::setValue(string newValue){
    this->value = newValue;
}

void piece:: addPossibleMove(pair<size_t,size_t> move){
    possibleMoves.insert(move);
}

void piece:: addPossibleCapture(pair<size_t,size_t> move){
    possibleCaptures.insert(move);
}

void piece:: clearMoves(){
    possibleMoves.clear();
    possibleCaptures.clear();
}

void piece :: checkMoves(board &Board, pair<size_t,size_t> currPosition){}


bool piece::Move(player *player, board &Board, pair<size_t, size_t> newPosition)
{
    if (!binary_search(this->possibleMoves.begin(), this->possibleMoves.end(), newPosition))
    {
        return false; // Not a valid move at all
    }

    piece* targetOnNextSquare = Board.getAt(newPosition);
    bool isCapture = (targetOnNextSquare != nullptr);
    bool isEnPassantCapture = (dynamic_cast<pawn*>(this) && !isCapture && binary_search(this->possibleCaptures.begin(), this->possibleCaptures.end(), newPosition));


    // --- BRANCH 1: Standard Capture ---
    if (isCapture && !isEnPassantCapture)
    {
        player->addMove({{this, moveTOstring(position)}, true});
        player->addCapture({targetOnNextSquare, moveTOstring(newPosition)});
        Board.setAt(newPosition, this);
        Board.setAt(position, nullptr);
        this->updatePos(newPosition);
        Board.resetEnpassant(); // A capture resets any en passant opportunity
    }
    // --- BRANCH 2: En Passant Capture ---
    else if (isEnPassantCapture)
    {
        player->addMove({{this, moveTOstring(position)}, true});
        Board.setAt(newPosition, this);
        Board.setAt(position, nullptr);

        int capturedPawnRow = this->isWhite() ? newPosition.first - 1 : newPosition.first + 1;
        pair<size_t, size_t> capturedPawnPos = {(size_t)capturedPawnRow, newPosition.second};
        player->addCapture({Board.getAt(capturedPawnPos), moveTOstring(capturedPawnPos)});
        Board.setAt(capturedPawnPos, nullptr);
        
        this->updatePos(newPosition);
        Board.resetEnpassant(); // An en passant capture also resets the state
    }
    // --- BRANCH 3: Standard Non-Capture Move ---
    else 
    {
        player->addMove({{this, moveTOstring(position)}, false});
        Board.setAt(newPosition, this);
        Board.setAt(position, nullptr);

        if (pawn *p = dynamic_cast<pawn *>(this)) {
            if (abs((int)newPosition.first - (int)position.first) == 2) {
                Board.setEnpassant();
                p->setenpassant();
            } else {
                Board.resetEnpassant();
            }
        } else {
            Board.resetEnpassant();
        }

        this->updatePos(newPosition);
    }

    return true;
}