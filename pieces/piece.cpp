#include <bits/stdc++.h>
#include "piece.h"
#include "game.h"
using namespace std;

bool piece::isWhite(){return White;}

piece :: piece (bool isWhite, pos startingPosition)
: position(startingPosition), White(isWhite), printableValue(""), possibleMoves() {}

piece::piece()
: position({0,0}), White(false), printableValue(""), possibleMoves() {}

pos piece::getPosition()
{
    return this->position;
}

piece :: ~piece(){
}

void piece::updatePos(pos newPosition)
{
    this->position = newPosition;
}

string piece:: getprintableValue(){
    return printableValue;
}

void piece::setprintableValue(string newprintableValue){
    this->printableValue = newprintableValue;
}

char piece:: getType(){
    return type;
}

void piece::setType(char newType){
    this->type = newType;
}


void piece:: addPossibleMove(pos move){
    possibleMoves.insert(move);
}

void piece:: addPossibleCapture(pos move){
    possibleCaptures.insert(move);
}
set<pos> piece :: getPossibleMoves () {return possibleMoves;};
set<pos> piece :: getPossibleCaptures () {return possibleCaptures;};
 
void piece:: clearMoves(){
    possibleMoves.clear();
    possibleCaptures.clear();
}

void piece :: checkMoves(board &Board, pos currPosition){}


bool piece::Move(player *player, board &Board, pos newPosition)
{
    if (!binary_search(this->possibleMoves.begin(), this->possibleMoves.end(), newPosition))
    {
        return false; // Not a valid move at all
    }

    piece* targetOnNextSquare = Board.getAt(newPosition);
    char movingPieceType = this->getType();
    int movingPieceColor = this->isWhite() ? 1 : 0;

    bool isCapture = (targetOnNextSquare != nullptr);
    bool isEnPassantCapture = (dynamic_cast<pawn*>(this) && !isCapture && binary_search(this->possibleCaptures.begin(), this->possibleCaptures.end(), newPosition));
    bool isCastle = (dynamic_cast<king*>(this) && abs((int)(position.second-newPosition.second)) == 2);
    bool isPromotion = (dynamic_cast<pawn*>(this) && (newPosition.first == 7 || newPosition.first == 0));
    
    uint64_t newHash = Board.getPreviousHash();
    enum PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
        static const map<char, int> pieceType = {
            {'p', PAWN}, {'n', KNIGHT}, {'b', BISHOP},
            {'r', ROOK}, {'q', QUEEN}, {'k', KING}
        };

    newHash^=Board.getWhiteTurnkey();
    if (Board.getEnPassantFile() != NO_FILE) {
            newHash ^= Board.getenPassantFileKey(Board.getEnPassantFile());
    }
    newHash ^= Board.getPiecehash(pieceType.at(movingPieceType),movingPieceColor,this->position);

    // --- BRANCH 1: Capture ---
    if (isCapture && !isEnPassantCapture)
    {
        newHash ^= Board.getPiecehash(pieceType.at(movingPieceType),movingPieceColor,newPosition);
        piece* capturedPiece =Board.getAt(newPosition);
        char capturedPieceType = capturedPiece->getType();
        int capturedPieceColor = capturedPiece->isWhite() ? 1 : 0;
        newHash ^= Board.getPiecehash(pieceType.at(capturedPieceType),capturedPieceColor, newPosition);
        player->addMove({{this, moveTOstring(position)}, false});
        player->addMove({{this, moveTOstring(position)}, true});
        player->addCapture({targetOnNextSquare, moveTOstring(newPosition)});
        Board.setAt(newPosition, this);
        Board.setAt(position, nullptr);
        this->updatePos(newPosition);
        Board.resetEnpassant(); // A capture resets any en passant opportunity
        Board.resetEnPassantFile();
    }
    // --- BRANCH 2: En Passant Capture ---
    else if (isEnPassantCapture)
    {
        pos capturedPawnPos = {this->position.first, newPosition.second}; 
        newHash ^= Board.getPiecehash(pieceType.at(movingPieceType),movingPieceColor,newPosition);
        newHash ^= Board.getPiecehash(PAWN,!movingPieceColor,{capturedPawnPos.first, capturedPawnPos.second});
        player->addMove({{this, moveTOstring(position)}, true});
        Board.setAt(newPosition, this);
        Board.setAt(position, nullptr);

        int capturedPawnRow = this->isWhite() ? newPosition.first - 1 : newPosition.first + 1;
        pair<size_t, size_t> capturedPawnPos = {(size_t)capturedPawnRow, newPosition.second};
        player->addCapture({Board.getAt(capturedPawnPos), moveTOstring(capturedPawnPos)});
        Board.setAt(capturedPawnPos, nullptr);
        
        this->updatePos(newPosition);
        Board.resetEnpassant(); // An en passant capture also resets the state
        Board.resetEnPassantFile();
    }
    
    // --- BRANCH 3: Castling Move ---
    else if(isCastle)
    {
        newHash ^= Board.getPiecehash(pieceType.at(movingPieceType),movingPieceColor,newPosition);
        bool kingSide = (newPosition.second > position.second);
        player->addMove({{this,kingSide ? "0-0":"0-0-0"}, false});
        Board.setAt(newPosition, this);
        pos oldRookPos = {position.first, kingSide ? 7 : 0};
        pos newRookPos = {position.first, kingSide ? newPosition.second-1 : newPosition.second+1};
        piece* rook = Board.getAt(oldRookPos);
        newHash ^= Board.getPiecehash(ROOK,movingPieceColor,oldRookPos);
        newHash ^= Board.getPiecehash(ROOK,movingPieceColor,newRookPos);
        Board.setAt(newRookPos, rook);
        Board.setAt(oldRookPos, nullptr);
        Board.setAt(position, nullptr);
        Board.resetEnpassant();
        Board.resetEnPassantFile();
        this->updatePos(newPosition);
        rook->updatePos(newRookPos);
    }
    // --- BRANCH 4: Promotion ---
    else if (isPromotion)
    {
        piece* promotedPiece = nullptr;
        char promotionPieceType = getPromotionPiece();
        switch (promotionPieceType)
        {
        case 'q':
            promotedPiece = new queen(this->White, newPosition);
            break;
        case 'r':
            promotedPiece = new rook(this->White, newPosition);
            break;
        case 'b':
            promotedPiece = new bishop(this->White, newPosition);
            break;
        case 'n':
            promotedPiece = new Knight(this->White, newPosition);
            break;
        default:
            promotedPiece = new queen(this->White, newPosition);
            break;
        }
        newHash ^= Board.getPiecehash(pieceType.at(promotionPieceType), movingPieceColor, {newPosition.first , newPosition.second});
        player->addMove({{this, moveTOstring(position)}, false});
        Board.setAt(newPosition, promotedPiece);
        Board.setAt(position, nullptr);
        Board.resetEnpassant();
        Board.resetEnPassantFile();
    }
    

    // --- BRANCH 5: Standard Non-Capture Move ---
    else 
    {
            newHash ^= Board.getPiecehash(pieceType.at(movingPieceType),movingPieceColor,newPosition);
            Board.setAt(newPosition, this);
            Board.setAt(position, nullptr);
            
            if (pawn *p = dynamic_cast<pawn *>(this)) {
                if (abs((int)newPosition.first - (int)position.first) == 2) {
                Board.setEnpassant();
                Board.setEnPassantFile(newPosition.second);
                p->setenpassant();
            } else {
                Board.resetEnpassant();
                Board.resetEnPassantFile();
            }
        } else {
            Board.resetEnpassant();
            Board.resetEnPassantFile();
        }
        
        this->updatePos(newPosition);
    }
    
    

    
    //Reseting Castling possibility for rooks and kings as anyways once they make a move (even if that move was castling) castling should reset
    if(king *k = dynamic_cast<king *>(this)) 
    {
        k->resetCastling();
        Board.setKingPosition(k->isWhite(),newPosition);
    }
    if(rook *r = dynamic_cast<rook *>(this)) r->resetCastling();
    return true;
}
