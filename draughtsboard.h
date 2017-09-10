#ifndef DRAUGHTSBOARD_H
#define DRAUGHTSBOARD_H

#include <QWidget>

#include "board.h"

class DraughtsBoard : public QWidget {
    Q_OBJECT
public:
    explicit DraughtsBoard(QWidget *parent = nullptr);
    Board *b;

    bool *selected;
    bool *available;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void paintBackground(QPainter & p);
    void drawPieces(QPainter & p);
    void drawHints(QPainter & p);

signals:
    void onCellClick(int row, int column);

public slots:
};

#endif  // DRAUGHTSBOARD_H
