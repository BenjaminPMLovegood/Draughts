#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "commonheader.h"

// 0 : none, 1 : black, 2 : white
inline int fromCharToSide(char chr) { return (chr | 32) == 'w' ? 2 : ((chr | 32) == 'b' ? 1 : 0); }
inline int fromCoordinatesToId(int row, int column) { return row * 5 + (column / 2); }
inline int fromIdToRow(int id) { return id / 5; }
inline int fromIdToColumn(int id) { return ((id % 5) << 1) + 1 - ((id / 5) & 1); }
inline int sign(int v) { return v > 0 ? (int)(bool)v : -1; }
//inline int abs(int v) { return v > 0 ? v : -v; }

class Board {
    char _board[BOARD_WIDTH][BOARD_WIDTH];  // ' ' or 'w' or 'b' or 'W' or 'B'


public:
    Board();
    Board(QString status);

    bool canMovePiece(int from, int to, int *captured = nullptr);
    bool canMovePieceIfSide(int from, int to, int side, bool isKing, int *captured = nullptr);
    bool movePiece(int from, int to, int *captured = nullptr);

    QVector<QString> possibleMoves(int side);
};

#endif  // BOARD_H
