#include "customboard.h"
#include "ui_customboard.h"

CustomBoard::CustomBoard(QWidget *parent)
    : QDialog(parent), ui(new Ui::CustomBoard) {
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint /*| Qt::WindowCloseButtonHint*/);
    this->setFixedSize(this->size());

    board = new DraughtsBoard(this);
    status = new Board();
    board->b = status;
}

CustomBoard::~CustomBoard() {
    delete ui;
}

void CustomBoard::on_ok_clicked() {

}

void CustomBoard::on_makeDefault_clicked() {
    delete status;
    status = new Board(defaultInitStatus);
    board->b = status;
    repaint();
}

void CustomBoard::on_loadA_clicked() {
    delete status;
    status = new Board(QString("      b ww    b b    w    b     b   b     w       "));
    board->b = status;
    repaint();
}

void CustomBoard::on_loadB_clicked() {
    delete status;
    status = new Board(QString("b     b ww    b b    w    b     b   b     w       "));
    board->b = status;
    repaint();
}
