//Use g++ -std=c++17 -Wall -Wextra -I. -o chess main.cpp game.cpp  pieces/*.cpp to compile
//chcp 65001


#include <bits/stdc++.h>
#include "board.h"
#include "player.h"
#include "helpers.h"
using namespace std;

int main (){
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
        return 0;
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