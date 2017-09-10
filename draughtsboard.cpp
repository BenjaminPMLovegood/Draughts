#include "draughtsboard.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

DraughtsBoard::DraughtsBoard(QWidget *parent) : QWidget(parent) { b = nullptr; selected = available = false; }

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
    drawPieces(p);
    drawHints(p);

    event->accept();
}

void DraughtsBoard::paintBackground(QPainter &p) {
    QBrush blackBrush(BLACK_COLOR), whiteBrush(WHITE_COLOR), borderBrush(BORDER_COLOR);

    p.fillRect(0, 0, SIZE, SIZE, borderBrush);

    for (int i = 0; i < CELL_COUNT; ++i)
        for (int j = 0; j < CELL_COUNT; ++j)
            p.fillRect(BORDER_SIZE + j * CELL_SIZE, BORDER_SIZE + i * CELL_SIZE, CELL_SIZE, CELL_SIZE, (i + j) & 1 ? blackBrush : whiteBrush);

}

void DraughtsBoard::drawPieces(QPainter &p) {
    QBrush pbBrush(QColor(0, 0, 0)), pwBrush(QColor(255, 255, 255)), kgBrush(QColor(255, 215, 0));

    if (b != nullptr) {
        for (int i = 0; i < CELL_COUNT; ++i)
            for (int j = 0; j < CELL_COUNT; ++j) {
                char c = b->cell(i, j);
                int side = fromCharToSide(c);
                if (!side) continue;

                bool isKing = !(c & 32);

                if (side == 1) {
                    p.setBrush(pbBrush);
                    p.setPen(QPen(pbBrush.color()));
                    p.drawEllipse(BORDER_SIZE + j * CELL_SIZE + 5, BORDER_SIZE + i * CELL_SIZE + 5, 30, 30);
                } else {
                    p.setBrush(pwBrush);
                    p.setPen(QPen(pwBrush.color()));
                    p.drawEllipse(BORDER_SIZE + j * CELL_SIZE + 5, BORDER_SIZE + i * CELL_SIZE + 5, 30, 30);
                }

                if (isKing) {
                    p.setBrush(kgBrush);
                    p.setPen(QPen(kgBrush.color()));
                    p.drawEllipse(BORDER_SIZE + j * CELL_SIZE + 12, BORDER_SIZE + i * CELL_SIZE + 12, 16, 16);
                }
            }
    }
}

void DraughtsBoard::drawHints(QPainter &p) {
    QBrush rpBrush(QColor(255, 0, 0));

    if (selected != false) {

    }

    if (available != false) {
        for (int i = 0; i < 50; ++i) if (available[i]) {
            int r = fromIdToRow(i), c = fromIdToColumn(i);

            p.setBrush(rpBrush);
            p.setPen(QPen(rpBrush.color()));
            p.drawEllipse(BORDER_SIZE + c * CELL_SIZE + 17, BORDER_SIZE + r * CELL_SIZE + 17, 6, 6);
        }
    }
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
