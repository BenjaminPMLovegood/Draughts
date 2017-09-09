#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setFixedSize(810, 500);

    board = new DraughtsBoard(this);
    board->setGeometry(30, 30, 440, 440);

    connect(board, SIGNAL(onCellClick(int, int)), this, SLOT(onCellClick(int, int)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter(this).fillRect(rect(), QColor(0xff, 0xff, 0xff));

    this->QMainWindow::paintEvent(event);
}

void MainWindow::onCellClick(int row, int column) {
    qDebug() << row << column;
}
