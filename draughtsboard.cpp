#include "draughtsboard.h"

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

DraughtsBoard::DraughtsBoard(QWidget *parent) : QWidget(parent) { ; }

#define SIZE 440
#define CELL_SIZE 40
#define CELL_COUNT 10
#define BORDER_SIZE 20

#define BORDER_COLOR QColor(114, 73, 56)
#define WHITE_COLOR QColor(238, 222, 215)
#define BLACK_COLOR QColor(179, 92, 55)

// painter
void DraughtsBoard::paintEvent(QPaintEvent *event) {
    QPainter p(this);

    this->resize(SIZE, SIZE);

    p.setRenderHint(QPainter::Antialiasing, true);
    paintBackground(p);

    event->accept();
}

void DraughtsBoard::paintBackground(QPainter &p) {
    QBrush blackBrush(BLACK_COLOR), whiteBrush(WHITE_COLOR), borderBrush(BORDER_COLOR);

    p.fillRect(0, 0, SIZE, SIZE, borderBrush);

    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < CELL_COUNT; ++j)
            p.fillRect(BORDER_SIZE + j * CELL_SIZE, BORDER_SIZE + i * CELL_SIZE, CELL_SIZE, CELL_SIZE, (i + j) & 1 ? blackBrush : whiteBrush);
}

// mouse handler
void DraughtsBoard::mousePressEvent(QMouseEvent *event) {
    while (event->button() == Qt::LeftButton) {
        auto pos = event->pos();
        auto x = pos.x();
        auto y = pos.y();

        if (x < BORDER_SIZE || y < BORDER_SIZE) break;
        if (x >= (SIZE - BORDER_SIZE) || y >= (SIZE - BORDER_SIZE)) break;

        int i = (y - BORDER_SIZE) / CELL_SIZE;
        int j = (x - BORDER_SIZE) / CELL_SIZE;

        emit onCellClick(i, j);

        event->accept();
        return;
    }

    event->ignore();
}
