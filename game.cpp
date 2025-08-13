#include <bits/stdc++.h>
#include "game.h"
using namespace std;

void clearScreen() {
#ifdef _WIN32 // For Windows
    system("cls");
#else // For Unix-like systems (Linux, macOS)
    system("clear");
#endif
}



string moveTOstring(pair<size_t,size_t> Position){
    string move="";
    move+=(static_cast<char>('a' + Position.second));
    move+= to_string(Position.first+1);
    return move;
}

pair<size_t,size_t> stringTOmove(string move){
    size_t col, row;
    char file = move [0], rank = move[1];
    col = static_cast<size_t>(file - 'a');
    row = static_cast<size_t>(rank - '0') - 1;
    return {row, col};
}

board::board ()
:Board(8, vector<piece*>(8, nullptr)){
    whitePieces.insert({"a1", new rook(true,{0,0})});
    whitePieces.insert({"b1", new Knight(true,{0,1})});
    whitePieces.insert({"c1", new bishop(true,{0,2})});
    whitePieces.insert({"e1", new king(true,{0,4})});
    whitePieces.insert({"d1", new queen(true,{0,3})});
    whitePieces.insert({"f1", new bishop(true,{0,5})});
    whitePieces.insert({"g1", new Knight(true,{0,6})});
    whitePieces.insert({"h1", new rook(true,{0,7})});
    for (size_t i = 0; i < 8; i++)    whitePieces.insert({string(1, 'a' + i) + "2", new pawn(true,{1,i})});

    blackPieces.insert({"a8", new rook(false,{7,0})});
    blackPieces.insert({"b8", new Knight(false,{7,1})});
    blackPieces.insert({"c8", new bishop(false,{7,2})});
    blackPieces.insert({"e8", new king(false,{7,4})});
    blackPieces.insert({"d8", new queen(false,{7,3})});
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

bool board :: isEnpassant () {
    return enpassant;
}

void board :: setEnpassant () {
    enpassant = true;
}

void board :: resetEnpassant() {
    enpassant = false;
}

void board :: printBoardB (){
    for (size_t i = 0; i < 8; i++)
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
        cout << static_cast<char>('h' - i) << ' ';   
    cout<<'\n';
}


void board :: printBoardW (){
    for (int i = 7; i >= 0; i--)
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
        cout << static_cast<char>('a' + i) << ' ';   
    cout<<'\n';
}

void player :: addMove (pair<pair<piece*,string>,bool> move){
    moves.push(move);
}

void player:: addCapture (pair<piece*,string> capture)
{
    captured.push(capture);
}
player::player(bool isWhite)
{
    this->White=isWhite;
}


player::~player()
{
}



Normalgame::Normalgame(/* args */)
{
}

Normalgame::~Normalgame()
{
}

void Normalgame :: run (){
    board board;
    player White = player (true);
    player Black = player (false);
    bool whiteTurn = true;
    regex e ("^[a-hA-H][1-8]$");
    while (true){
        clearScreen();
        whiteTurn ? board.printBoardW() : board.printBoardB();
        string input;
        cout << "Select a piece (e.g., e2 e4) or type exit: ";
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "exit") {
            cout << "Exiting the game." << endl;
            return ;
        }
        
        else if (regex_match(input,e)){
            pair<size_t,size_t> position = stringTOmove(input);
            piece* selected = board.getAt(position);
            if(selected == nullptr || whiteTurn != selected->isWhite()){
                cout<<"Illegal move"<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));
                continue;
            }

            clearScreen();
            whiteTurn ? board.printBoardW() : board.printBoardB();
            selected->checkMoves(board,position);
            set<pair<size_t,size_t>> moves = selected -> getPossibleMoves();
            set<pair<size_t,size_t>> captures = selected -> getPossibleCaptures();
            if(moves.empty())
            {
                cout<<"No possible moves"<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));
                continue;
            }
            cout<< "Possible moves (Red is capturable): ";
            for(pair<size_t,size_t> move : moves){
                string moveString = moveTOstring(move);
                if(binary_search(captures.begin(),captures.end(),move)){
                    moveString = "\x1b[31m" + moveString + "\x1b[0m";
                }
                cout<< moveString <<"  ";

            }
            cout<<endl;
            cout << "Play a move or type \"back\" to select another piece : ";
            cin >> input;
            transform(input.begin(), input.end(), input.begin(), ::tolower);
            if (input == "back") continue;
            else {
                if(regex_match(input,e) && selected->Move(whiteTurn? &White : &Black, board,stringTOmove(input))){
                    whiteTurn = !whiteTurn;
                    continue;
                }
                else{
                    cout<<"Illegal move"<<endl;
                    this_thread::sleep_for(std::chrono::seconds(7));
                    continue;
                }
            }
            
        }
        else{
            cout<<"Invalid position"<<endl;
            this_thread::sleep_for(chrono::seconds(3));
            continue;
        }
        
        

    }
}
