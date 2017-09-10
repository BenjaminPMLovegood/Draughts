#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "commonheader.h"
#include "possiblemovetreenode.h"

// 0 : none, 1 : black, 2 : white
inline int fromCharToSide(char chr) { return (chr | 32) == 'w' ? 2 : ((chr | 32) == 'b' ? 1 : 0); }
inline int fromCoordinatesToId(int row, int column) { return row * 5 + (column / 2); }
inline int fromIdToRow(int id) { return id / 5; }
inline int fromIdToColumn(int id) { return ((id % 5) << 1) + 1 - ((id / 5) & 1); }
inline int sign(int v) { return v > 0 ? (int)(bool)v : -1; }
//inline int abs(int v) { return v > 0 ? v : -v; }
inline bool inBoard(int r, int c) { return r >= 0 && r < 10 && c >= 0 && c < 10; }

class Board {
    char _board[BOARD_WIDTH][BOARD_WIDTH];  // ' ' or 'w' or 'b' or 'W' or 'B'

    void dfsCap(PossibleMoveTreeNode *currNode, int currPos, int side, bool captured[50], bool isKing);
    void findStep(PossibleMoveTreeNode *currNode, int currPos, int side, bool isKing);

public:
    Board();
    Board(QString status);

    PossibleMoveTreeNode* possibleMoves(int side);

    char cell(int r, int c) const;
    void setCell(int r, int c, char v);

    QString toString();
};

#endif  // BOARD_H
