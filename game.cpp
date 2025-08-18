#include <bits/stdc++.h>
#include "game.h"
using namespace std;

void clearScreen()
{
#ifdef _WIN32 // For Windows
    system("cls");
#else // For Unix-like systems (Linux, macOS)
    system("clear");
#endif
}

string moveTOstring(pos Position)
{
    string move = "";
    move += (static_cast<char>('a' + Position.second));
    move += to_string(Position.first + 1);
    return move;
}

pos stringTOmove(string move)
{
    size_t col, row;
    char file = move[0], rank = move[1];
    col = static_cast<size_t>(file - 'a');
    row = static_cast<size_t>(rank - '0') - 1;
    return {row, col};
}

board::board()
    : Board(8, vector<piece *>(8, nullptr))
{
    whitePieces.insert({"a1", new rook(true, {0, 0})});
    whitePieces.insert({"b1", new Knight(true, {0, 1})});
    whitePieces.insert({"c1", new bishop(true, {0, 2})});
    whitePieces.insert({"e1", new king(true, {0, 4})});
    setKingPosition(true, {0, 4});
    whitePieces.insert({"d1", new queen(true, {0, 3})});
    whitePieces.insert({"f1", new bishop(true, {0, 5})});
    whitePieces.insert({"g1", new Knight(true, {0, 6})});
    whitePieces.insert({"h1", new rook(true, {0, 7})});
    for (size_t i = 0; i < 8; i++)
        whitePieces.insert({string(1, 'a' + i) + "2", new pawn(true, {1, i})});

    blackPieces.insert({"a8", new rook(false, {7, 0})});
    blackPieces.insert({"b8", new Knight(false, {7, 1})});
    blackPieces.insert({"c8", new bishop(false, {7, 2})});
    blackPieces.insert({"e8", new king(false, {7, 4})});
    setKingPosition(false, {7, 4});
    blackPieces.insert({"d8", new queen(false, {7, 3})});
    blackPieces.insert({"f8", new bishop(false, {7, 5})});
    blackPieces.insert({"g8", new Knight(false, {7, 6})});
    blackPieces.insert({"h8", new rook(false, {7, 7})});
    for (size_t i = 0; i < 8; i++)
        blackPieces.insert({string(1, 'a' + i) + "7", new pawn(false, {6, i})});

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (i == 0 || i == 1)
                Board[i][j] = whitePieces[static_cast<char>('a' + j) + std::to_string(i + 1)];
            else if (i == 6 || i == 7)
                Board[i][j] = blackPieces[static_cast<char>('a' + j) + std::to_string(i + 1)];
        }
    }
}

board::~board() {
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            if (Board[i][j] != nullptr) {
                delete Board[i][j];
                Board[i][j] = nullptr;
            }
        }
    }
}

piece *board ::getAt(pos position)
{
    return Board[position.first][position.second];
}

void board ::setAt(pos position, piece *Pointer2piece)
{
    Board[position.first][position.second] = Pointer2piece;
}

bool board ::isEnpassant()
{
    return enpassant;
}

void board ::setEnpassant()
{
    enpassant = true;
}

void board ::resetEnpassant()
{
    enpassant = false;
}

void board::setKingPosition(bool isWhite, pos newPosition)
{
    isWhite ? whiteKingPosition = newPosition : blackKingPosition = newPosition;
}

pos board ::getKingPosition(bool isWhite)
{
    return isWhite ? whiteKingPosition : blackKingPosition;
}

vector<AttackInfo> board ::AttackedBy(pos Position, bool isDefenderWhite)
{
    vector<AttackInfo> result;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (this->getAt({i, j}) == nullptr || this->getAt({i, j})->isWhite() == isDefenderWhite)
            {
                continue;
            }
            else
            {
                set<pos> possiblePath;
                AttackInfo currAttk;
                if (pawn *p = dynamic_cast<pawn *>(this->getAt({i, j})))
                {
                    int forwardOne = p->isWhite() ? p->getPosition().first + 1 : p->getPosition().first - 1;
                    if (forwardOne == Position.first && (Position.second == p->getPosition().second + 1 || Position.second == p->getPosition().second - 1))
                    {
                        currAttk.attacker = p;
                        currAttk.path = possiblePath;
                        result.push_back(currAttk);
                    }
                }
                else if (Knight *N = dynamic_cast<Knight *>(this->getAt({i, j})))
                {
                    pair<int, int> directions[8] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
                    for (pair<int, int> direction : directions)
                    {
                        int firstCoord = (int)N->getPosition().first + direction.first;
                        int secondCoord = (int)N->getPosition().second + direction.second;
                        if ((firstCoord < 8 && firstCoord >= 0 && secondCoord < 8 && secondCoord >= 0) && (firstCoord == Position.first && secondCoord == Position.second))
                        {
                            currAttk.attacker = N;
                            currAttk.path = possiblePath;
                            result.push_back(currAttk);
                        }
                    }
                }
                else if (rook *R = dynamic_cast<rook *>(this->getAt({i, j})))
                {
                    for (int direction = 1; direction < 5; direction++)
                    {
                        possiblePath.clear();

                        for (size_t k = 1; k < 8; k++)
                        {
                            size_t firstCoord, secondCoord;

                            switch (direction)
                            {
                            case 1:
                                firstCoord = i;
                                secondCoord = j + k;
                                break;
                            case 2:
                                firstCoord = i;
                                secondCoord = j - k;
                                break;
                            case 3:
                                firstCoord = i + k;
                                secondCoord = j;
                                break;
                            case 4:
                                firstCoord = i - k;
                                secondCoord = j;
                                break;
                            }

                            if (secondCoord < 8 && firstCoord < 8)
                            {
                                if (firstCoord == Position.first && secondCoord == Position.second)
                                {

                                    currAttk.attacker = R;
                                    currAttk.path = possiblePath;
                                    result.push_back(currAttk);
                                    break;
                                }
                                else
                                {
                                    if (this->getAt({firstCoord, secondCoord}) == nullptr)
                                    {
                                        possiblePath.insert({firstCoord, secondCoord});
                                    }
                                    else
                                    {
                                        possiblePath.clear();
                                        break;
                                    }
                                }
                            }
                            else
                            {

                                break;
                            }
                        }
                    }
                }
                else if (bishop *B = dynamic_cast<bishop *>(this->getAt({i, j})))
                {
                    for (size_t direction = 1; direction < 5; direction++)
                    {
                        possiblePath.clear();
                        {
                            for (size_t k = 1; k < 8; k++)
                            {
                                size_t firstCoord, secondCoord;
                                switch (direction)
                                {
                                case 1: // Right Diagonal Up
                                    firstCoord = B->getPosition().first + k;
                                    secondCoord = B->getPosition().second + k;
                                    break;

                                case 2: // Left Diagonal Down
                                    firstCoord = B->getPosition().first + k;
                                    secondCoord = B->getPosition().second - k;
                                    break;

                                case 3: // Right Diagonal Down
                                    firstCoord = B->getPosition().first - k;
                                    secondCoord = B->getPosition().second + k;
                                    break;

                                case 4: // left Diagonal Down
                                    firstCoord = B->getPosition().first - k;
                                    secondCoord = B->getPosition().second - k;
                                    break;

                                default:
                                    break;
                                }
                                if (secondCoord < 8 && firstCoord < 8)
                                {
                                    if (firstCoord == Position.first && secondCoord == Position.second)
                                    {

                                        currAttk.attacker = B;
                                        currAttk.path = possiblePath;
                                        result.push_back(currAttk);
                                        break;
                                    }
                                    else
                                    {
                                        if (this->getAt({firstCoord, secondCoord}) == nullptr)
                                        {
                                            possiblePath.insert({firstCoord, secondCoord});
                                        }
                                        else
                                        {
                                            possiblePath.clear();
                                            break;
                                        }
                                    }
                                }
                                else
                                    break;
                            }
                        }
                    }
                }

                else if (queen *Q = dynamic_cast<queen *>(this->getAt({i, j})))
                {
                    for (int direction = 1; direction < 5; direction++)
                    {
                        possiblePath.clear();
                        for (size_t k = 1; k < 8; k++)
                        {
                            size_t firstCoord, secondCoord;

                            switch (direction)
                            {
                            case 1:
                                firstCoord = Q->getPosition().first;
                                secondCoord = Q->getPosition().second + k;
                                break;

                            case 2:
                                firstCoord = Q->getPosition().first;
                                secondCoord = Q->getPosition().second - k;
                                break;

                            case 3:
                                firstCoord = Q->getPosition().first + k;
                                secondCoord = Q->getPosition().second;
                                break;

                            case 4:
                                firstCoord = Q->getPosition().first - k;
                                secondCoord = Q->getPosition().second;
                                break;

                            default:
                                break;
                            }
                            if (secondCoord < 8 && firstCoord < 8)
                            {
                                if (firstCoord == Position.first && secondCoord == Position.second)
                                {

                                    currAttk.attacker = Q;
                                    currAttk.path = possiblePath;
                                    result.push_back(currAttk);
                                    break;
                                }
                                else
                                {
                                    if (this->getAt({firstCoord, secondCoord}) == nullptr)
                                    {
                                        possiblePath.insert({firstCoord, secondCoord});
                                    }
                                    else
                                    {
                                        possiblePath.clear();
                                        break;
                                    }
                                }
                            }
                            else
                                break;
                        }
                    }
                    for (size_t direction = 1; direction < 5; direction++)
                    {
                        possiblePath.clear();
                        {
                            for (size_t k = 1; k < 8; k++)
                            {
                                size_t firstCoord, secondCoord;
                                switch (direction)
                                {
                                case 1: // Right Diagonal Up
                                    firstCoord = Q->getPosition().first + k;
                                    secondCoord = Q->getPosition().second + k;
                                    break;

                                case 2: // Left Diagonal Down
                                    firstCoord = Q->getPosition().first + k;
                                    secondCoord = Q->getPosition().second - k;
                                    break;

                                case 3: // Right Diagonal Down
                                    firstCoord = Q->getPosition().first - k;
                                    secondCoord = Q->getPosition().second + k;
                                    break;

                                case 4: // left Diagonal Down
                                    firstCoord = Q->getPosition().first - k;
                                    secondCoord = Q->getPosition().second - k;
                                    break;

                                default:
                                    break;
                                }
                                if (secondCoord < 8 && firstCoord < 8)
                                {
                                    if (firstCoord == Position.first && secondCoord == Position.second)
                                    {

                                        currAttk.attacker = Q;
                                        currAttk.path = possiblePath;
                                        result.push_back(currAttk);
                                        break;
                                    }
                                    else
                                    {
                                        if (this->getAt({firstCoord, secondCoord}) == nullptr)
                                        {
                                            possiblePath.insert({firstCoord, secondCoord});
                                        }
                                        else
                                        {
                                            possiblePath.clear();
                                            break;
                                        }
                                    }
                                }
                                else
                                    break;
                            }
                        }
                    }
                }
                else if (king *K = dynamic_cast<king *>(this->getAt({i, j})))
                {
                    pair<int, int> directions[8] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
                    for (pair<int, int> direction : directions)
                    {
                        int firstCoord = (int)K->getPosition().first + direction.first;
                        int secondCoord = (int)K->getPosition().second + direction.second;
                        if ((firstCoord < 8 && firstCoord >= 0 && secondCoord < 8 && secondCoord >= 0) && (firstCoord == Position.first && secondCoord == Position.second))
                        {
                            currAttk.attacker = K;
                            currAttk.path = possiblePath;
                            result.push_back(currAttk);
                        }
                    }
                }
            }
        }
    }
    return result;
}

char getPromotionPiece ()
{
    char piece;
    cout<<"Choose What piece to promote to (N,Q,B,R): ";
    cin>>piece;
    return tolower(piece);
}


bool board ::isPinned(piece *piece, pos newPosition)
{
    board tempBoard = *this;
    size_t firstCoord = newPosition.first, secondCoord = newPosition.second;
    
    set<pos> possibleCaptures = piece->getPossibleCaptures();
    bool isCapture = (tempBoard.getAt(newPosition) != nullptr);
    bool isEnPassantCapture = (dynamic_cast<pawn *>(piece) && !isCapture && binary_search(possibleCaptures.begin(), possibleCaptures.end(), newPosition));
    tempBoard.setAt({firstCoord, secondCoord}, piece);
    tempBoard.setAt(piece->getPosition(), nullptr);
    
    if (isEnPassantCapture)
    {
        int capturedPawnRow = piece->isWhite() ? newPosition.first - 1 : newPosition.first + 1;
        pos capturedPawnPos = {(size_t)capturedPawnRow, newPosition.second};
        tempBoard.setAt(capturedPawnPos, nullptr);
    }

    if (tempBoard.AttackedBy(tempBoard.getKingPosition(piece->isWhite()), piece->isWhite()).empty())
        return false;
    else
        return true;
}

bool board:: isCheckmate(bool isWhiteTurn)
{
    for (size_t i = 0; i < 8; i++)
    {
        for(size_t j=0;j<8;j++){
            if(!this->getAt({i,j})->getPossibleMoves().empty()) return false;
        }
    }
    if((isWhiteTurn && !this->AttackedBy(whiteKingPosition,isWhiteTurn).empty()) || (!isWhiteTurn && !this->AttackedBy(blackKingPosition,isWhiteTurn).empty()))
    {
        return true;
    }
    return false;
}

bool board:: isStalemate(bool isWhiteTurn)
{
    for (size_t i = 0; i < 8; i++)
    {
        for(size_t j=0;j<8;j++){
            if(!this->getAt({i,j})->getPossibleMoves().empty()) return false;
        }
    }
    if((isWhiteTurn && this->AttackedBy(whiteKingPosition,isWhiteTurn).empty()) || (!isWhiteTurn && this->AttackedBy(blackKingPosition,isWhiteTurn).empty()))
    {
        return true;
    }
    return false;
}

void board ::printBoardB()
{
    for (size_t i = 0; i < 8; i++)
    {
        cout << i + 1 << ' ';
        for (int j = 7; j >= 0; j--)
        {
            if (Board[i][j] == nullptr)
                (i + j) % 2 == 0 ? cout << "■" << ' ' : cout << "□" << ' ';
            else
                cout << Board[i][j]->getValue() << ' ';
        }
        cout << '\n';
    }
    cout << "  ";
    for (size_t i = 0; i < 8; i++)
        cout << static_cast<char>('h' - i) << ' ';
    cout << '\n';
}

void board ::printBoardW()
{
    for (int i = 7; i >= 0; i--)
    {
        cout << i + 1 << ' ';
        for (size_t j = 0; j < 8; j++)
        {
            if (Board[i][j] == nullptr)
                (i + j) % 2 == 0 ? cout << "■" << ' ' : cout << "□" << ' ';
            else
                cout << Board[i][j]->getValue() << ' ';
        }
        cout << '\n';
    }
    cout << "  ";
    for (size_t i = 0; i < 8; i++)
        cout << static_cast<char>('a' + i) << ' ';
    cout << '\n';
}

void player ::addMove(pair<pair<piece *, string>, bool> move)
{
    moves.push(move);
}

void player::addCapture(pair<piece *, string> capture)
{
    captured.push(capture);
}
player::player(bool isWhite)
{
    this->White = isWhite;
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

void Normalgame ::run()
{
    board board;
    player White = player(true);
    player Black = player(false);
    bool whiteTurn = true;

    regex e("^[a-hA-H][1-8]$");
    while (true)
    {
        clearScreen();
        if (board.isCheckmate(whiteTurn))
        {
            cout<<"Black Wins By Checkmate";
            return;
        }
        else if(board.isStalemate(whiteTurn))
        {
            cout<<"Draw By Stalemate";
        }
        
        whiteTurn ? board.printBoardW() : board.printBoardB();
        string input;
        cout << "Select a piece (e.g., e2 e4) or type exit: ";
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "exit")
        {
            cout << "Exiting the game." << endl;
            return;
        }

        else if (regex_match(input, e))
        {
            pos position = stringTOmove(input);
            piece *selected = board.getAt(position);
            if (selected == nullptr || whiteTurn != selected->isWhite())
            {
                cout << "Illegal move" << endl;
                this_thread::sleep_for(std::chrono::seconds(2));
                continue;
            }

            clearScreen();
            whiteTurn ? board.printBoardW() : board.printBoardB();
            selected->checkMoves(board, position);
            set<pos> moves = selected->getPossibleMoves();
            set<pos> captures = selected->getPossibleCaptures();
            if (moves.empty())
            {
                cout << "No possible moves" << endl;
                this_thread::sleep_for(std::chrono::seconds(2));
                continue;
            }
            cout << "Possible moves (Red is capturable): ";
            for (pos move : moves)
            {
                string moveString = moveTOstring(move);
                if (binary_search(captures.begin(), captures.end(), move))
                {
                    moveString = "\x1b[31m" + moveString + "\x1b[0m";
                }
                cout << moveString << "  ";
            }
            cout << endl;
            cout << "Play a move or type \"back\" to select another piece : ";
            cin >> input;
            transform(input.begin(), input.end(), input.begin(), ::tolower);
            if (input == "back")
                continue;
            else
            {
                if (regex_match(input, e) && selected->Move(whiteTurn ? &White : &Black, board, stringTOmove(input)))
                {
                    whiteTurn = !whiteTurn;
                    continue;
                }
                else
                {
                    cout << "Illegal move" << endl;
                    this_thread::sleep_for(std::chrono::seconds(2));
                    continue;
                }
            }
        }
        else
        {
            cout << "Invalid position" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            continue;
        }
    }
}
