//Use g++ -I. -o chess main.cpp game.cpp  pieces/*.cpp to compile
//chcp 65001
// valgrind --tool=memcheck --leak-check=yes ./chess

#include "game.h"

int main (){
    Normalgame game;

    while (true) {
        clearScreen();
        cout << "--- C++ Chess ---" << endl;
        cout << "1. New Game" << endl;
        cout << "2. Load from FEN" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose an option: ";

        string choice;
        cin >> choice;

        if (choice == "1") {
            board newBoard(true); 

            game.run(newBoard);   
            break; 

        } else if (choice == "2") {
            cout << "Please enter the FEN string: " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            string fenString;
            getline(cin, fenString);

            if (board* boardOptional = board::boardFromFEN(fenString)) {

                board* Board = boardOptional; 
                game.run(*Board);       
                delete Board;
                break;
            } else {
                cout << "Error: Invalid or malformed FEN string." << endl;
                cout << "Press Enter to return to the menu." << endl;
                cin.get();
            }

        } else if (choice == "3") {
            cout << "Exiting." << endl;
            break;

        } else {
            cout << "Invalid choice. Press Enter to try again." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    return 0;
}

//Remaining Stuff to be done before moving to GUI 


/*
- fixing notation to the PGN
- saving positions
- redo/undo moves
- Refactor and optimize if possible
- adding the stockfish functionality to play 1 Vs bot and evaluate game
(possibly and might be left to do in the GUI version)
*/
