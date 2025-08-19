//Use g++ -I. -o chess main.cpp game.cpp  pieces/*.cpp to compile
//chcp 65001

#include "game.h"

int main (){
    Normalgame game;
    game.run();
}

//Remaining Stuff to be done before moving to GUI 


/*
- Trifold Draw
- 50/75 move rules
- fixing notation to the standard
- FEN
- saving and loading positions
- redo/undo moves
- Refactor and optimize if possible
- adding the stockfish functionality to play 1 Vs bot and evaluate game
(possibly and might be left to do in the GUI version)
*/
