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
    board->setGeometry(30, 30, 440, 440);
    board->repaint();

    connect(ui->ok, SIGNAL(clicked()), this, SLOT(on_ok_clicked()));
    connect(ui->loadA, SIGNAL(clicked()), this, SLOT(on_loadA_clicked()));
    connect(ui->loadB, SIGNAL(clicked()), this, SLOT(on_loadB_clicked()));
    connect(ui->makeDefault, SIGNAL(clicked()), this, SLOT(on_makeDefault_clicked()));
    connect(board, SIGNAL(onCellClick(int, int)), this, SLOT(onCellClick(int, int)));
}

CustomBoard::~CustomBoard() {
    delete ui;
}

void CustomBoard::on_ok_clicked() {
    this->res = status->toString();
    this->tl = ui->spinBox->value();
    this->whiteFirst = ui->whiteFirst->checkState() == Qt::Checked;

    close();
}

void CustomBoard::on_makeDefault_clicked() {
    delete status;
    status = new Board(defaultInitStatus);
    board->b = status;
    board->repaint();
}

void CustomBoard::on_loadA_clicked() {
    delete status;
    status = new Board(QString("      b ww    b b    w    b     b   b     w       "));
    board->b = status;
    board->repaint();
}

void CustomBoard::on_loadB_clicked() {
    delete status;
    status = new Board(QString("b     b ww    b b    w    b     b   b     w       "));
    board->b = status;
    board->repaint();
}

void CustomBoard::onCellClick(int i, int j) {
    switch (status->cell(i, j)) {
    case ' ':
        status->setCell(i, j, 'w');
        break;
    case 'w':
        status->setCell(i, j, 'b');
        break;
    case 'b':
        status->setCell(i, j, 'W');
        break;
    case 'W':
        status->setCell(i, j, 'B');
        break;
    case 'B':
        status->setCell(i, j, ' ');
    default:
        break;
    }

    repaint();
}
