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
    size_t col, first;
    char file = move[0], rank = move[1];
    col = static_cast<size_t>(file - 'a');
    first = static_cast<size_t>(rank - '0') - 1;
    return {first, col};
}

piece *board::createPieceFromChar(char pieceChar, pos position)
{
    bool isWhite = (isupper(pieceChar) != 0);

    switch (tolower(pieceChar))
    {
    case 'r':
        isWhite ? whiteRooks++ : blackRooks++;
        return new rook(isWhite, position);
    case 'n':
        isWhite ? whiteKnights++ : blackKnights++;
        return new Knight(isWhite, position);
    case 'b':
        isWhite ? whiteBishops++ : blackBishops++;
        return new bishop(isWhite, position);
    case 'q':
        isWhite ? whiteQueens++ : blackQueens++;
        return new queen(isWhite, position);
    case 'k':
        isWhite ? whiteKingPosition = position : blackKingPosition = position;
        return new king(isWhite, position);
    case 'p':
        isWhite ? whitePawns++ : blackPawns++;
        return new pawn(isWhite, position);
    default:
        return nullptr;
    }
}

bool board::isWhiteTurn()
{
    return whiteTurn;
}
void board::switchTurns()
{
    whiteTurn = !whiteTurn;
}
void board::setWhitecaptured()
{
    didWhiteCapture = true;
}

void board::resetWhitecaptured()
{
    didWhiteCapture = false;
}

bool board::DidWhitecapture()
{
    return didWhiteCapture;
}

void board::initZobrist()
{
    mt19937_64 randomEngine(12345);
    uniform_int_distribution<uint64_t> distribution;

    for (int p = 0; p < 6; ++p)
    {
        for (int c = 0; c < 2; ++c)
        {
            for (int s = 0; s < 64; ++s)
            {
                zobristTable[p][c][s] = distribution(randomEngine);
            }
        }
    }

    WhiteTurnkey = distribution(randomEngine);
    for (int i = 0; i < 4; ++i)
        castlingKeys[i] = distribution(randomEngine);
    for (int i = 0; i < 8; ++i)
        enPassantFileKeys[i] = distribution(randomEngine);
}

uint64_t board ::calculateintitialZobristHash()
{
    uint64_t hash = 0;
    hash ^= WhiteTurnkey;
    enum PieceType
    {
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING
    };
    static const map<char, int> pieceType = {
        {'p', PAWN}, {'n', KNIGHT}, {'b', BISHOP}, {'r', ROOK}, {'q', QUEEN}, {'k', KING}};
    // XOR keys for each piece
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            piece *piece = this->getAt({i, j});
            if (piece != nullptr)
            {
                char type = piece->getType();
                int color = piece->isWhite() ? 1 : 0;
                uint64_t pieceHash = zobristTable[pieceType.at(type)][color][8 * i + j];
                hash ^= pieceHash;

                if (king *k = dynamic_cast<king *>(piece))
                {
                    if (k->isWhite())
                    {
                        if (k->canKingsideCastle(*this))
                            hash ^= castlingKeys[2];
                        if (k->canQueensideCastle(*this))
                            hash ^= castlingKeys[3];
                    }
                    else
                    {
                        if (k->canKingsideCastle(*this))
                            hash ^= castlingKeys[0];
                        if (k->canQueensideCastle(*this))
                            hash ^= castlingKeys[1];
                    }
                }
            }
        }
    }

    int epFile = this->getEnPassantFile();
    if (epFile != NO_FILE)
    {
        hash ^= enPassantFileKeys[epFile];
    }
    return hash;
}

uint64_t board::getPiecehash(char piece, bool isWhite, pos position)
{
    int color = isWhite ? 1 : 0;
    enum PieceType
    {
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING
    };
    static const map<char, int> pieceType = {
        {'p', PAWN}, {'n', KNIGHT}, {'b', BISHOP}, {'r', ROOK}, {'q', QUEEN}, {'k', KING}};

    return zobristTable[pieceType.at(piece)][color][(int)position.first * 8 + (int)position.second];
}

uint64_t board::getPreviousHash()
{
    return this->PreviousHash;
}
void board::setPreviousHash(uint64_t newHash)
{
    this->PreviousHash = newHash;
}

uint64_t board::getWhiteTurnkey()
{
    return this->WhiteTurnkey;
}
uint64_t board::getcastlingKey(int side, bool isWhite)
{
    return this->castlingKeys[side + isWhite];
}
uint64_t board::getenPassantFileKey(int file)
{
    return this->enPassantFileKeys[file];
}
void board::addHash(uint64_t newHash)
{
    if (this->zobristHistory.find(newHash) != zobristHistory.end())
    {
        zobristHistory[newHash]++;
    }
    else
    {
        this->zobristHistory.insert({newHash, 1});
    }
}

void board::minusFullMove()
{
    fullmoves--;
}
void board::plusFullMove()
{
    fullmoves++;
}
void board::minusHalfMoveNoCaptures()
{
    halfmovesNoCaptures--;
}
void board::plusHalfMoveNoCaptures()
{
    halfmovesNoCaptures++;
}

void board::resetHalfMovesNoCaptures()
{
    halfmovesNoCaptures = 0;
}

board::board(bool fullBoard)
    : Board(8, vector<piece *>(8, nullptr))
{
    whiteQueens = 0, whiteRooks = 0, whiteBishops = 0, whiteKnights = 0, whitePawns = 0;
    blackQueens = 0, blackRooks = 0, blackBishops = 0, blackKnights = 0, blackPawns = 0;
    fullmoves = 0, halfmovesNoCaptures = 0;
    whiteTurn = true;
    enPassantFile = NO_FILE;
    initZobrist();
    if (fullBoard)
    {
        for (int rank = 0; rank < 8; rank++)
        {
            for (int file = 0; file < 8; file++)
            {
                char pieceChar = layout[rank][file];
                if (pieceChar != '.')
                {
                    Board[rank][file] = createPieceFromChar(pieceChar, {rank, file});
                }
            }
        }
    }
    uint64_t inititalHash = calculateintitialZobristHash();
    this->addHash(inititalHash);
    PreviousHash = inititalHash;
}

vector<string> splitFEN(string FEN)
{
    vector<string> res(6);
    // {pieces , turn , castling , enpassant , halfmoves , fullmoves}

    stringstream ss(FEN);
    string t;
    int i = 0;

    while (getline(ss, t, ' '))
    {
        res[i] = t;
        i++;
    }
    return res;
}

optional<board> board::boardFromFEN(string FEN)
{
    regex e(R"(^([rnbqkpRNBQKP1-8]+\/){7}[rnbqkpRNBQKP1-8]+\s[wb]\s(?:K?Q?k?q?|-)\s(?:[a-h][36]|-)\s\d+\s[1-9]\d*$)");
    if (!regex_match(FEN, e))
    {
        return nullopt;
    }

    board Board(false);
    Board.initZobrist();
    vector<string> splitFENstrs = splitFEN(FEN);
    bool loadedwhiteKing = false, loadedblackKing = false;
    int rank = 7, file = 0;
    for (char a : splitFENstrs[0])
    {
        if (a == '/')
        {
            if (file != 8)
                return nullopt;
            file = 0;
            rank--;
            continue;
        }

        if (file > 7 || Board.whitePawns > 8 || Board.blackPawns > 8)
            return nullopt;

        if (isdigit(a))
        {
            file += (a - '0');
            continue;
        }
        else if (file == 8)
            break;
        else
        {
            if ((a == 'k' && loadedblackKing) || (a == 'K' && loadedwhiteKing))
                return nullopt;
            else if ((a == 'k' && !loadedblackKing))
                loadedblackKing = true;
            else if ((a == 'K' && !loadedwhiteKing))
                loadedwhiteKing = true;

            if ((a == 'p' || a == 'P') && (rank == 7 || rank == 0))
                return nullopt;
            Board.setAt({rank, file}, Board.createPieceFromChar(a, {rank, file}));
            file++;
        }
    }

    if (rank != 0 || file != 8)
    {
        return nullopt; // The FEN did not describe a full 8x8 board.
    }

    if (splitFENstrs[1][0] == 'w')
    {
        if (!Board.AttackedBy(Board.blackKingPosition, false).empty())
            return nullopt;
        Board.whiteTurn = true;
    }
    else
    {
        if (!Board.AttackedBy(Board.whiteKingPosition, true).empty())
            return nullopt;
        Board.whiteTurn = false;
    }

    king *wk = dynamic_cast<king *>(Board.getAt(Board.whiteKingPosition));
    king *bk = dynamic_cast<king *>(Board.getAt(Board.blackKingPosition));

    for (char flag : splitFENstrs[2])
    {
        switch (flag)
        {
        case 'K':
        {
            piece *r = Board.getAt({0, 7});
            if (Board.getKingPosition(true) != pos{0, 4} || r == nullptr || r->getType() != 'r')
            {
                return nullopt;
            }
            wk->setKingsideCastle();
            break;
        }
        case 'Q':
        {
            piece *r = Board.getAt({0, 0});
            if (Board.getKingPosition(true) != pos{0, 4} || r == nullptr || r->getType() != 'r')
            {
                return nullopt;
            }
            wk->setQueensideCastle();
            break;
        }
        case 'k':
        {
            piece *r = Board.getAt({7, 7});
            if (Board.getKingPosition(false) != pos{7, 4} || r == nullptr || r->getType() != 'r')
            {
                return nullopt;
            }
            bk->setKingsideCastle();
            break;
        }
        case 'q':
        {
            piece *r = Board.getAt({7, 0});
            if (Board.getKingPosition(false) != pos{7, 4} || r == nullptr || r->getType() != 'r')
            {
                return nullopt;
            }
            bk->setQueensideCastle();
            break;
        }
        }
    }

    if (splitFENstrs[3] != "-")
    {
        pos newenpassantpos = stringTOmove(splitFENstrs[3]);
        if ((newenpassantpos.first == 5 && !Board.whiteTurn) || (newenpassantpos.first == 2 && Board.whiteTurn))
        {
            return nullopt;
        }
        if (Board.getAt(newenpassantpos) != nullptr ||
            (Board.whiteTurn && Board.getAt({newenpassantpos.first + 1, newenpassantpos.second}) != nullptr) ||
            (!Board.whiteTurn && Board.getAt({newenpassantpos.first - 1, newenpassantpos.second}) != nullptr))
        {
            return nullopt;
        }
        Board.enPassantFile = newenpassantpos.second;

        if (Board.whiteTurn)
        {
            pawn *p = dynamic_cast<pawn *>(Board.getAt({newenpassantpos.first - 1, newenpassantpos.second}));
            if (p != nullptr)
            {
                p->setenpassant();
                Board.setEnpassant();
            }
            else
                return nullopt;
        }

        if (!Board.whiteTurn)
        {
            pawn *p = dynamic_cast<pawn *>(Board.getAt({newenpassantpos.first + 1, newenpassantpos.second}));
            if (p != nullptr)
            {
                p->setenpassant();
                Board.setEnpassant();
            }
            else
                return nullopt;
        }
    }
    else
        Board.enPassantFile = NO_FILE;

    Board.halfmovesNoCaptures = stoi(splitFENstrs[4]);
    Board.fullmoves = stoi(splitFENstrs[5]);

    uint64_t inititalHash = Board.calculateintitialZobristHash();
    Board.addHash(inititalHash);
    Board.setPreviousHash(inititalHash);
    return Board;
}

void board::minusPiece(char pieceType, bool isWhite)
{
    if (isWhite)
    {
        switch (pieceType)
        {
        case 'q':
            whiteQueens--;
            break;
        case 'r':
            whiteRooks--;
            break;
        case 'b':
            whiteBishops--;
            break;
        case 'n':
            whiteKnights--;
            break;
        case 'p':
            whitePawns--;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (pieceType)
        {
        case 'q':
            blackQueens--;
            break;
        case 'r':
            blackRooks--;
            break;
        case 'b':
            blackBishops--;
            break;
        case 'n':
            blackKnights--;
            break;
        case 'p':
            blackPawns--;
            break;
        default:
            break;
        }
    }
}

void board::plusPiece(char pieceType, bool isWhite)
{
    if (isWhite)
    {
        switch (pieceType)
        {
        case 'q':
            whiteQueens++;
            break;
        case 'r':
            whiteRooks++;
            break;
        case 'b':
            whiteBishops++;
            break;
        case 'n':
            whiteKnights++;
            break;
        case 'p':
            whitePawns++;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (pieceType)
        {
        case 'q':
            blackQueens++;
            break;
        case 'r':
            blackRooks++;
            break;
        case 'b':
            blackBishops++;
            break;
        case 'n':
            blackKnights++;
            break;
        case 'p':
            blackPawns++;
            break;
        default:
            break;
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

int board::getEnPassantFile()
{
    return this->enPassantFile;
}

void board::setEnPassantFile(int file)
{
    enPassantFile = file;
}

void board::resetEnPassantFile()
{
    enPassantFile = NO_FILE;
}

int board::repeted(uint64_t key)
{
    return zobristHistory[key];
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

char getPromotionPiece()
{
    char piece;
    cout << "Choose What piece to promote to (N,Q,B,R): ";
    cin >> piece;
    return tolower(piece);
}

bool board::isPinned(piece *p, pos newPosition)
{
    pos oldPosition = p->getPosition();
    piece *capturedPiece = this->getAt(newPosition);

    bool isEnPassantCapture = (dynamic_cast<pawn *>(p) && capturedPiece == nullptr && p->getPossibleCaptures().count(newPosition));
    pos enPassantPawnPos;
    piece *enPassantPawn = nullptr;
    if (isEnPassantCapture)
    {
        int capturedPawnRow = p->isWhite() ? newPosition.first - 1 : newPosition.first + 1;
        enPassantPawnPos = {(size_t)capturedPawnRow, newPosition.second};
        enPassantPawn = this->getAt(enPassantPawnPos);
    }

    this->setAt(newPosition, p);
    this->setAt(oldPosition, nullptr);
    if (isEnPassantCapture)
    {
        this->setAt(enPassantPawnPos, nullptr);
    }
    p->updatePos(newPosition);

    bool isKingAttacked = !this->AttackedBy(this->getKingPosition(p->isWhite()), p->isWhite()).empty();

    this->setAt(oldPosition, p);
    this->setAt(newPosition, capturedPiece);
    if (isEnPassantCapture)
    {
        this->setAt(enPassantPawnPos, enPassantPawn);
    }
    p->updatePos(oldPosition);

    return isKingAttacked;
}

bool board::isCheckmate(bool isWhiteTurn)
{
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if ((this->getAt({i, j}) == nullptr))
                continue;
            if (this->getAt({i, j})->isWhite() != isWhiteTurn)
                continue;

            this->getAt({i, j})->checkMoves(*this, {i, j});
            if (!(this->getAt({i, j})->getPossibleMoves().empty()))
                return false;
        }
    }

    if ((isWhiteTurn && !this->AttackedBy(whiteKingPosition, isWhiteTurn).empty()) || (!isWhiteTurn && !this->AttackedBy(blackKingPosition, isWhiteTurn).empty()))
    {
        return true;
    }
    return false;
}

bool board::isStalemate(bool isWhiteTurn)
{
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if ((this->getAt({i, j}) == nullptr))
                continue;
            if (this->getAt({i, j})->isWhite() != isWhiteTurn)
                continue;

            this->getAt({i, j})->checkMoves(*this, {i, j});
            if (!(this->getAt({i, j})->getPossibleMoves().empty()))
                return false;
        }
    }
    if ((isWhiteTurn && this->AttackedBy(whiteKingPosition, isWhiteTurn).empty()) || (!isWhiteTurn && this->AttackedBy(blackKingPosition, isWhiteTurn).empty()))
    {
        return true;
    }
    return false;
}

bool board::isTrifoldDraw()
{
    for (auto &hash : this->zobristHistory)
    {
        if (hash.second >= 3)
        {
            return true;
        }
    }
    return false;
}

bool board::isInsufficientMaterial()
{

    // If any player has a Queen, Rook, or Pawn, it's not a draw.
    if (whiteQueens > 0 || whiteRooks > 0 || whitePawns > 0)
        return false;
    if (blackQueens > 0 || blackRooks > 0 || blackPawns > 0)
        return false;

    int totalBishops = whiteBishops + blackBishops;
    int totalKnights = whiteKnights + blackKnights;

    // King vs King, King + Bishop vs King, or King + Knight vs King
    if (totalBishops <= 1 && totalKnights <= 1)
    {
        return true;
    }

    // King + Two Knights vs King
    if (whiteKnights == 2 && blackBishops == 0 && blackKnights == 0)
        return true;
    if (blackKnights == 2 && whiteBishops == 0 && whiteKnights == 0)
        return true;

    // King + Bishop vs King + Bishop on same-colored squares
    if (blackBishops == 1 && whiteBishops == 1 && whiteKnights == 0 && blackKnights == 0)
    {
        bool WhiteBishopOnWhiteSquare = false, BlackBishopOnWhiteSquare = false;
        int bishopsFound = 0;
        for (size_t i = 0; i < 8; i++)
        {
            if (bishopsFound == 2)
                break;
            for (size_t j = 0; j < 8; j++)
            {
                if (bishopsFound == 2)
                    break;
                piece *target = this->getAt({i, j});
                if (target == nullptr)
                    continue;
                else if (bishop *b = dynamic_cast<bishop *>(target))
                {
                    bishopsFound++;
                    bool isWhite = b->isWhite();
                    if (isWhite && ((i + j) % 2 != 0))
                        WhiteBishopOnWhiteSquare = true;
                    if (!isWhite && ((i + j) % 2 != 0))
                        BlackBishopOnWhiteSquare = true;
                }
            }
        }
        if (WhiteBishopOnWhiteSquare == BlackBishopOnWhiteSquare)
            return true;
    }

    return false;
}

bool board::is50MoveDraw()
{
    return (halfmovesNoCaptures >= 50);
}
bool board::is75MoveDraw()
{
    return (halfmovesNoCaptures == 75);
}

void board ::printBoardB()
{
    for (size_t i = 0; i < 8; i++)
    {
        cout << i + 1 << ' ';
        for (int j = 7; j >= 0; j--)
        {
            if (Board[i][j] == nullptr)
                (i + j) % 2 == 0 ? cout << "□" << ' ' : cout << "■" << ' ';
            else
                cout << Board[i][j]->getprintableValue() << ' ';
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
                (i + j) % 2 == 0 ? cout << "□" << ' ' : cout << "■" << ' ';
            else
                cout << Board[i][j]->getprintableValue() << ' ';
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

void Normalgame ::run(board &board)
{
    player White = player(true);
    player Black = player(false);

    regex e("^[a-hA-H][1-8]$");
    while (true)
    {
        bool whiteTurn = board.isWhiteTurn();
        clearScreen();

        // //debug zobrist History
        //     std::ofstream outputFile("output.txt", std::ios::app);
        //     if (!outputFile.is_open()) {
        //         std::cerr << "Error opening file!" << std::endl;
        //         return;
        //     }
        //     std::streambuf* originalCoutBuffer = std::cout.rdbuf();
        //     std::cout.rdbuf(outputFile.rdbuf());
        //     cout << "Last Hash = " << board.getPreviousHash() << "  Repeated = "<< board.repeted(board.getPreviousHash())<< endl;
        //     std::cout.rdbuf(originalCoutBuffer);
        //     outputFile.close();
        // //endofdebug

        if (board.isCheckmate(whiteTurn))
        {
            cout << "Black Wins By Checkmate." << endl;
            return;
        }
        else if (board.isCheckmate(!whiteTurn))
        {
            cout << "White Wins By Checkmate." << endl;
            return;
        }
        else if (board.isStalemate(whiteTurn))
        {
            cout << "Draw By Stalemate." << endl;
            return;
        }
        else if (board.is75MoveDraw())
        {
            cout << "Draw By 75 move rule." << endl;
            return;
        }
        else if (board.is50MoveDraw())
        {
            cout << "Do you want to claim draw By 50 move rule? (y/n) : " << endl;
            char choice;
            cin >> choice;
            if (tolower(choice) == 'y')
            {
                cout << "Draw By 50 move rule." << endl;
                return;
            }
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
                    if (board.isTrifoldDraw())
                    {
                        cout << "Draw By Repetition" << endl;
                        return;
                    }
                    board.switchTurns();
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
