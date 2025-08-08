#include <bits/stdc++.h>
#include "board.h"
#include "game.h"
using namespace std;

int main (){
board board;
player White = player (true);
player Black = player (false);
while (true){
    board.printBoardW();
    string input;
    cout << "Select a piece (e.g., e2 e4) or type exit: ";
    getline(cin, input);
    if (input == "exit") {
        cout << "Exiting the game." << endl;
        break;
    }
    


    
}