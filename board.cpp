#include "board.h"

Board::Board() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            this->_board[i][j] = ' ';
}

Board::Board(QString status) {
    for (int i = 0; i < 50; ++i) {
        this->_board[fromIdToRow(i)][fromIdToColumn(i)] = status[i].toLatin1();
        this->_board[fromIdToRow(i)][fromIdToColumn(i) ^ 1] = ' ';
    }
}

int d[4][2] = { { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } }; // first 2 : black -> white, last 2  : white -> black
void Board::dfsCap(PossibleMoveTreeNode *currNode, int currPos, int side, bool captured[50], bool isKing) {
    currNode->end = true;

    int r = fromIdToRow(currPos), c = fromIdToColumn(currPos);

    for (int i = 0; i < 4; ++i) {
        int dr = d[i][0], dc = d[i][1];

        if (isKing) {
            int rm = r, cm = c;
            for (;;) {
                rm += dr; cm += dc;
                if (!inBoard(rm, cm)) break;
                if (captured[fromCoordinatesToId(rm, cm)]) break;

                int sideh = fromCharToSide(_board[rm][cm]);
                if (sideh == side) break;

                if ((sideh ^ side) == 3) {
                    int rd = rm, cd = cm;

                    for (;;) {
                        rd += dr; cd += dc;
                        if (!inBoard(rd, cd)) break;
                        if (captured[fromCoordinatesToId(rd, cd)]) break;

                        int sided = fromCharToSide(_board[rd][cd]);
                        if (sided) break;

                        int nxPos = fromCoordinatesToId(rd, cd);
                        currNode->end = false;
                        currNode->sub[nxPos] = new PossibleMoveTreeNode();

                        captured[fromCoordinatesToId(rm, cm)] = true;
                        dfsCap(currNode->sub[nxPos], nxPos, side, captured, isKing);
                        captured[fromCoordinatesToId(rm, cm)] = false;
                    }

                    break;
                }
            }
        } else {
            int rm = r + dr, cm = c + dc;
            int rd = rm + dr, cd = cm + dc;

            if (!inBoard(rm, cm) || !inBoard(rd, cd)) continue;
            if (captured[fromCoordinatesToId(rm, cm)]) continue;

            int sidem = fromCharToSide(_board[rm][cm]);
            int sided = fromCharToSide(_board[rd][cd]);

            if (sided) continue;
            if ((sidem ^ side) != 3) continue;

            int nxPos = fromCoordinatesToId(rd, cd);
            currNode->end = false;
            currNode->sub[nxPos] = new PossibleMoveTreeNode();

            captured[fromCoordinatesToId(rm, cm)] = true;
            dfsCap(currNode->sub[nxPos], nxPos, side, captured, isKing);
            captured[fromCoordinatesToId(rm, cm)] = false;
        }
    }

    if (currNode->end) { currNode->captured = 0; return; }
    int maxCap = 0;
    for (int i = 0; i < 50; ++i) {
        if (currNode->sub[i] != nullptr) {
            if (currNode->sub[i]->captured > maxCap) maxCap = currNode->sub[i]->captured;
        }
    }

    for (int i = 0; i < 50; ++i) {
        if (currNode->sub[i] != nullptr) {
            if (currNode->sub[i]->captured < maxCap) {
                delete currNode->sub[i];
                currNode->sub[i] = nullptr;
            }
        }
    }

    currNode->captured = maxCap + 1;
}

void Board::findStep(PossibleMoveTreeNode *currNode, int currPos, int side, bool isKing) {
    currNode->end = true;
    currNode->captured = 0;

    int r = fromIdToRow(currPos), c = fromIdToColumn(currPos);

    for (int i = 0; i < 4; ++i) {
        int dr = d[i][0], dc = d[i][1];

        if (isKing) {
            int rd = r, cd = c;
            for (;;) {
                rd += dr; cd += dc;
                if (!inBoard(rd, cd)) break;

                int sideh = fromCharToSide(_board[rd][cd]);
                if (sideh) break;

                int nxPos = fromCoordinatesToId(rd, cd);

                currNode->end = false;
                currNode->sub[nxPos] = new PossibleMoveTreeNode();
                currNode->sub[nxPos]->captured = 0;
                currNode->sub[nxPos]->end = true;
            }
        } else {
            int rd = r + dr, cd = c + dc;

            if (side == 1 && i > 1) continue;
            if (side == 2 && i < 2) continue;
            if (!inBoard(rd, cd)) continue;

            int sided = fromCharToSide(_board[rd][cd]);
            if (sided) continue;

            int nxPos = fromCoordinatesToId(rd, cd);
            currNode->end = false;
            currNode->sub[nxPos] = new PossibleMoveTreeNode();
            currNode->sub[nxPos]->captured = 0;
            currNode->sub[nxPos]->end = true;
        }
    }
}

PossibleMoveTreeNode* Board::possibleMoves(int side) {
    auto rv = new PossibleMoveTreeNode();
    rv->end = true;

    bool captured[50];
    for (int i = 0; i < 50; ++i) captured[i] = false;

    for (int i = 0; i < 50; ++i) {
        int r = fromIdToRow(i), c = fromIdToColumn(i);

        if (fromCharToSide(_board[r][c]) != side) continue;

        rv->sub[i] = new PossibleMoveTreeNode();

        char cache = _board[r][c];
        _board[r][c] = ' ';
        dfsCap(rv->sub[i], i, side, captured, !(cache & 32));
        _board[r][c] = cache;

        if (!rv->sub[i]->end) rv->end = false;
        else {
            delete rv->sub[i];
            rv->sub[i] = nullptr;
        }
    }

    if (!rv->end) {
        int maxCap = 0;
        for (int i = 0; i < 50; ++i) {
            if (rv->sub[i] != nullptr) {
                if (rv->sub[i]->captured > maxCap) maxCap = rv->sub[i]->captured;
            }
        }

        for (int i = 0; i < 50; ++i) {
            if (rv->sub[i] != nullptr) {
                if (rv->sub[i]->captured < maxCap) {
                    delete rv->sub[i];
                    rv->sub[i] = nullptr;
                }
            }
        }

        rv->captured = maxCap + 1;
    } else {
        for (int i = 0; i < 50; ++i) {
            int r = fromIdToRow(i), c = fromIdToColumn(i);

            if (fromCharToSide(_board[r][c]) != side) continue;

            rv->sub[i] = new PossibleMoveTreeNode();

            char cache = _board[r][c];
            _board[r][c] = ' ';
            findStep(rv->sub[i], i, side, !(cache & 32));
            _board[r][c] = cache;

            if (!rv->sub[i]->end) rv->end = false;
            else {
                delete rv->sub[i];
                rv->sub[i] = nullptr;
            }
        }
    }

    return rv;
}

char Board::cell(int r, int c) const {
    return _board[r][c];
}

void Board::setCell(int r, int c, char v) {
    _board[r][c] = v;
}
