#pragma once
#include <bits/stdc++.h>
#include "pieces/piece.h"
using namespace std;


//Helper Functions
string moveTOstring(pos Position);
pos stringTOmove(string move);
char getPromotionPiece();
void clearScreen();


struct AttackInfo {
    //<<<<<<< This turned out to be totally useless I'll need to remove it later....
    piece* attacker; // A pointer to the piece delivering the attack
    set<pos> path; // The squares between the attacker and a given square.
    // This will be EMPTY for direct attackers like knights and pawns.
};

const int NO_FILE = -1; 

class board
{
private:
    vector<vector<piece*>> Board;
    const std::string layout[8] = {
        "RNBQKBNR",
        "PPPPPPPP",
        "........",
        "........",
        "........",
        "........",
        "pppppppp",
        "rnbqkbnr"
    }; //White Pieces in Capital letters
    

    
    /*Using Zobrist table & keys for threefold repetition draw logic
    - this is way more efficient than saving the whole board 
    - it works by genarating a random number (key) for each piece of each color on each square
    in the beginning of each game and then Xor all keys for each position int a one unique hash
    that represents the whole game state
    - the use of uint64_t here is typically for portability and safety*/
    uint64_t zobristTable[6][2][64]; 
    uint64_t WhiteTurnkey;
    uint64_t castlingKeys[4];  // [BKSide, BQSide, WKSide , WQSide]
    uint64_t enPassantFileKeys[8];
    uint64_t calculateZobristHash(); //Making it private because it won't be used each time only for the initial position
    void initZobrist();
    unordered_map<uint64_t,int> zobristHistory; // {hash, #occurences}
    uint64_t PreviousHash;
    pos whiteKingPosition;
    pos blackKingPosition;
    bool whiteTurn;
    bool enpassant = false;
    int enPassantFile;
    piece* createPieceFromChar(char pieceChar, pos position);
public:
    board(bool FullBoardInit);
    // true for normal game -> initialized full board

    bool isWhiteTurn();
    void switchTurns();
    void setAt(pos position,piece* Pointer2piece);
    piece* getAt(pos position);
    vector<AttackInfo> AttackedBy(pos Position,bool isDefenderWhite); //returns a vector containing the path of attack of pieces (bishop, rook and queen) attacking a given square and a pointer to the attacking piece
    bool isPinned(piece* piece, pos newPosition);
    void setKingPosition(bool isWhite, pos newPosition);
    pos getKingPosition(bool isWhite);
    
    uint64_t getPiecehash(char piece,bool isWhite,pos position);
    uint64_t getPreviousHash();
    uint64_t getWhiteTurnkey();
    uint64_t getcastlingKey(int side,bool isWhite);
    uint64_t getenPassantFileKey(int file);
    void addHash (uint64_t newHash);

    void setPreviousHash(uint64_t newHash);

    void makeHash(pos from, pos to, char promotionPieceType = '.');

    bool isEnpassant ();
    void setEnpassant();
    void resetEnpassant();
    int getEnPassantFile();
    void setEnPassantFile(int file);
    void resetEnPassantFile();
    
    bool isCheckmate (bool isWhiteTurn);
    bool isStalemate (bool isWhiteTurn);
    bool isTrifoldDraw ();
    
    void printBoardW();
    void printBoardB();
};

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


class Normalgame
{
public:
    Normalgame();
    void run (); 
    ~Normalgame();
};