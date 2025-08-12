#include "piece.h"
#include "board.h"

Knight::Knight(bool isWhite, pair<size_t, size_t> startingPosition)
    : piece(isWhite, startingPosition)
{
    setValue(isWhite ? "♞" : "♘");
}

void Knight ::checkMoves(board &Board, pair<size_t, size_t> currPosition)
{
    clearMoves();
    for (int direction = 1; direction < 5; direction++){
        switch (direction)
        {
        case 1:
            if ((currPosition.first + 1 < 8 && currPosition.second + 2 < 8))
            {
                if (Board.getAt({currPosition.first + 1, currPosition.second + 2}) == nullptr)
                {
                    addPossibleMove({currPosition.first + 1, currPosition.second + 2});
                }
                else
                {
                    if (Board.getAt({currPosition.first + 1, currPosition.second + 2})->isWhite() != this->isWhite())
                    {
                        // capturable
                        addPossibleMove({currPosition.first + 1, currPosition.second + 2});
                        addPossibleCapture({currPosition.first + 1, currPosition.second + 2});
                    }
                }
            }

            if ((currPosition.first - 1 < 8 && currPosition.second + 2 < 8))
            {
                if (Board.getAt({currPosition.first - 1, currPosition.second + 2}) == nullptr)
                {
                    addPossibleMove({currPosition.first - 1, currPosition.second + 2});
                }
                else
                {
                    if (Board.getAt({currPosition.first - 1, currPosition.second + 2})->isWhite() != this->isWhite())
                    {
                        // capturable
                        addPossibleMove({currPosition.first - 1, currPosition.second + 2});
                        addPossibleCapture({currPosition.first - 1, currPosition.second + 2});
                    }
                }
            }
            break;

        case 2:
            if ((currPosition.first + 1 < 8 && currPosition.second - 2 < 8))
            {
                if ((Board.getAt({currPosition.first + 1, currPosition.second - 2}) == nullptr))
                {
                    addPossibleMove({currPosition.first + 1, currPosition.second - 2});
                }
                else
                {
                    if (Board.getAt({currPosition.first + 1, currPosition.second - 2})->isWhite() != this->isWhite())
                    {
                        // capturable
                        addPossibleMove({currPosition.first + 1, currPosition.second - 2});
                        addPossibleCapture({currPosition.first + 1, currPosition.second - 2});
                    }
                }
            }

            if ((currPosition.first - 1 < 8 && currPosition.second - 2 < 8))
            {
                if ((Board.getAt({currPosition.first - 1, currPosition.second - 2}) == nullptr))
                {
                    addPossibleMove({currPosition.first - 1, currPosition.second - 2});
                }
                else
                {
                    if (Board.getAt({currPosition.first - 1, currPosition.second - 2})->isWhite() != this->isWhite())
                    {
                        // capturable
                        addPossibleMove({currPosition.first - 1, currPosition.second - 2});
                        addPossibleCapture({currPosition.first - 1, currPosition.second - 2});
                    }
                }
            }
            break;

        case 3:
            if (currPosition.first + 2 < 8 && currPosition.second + 1 < 8)
            {
                if ((Board.getAt({currPosition.first + 2, currPosition.second + 1}) == nullptr))
                {
                    addPossibleMove({currPosition.first + 2, currPosition.second + 1});
                }
                else
                {
                    if (Board.getAt({currPosition.first + 2, currPosition.second + 1})->isWhite() != this->isWhite())
                    {
                        // capturable
                        addPossibleMove({currPosition.first + 2, currPosition.second + 1});
                        addPossibleCapture({currPosition.first + 2, currPosition.second + 1});
                    }
                }
            }

            if (currPosition.first + 2 < 8 && currPosition.second - 1 < 8)
            {
                if ((Board.getAt({currPosition.first + 2, currPosition.second - 1}) == nullptr))
                {
                    addPossibleMove({currPosition.first + 2, currPosition.second - 1});
                }
                else
                {
                    if (Board.getAt({currPosition.first + 2, currPosition.second - 1})->isWhite() != this->isWhite())
                    {
                        // capturable
                        addPossibleMove({currPosition.first + 2, currPosition.second - 1});
                        addPossibleCapture({currPosition.first + 2, currPosition.second - 1});
                    }
                }
            }
            break;

        case 4:
            if (currPosition.first - 2 < 8 && currPosition.second + 1 < 8)
            {
                if ((Board.getAt({currPosition.first - 2, currPosition.second + 1}) == nullptr))
                {
                    addPossibleMove({currPosition.first - 2, currPosition.second + 1});
                }
                else
                {
                    if (Board.getAt({currPosition.first - 2, currPosition.second + 1})->isWhite() != this->isWhite())
                    {
                        // capturable
                        addPossibleMove({currPosition.first - 2, currPosition.second + 1});
                        addPossibleCapture({currPosition.first - 2, currPosition.second + 1});
                    }
                }
            }

            if (currPosition.first - 2 < 8 && currPosition.second - 1 < 8)
            {
                if ((Board.getAt({currPosition.first - 2, currPosition.second - 1}) == nullptr))
                {
                    addPossibleMove({currPosition.first - 2, currPosition.second - 1});
                }
                else
                {
                    if (Board.getAt({currPosition.first - 2, currPosition.second - 1})->isWhite() != this->isWhite())
                    {
                        // capturable
                        addPossibleMove({currPosition.first - 2, currPosition.second - 1});
                        addPossibleCapture({currPosition.first - 2, currPosition.second - 1});
                    }
                }
            }
            break;

        default:
            break;
        }
}
}