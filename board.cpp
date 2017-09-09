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

bool Board::canMovePiece(int from, int to, int *captured) {
    int r1 = fromIdToRow(from), c1 = fromIdToColumn(from);
    int r2 = fromIdToRow(to), c2 = fromIdToColumn(to);
    int rd = sign(r2 - r1), cd = sign(c2 - c1);
    int cnt = abs(rd), vcnt = abs(cd);
    int side1 = fromCharToSide(this->_board[r1][c1]);
    int side2 = fromCharToSide(this->_board[r2][c2]);
    if (side2 || !side1) return false;
    if (cnt != vcnt) return false;

    bool isKing = !(this->_board[r1][c1] & 32);

    if (isKing) {
        bool anyCaptured = false;
        int currCaptured;

        for (int i = 1; i < cnt; ++i) {
            int rx = r1 + rd * i, cx = c1 + cd * i;
            int sidex = fromCharToSide(this->_board[rx][cx]);

            if (sidex) {
                if (sidex == side1) return false;

                if ((sidex ^ side1) == 3) {
                    if (anyCaptured) return false;

                    anyCaptured = true;
                    currCaptured = fromCoordinatesToId(rx, cx);
                }
            }
        }

        if (anyCaptured && captured != nullptr) *captured = currCaptured;
        return true;
    } else {
        if (cnt == 1) {
            if ((side1 == 1 && from < to) || (side1 == 2 && from < to)) return true;
            else return false;
        } else if (cnt == 2) {
            int rx = r1 + rd, cx = c1 + cd;
            int sidex = fromCharToSide(this->_board[rx][cx]);

            if ((sidex ^ side1) == 3) {
                if (captured != nullptr) *captured = fromCoordinatesToId(rx, cx);
                return true;
            }

            return false;
        } else {
            return false;
        }
    }
}

bool Board::canMovePieceIfSide(int from, int to, int side, bool isKing, int *captured) {
    int r1 = fromIdToRow(from), c1 = fromIdToColumn(from);
    int r2 = fromIdToRow(to), c2 = fromIdToColumn(to);
    int rd = sign(r2 - r1), cd = sign(c2 - c1);
    int cnt = abs(rd), vcnt = abs(cd);
    int &side1 = side;
    int side2 = fromCharToSide(this->_board[r2][c2]);
    if (side2 || !side1) return false;
    if (cnt != vcnt) return false;

    if (isKing) {
        bool anyCaptured = false;
        int currCaptured;

        for (int i = 1; i < cnt; ++i) {
            int rx = r1 + rd * i, cx = c1 + cd * i;
            int sidex = fromCharToSide(this->_board[rx][cx]);

            if (sidex) {
                if (sidex == side1) return false;

                if ((sidex ^ side1) == 3) {
                    if (anyCaptured) return false;

                    anyCaptured = true;
                    currCaptured = fromCoordinatesToId(rx, cx);
                }
            }
        }

        if (anyCaptured && captured != nullptr) *captured = currCaptured;
        return true;
    } else {
        if (cnt == 1) {
            if ((side1 == 1 && from < to) || (side1 == 2 && from < to)) return true;
            else return false;
        } else if (cnt == 2) {
            int rx = r1 + rd, cx = c1 + cd;
            int sidex = fromCharToSide(this->_board[rx][cx]);

            if ((sidex ^ side1) == 3) {
                if (captured != nullptr) *captured = fromCoordinatesToId(rx, cx);
                return true;
            }

            return false;
        } else {
            return false;
        }
    }
}

bool Board::movePiece(int from, int to, int *captured) {
    if (!canMovePiece(from, to)) return false;

    int r1 = fromIdToRow(from), c1 = fromIdToColumn(from);
    int r2 = fromIdToRow(to), c2 = fromIdToColumn(to);
    int rd = sign(r2 - r1), cd = sign(c2 - c1);
    int cnt = abs(rd);
    int side = fromCharToSide(this->_board[r1][c1]);

    for (int i = 1; i < cnt; ++i) {
        int rx = r1 + rd * i, cx = c1 + cd * i;
        int sidex = fromCharToSide(this->_board[rx][cx]);

        this->_board[rx][cx] = ' ';
        if ((sidex ^ side) == 3 && captured != nullptr) *captured = fromCoordinatesToId(rx, cx);
    }

    return true;
}

QVector<QString> Board::possibleMoves(int side) {
    return QVector<QString>();
}
