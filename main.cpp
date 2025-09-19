//Use g++ -I. -o chess main.cpp game.cpp  pieces/*.cpp to compile
//chcp 65001
// valgrind --tool=memcheck --leak-check=yes ./chess

#include "game.h"
int main() {
    game game;

    while (true) {
          clearScreen();
        cout << "--- Chessly ---" << endl;
        cout << "1. New Game" << endl;
        cout << "2. Load from FEN" << endl;
        cout << "3. Load Saved Game" << endl;
        cout << "4. Exit" << endl;
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
                 } else {
                cout << "Error: Invalid or malformed FEN string." << endl;
                cout << "Press Enter to return to the menu." << endl;
                cin.get();
            }

        } else if (choice == "3") {
            cout << "Loading saved games..." << endl;
            game.loadGame();
        } 

        else if (choice == "4") {
            cout << "Exiting." << endl;
            break;
             } else {
            cout << "Invalid choice. Press Enter to try again." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            }
        }
}
