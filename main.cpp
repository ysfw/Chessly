//Use g++ -I. -o chess main.cpp game.cpp  pieces/*.cpp to compile
//chcp 65001
// valgrind --tool=memcheck --leak-check=yes ./chess

#include "game.h"
int main() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    string menuItems[] = {"New Game", "Load from FEN", "Exit"};
    int choice;
    int highlight = 0;

    game game;

    while (true) {
        clear();
        mvprintw(0, 0, "--- Chessly ---");
        for (int i = 0; i < 3; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(i + 2, 2, menuItems[i].c_str());
            attroff(A_REVERSE);
        }

        choice = getch();

        switch (choice) {
            case KEY_UP:
                highlight = (highlight - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % 3;
                break;
            case 10:
                if (highlight == 0) {
                    {
                        board newBoard(true);
                        endwin();
                        game.run(newBoard);
                        return 0;
                    }
                } else if (highlight == 1) {
                    {
                        endwin();
                        cout << "Please enter the FEN string: " << endl;
                        string fenString;
                        getline(cin, fenString);

                        if (board* boardOptional = board::boardFromFEN(fenString)) {
                            board* Board = boardOptional;
                            game.run(*Board);
                            delete Board;
                            return 0;
                        } else {
                            cout << "Invalid or malformed FEN string." << endl;
                            cout << "Press Enter to return to the menu." << endl;
                            cin.get();
                            initscr();
                            noecho();
                            cbreak();
                            keypad(stdscr, TRUE);
                        }
                    }
                } else if (highlight == 2) { // Exit
                    endwin();
                    cout << "Exiting." << endl;
                    return 0;
                }
                break;
        }
    }

    endwin();
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
