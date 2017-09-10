#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>

#include "gameend.h"

MainWindow::MainWindow(GameClient *client, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), client(client) {
    ui->setupUi(this);

    this->setFixedSize(810, 500);

    board = new DraughtsBoard(this);
    board->setGeometry(30, 30, 440, 440);

    this->timer = new QTimer(this);

    ui->surrender->setEnabled(false);
    ui->offerADraw->setEnabled(false);

    connect(board, SIGNAL(onCellClick(int, int)), this, SLOT(onCellClick(int, int)));
    connect(client, SIGNAL(onMessage(QString)), this, SLOT(onMessage(QString)));
    connect(ui->offerADraw, SIGNAL(clicked()), this, SLOT(offerDraw()));
    connect(ui->surrender, SIGNAL(clicked()), this, SLOT(gg()));
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter(this).fillRect(rect(), QColor(0xff, 0xff, 0xff));

    this->QMainWindow::paintEvent(event);
}

void MainWindow::onCellClick(int row, int column) {
    if (!myTurn) return;
    if (!((row + column) & 1)) return;

    int id = fromCoordinatesToId(row, column);

    if (!valid[id]) return;

    this->ui->surrender->setEnabled(false);
    this->ui->offerADraw->setEnabled(false);

    if (selection != -1) {
        int r = fromIdToRow(selection), c = fromIdToColumn(selection);
        int dr = sign(row - r), dc = sign(column - c);
        int cnt = abs(row - r);

        for (int i = 1; i < cnt; ++i) {
            clear[fromCoordinatesToId(r + i * dr, c + i * dc)] = true;
        }

        status->setCell(row, column, status->cell(r, c));
        status->setCell(r, c, ' ');

        client->sendData(QString("move ") + QString::number(selection) + ' ' + QString::number(id));

        QSound::play(QString("://wav/move.wav"));
    } else {
        QSound::play("://wav/selected.wav");
    }

    for (int i = 0; i < 50; ++i) selected[i] = (i == selection || i == id);
    selection = id;

    curr = curr->sub[id];

    refreshValid();
    repaint();

    if (curr->end) {
        actAllCapture();

        int r = fromIdToRow(selection), c = fromIdToColumn(selection);
        if ((side == 1 && selection > 44) || (side == 2 && selection < 5)) status->setCell(r, c, status->cell(r, c) & 0xDF);

        delete root;
        root = curr = nullptr;

        myTurnEnds();
    }
}

void MainWindow::actAllCapture() {
    for (int i = 0; i < 50; ++i) {
        valid[i] = false;

        if (clear[i]) {
            status->setCell(fromIdToRow(i), fromIdToColumn(i), ' ');
            clear[i] = false;
        }
    }
}

void MainWindow::onMessage(QString msg) {
    qDebug() << "[Mainwindow]message received:" << msg;

    QString fi = msg.left(2);

    if (fi == "br") {
        QString cont = msg.right(50);
        status = new Board(cont);
        board->b = status;
        board->available = valid;
        board->selected = selected;

        for (int i = 0; i < 50; ++i) valid[i] = selected[i] = false;
        for (int i = 0; i < 50; ++i) clear[i] = false;
        selection = -1;

        repaint();
    } else if (fi == "yo") {
        QString cont = msg.mid(4);
        auto param = cont.split(' ');

        this->side = 1 + param[0].toInt();
        this->timeLeft = param[1].toInt();
        int whoFirst = param[2].toInt();

        refreshTime();

        if (this->side == whoFirst) myTurnBegins();
    } else if (fi == "fi") {
        QString cont = msg.mid(7);
        int param = cont.toInt();

        int acc = 0;
        switch (param) {
        case 0:
            {
            actAllCapture();
            repaint();

            int r = fromIdToRow(selection), c = fromIdToColumn(selection);
            if ((side == 2 && selection > 44) || (side == 1 && selection < 5)) status->setCell(r, c, status->cell(r, c) & 0xDF);

            myTurnBegins();}
            break;

        case 1:
            acc = QMessageBox::question(this, "Draw offer", "Would you like to accept your opponent's draw offer?", QMessageBox::Yes, QMessageBox::No);
            if (acc == QMessageBox::Yes) {
                myTurnEnds(2);

                endGame("Draw offer accepted.", 0);
            } else {
                myTurnEnds(3);
            }

            break;

        case 2:
            endGame("Draw offer accepted.", 0);
            break;

        case 3:
            QMessageBox::information(this, "Draw offer", "Draw offer rejected. Game continues.", QMessageBox::Yes);
            myTurnBegins();
            break;
        }
    } else if (fi == "gg") {
        QString cont = msg.mid(3);
        endGame(cont, 2);
    } else if (fi == "mo") {
        QString cont = msg.mid(5);
        auto param = cont.split(' ');

        int from = param[0].toInt();
        int to = param[1].toInt();

        int rf = fromIdToRow(from), cf = fromIdToColumn(from);
        int rt = fromIdToRow(to), ct = fromIdToColumn(to);
        int dr = sign(rt - rf), dc = sign(ct - cf);
        int cnt = abs(rt - rf);

        for (int i = 1; i < cnt; ++i) {
            clear[fromCoordinatesToId(rf + i * dr, cf + i * dc)] = true;
        }

        status->setCell(rt, ct, status->cell(rf, cf));
        status->setCell(rf, cf, ' ');

        for (int i = 0; i < 50; ++i) selected[i] = (i == from || i == to);

        selection = to;

        QSound::play(QString("://wav/move.wav"));

        repaint();
    }
}

void MainWindow::refreshTime() {
    ui->time->display(QString::number(timeLeft, 'f', 1));
}

void MainWindow::refreshValid() {
    for (int i = 0; i < 50; ++i) {
        if (curr->sub[i] != nullptr) valid[i] = true;
        else valid[i] = false;
    }
}

void MainWindow::myTurnBegins() {
    myTurn = true;
    timer->start(100);

    ui->surrender->setEnabled(true);
    ui->offerADraw->setEnabled(true);

    root = status->possibleMoves(side);
    curr = root;

    if (root->end) gg("No legal moves!");

    refreshValid();
    for (int i = 0; i < 50; ++i) selected[i] = false;
    selection = -1;
    repaint();
}

void MainWindow::myTurnEnds(int code) {
    myTurn = false;
    timer->stop();

    ui->surrender->setEnabled(false);
    ui->offerADraw->setEnabled(false);

    for (int i = 0; i < 50; ++i) selected[i] = clear[i] = valid[i] = false;
    selection = -1;
    repaint();

    client->sendData(QString("finish ") + QString::number(code));
}

void MainWindow::offerDraw() {
    if (!myTurn) return;

    myTurnEnds(1);
}

void MainWindow::gg(QString reason) {
    timer->stop();
    client->sendData(QString("gg ") + reason);
    endGame(reason, 1);
}

void MainWindow::tick() {
    if (!myTurn) return;

    timeLeft -= 0.1;
    if (timeLeft <= 0.0) { timeLeft = 0.0; refreshTime(); gg("Time out!"); }

    refreshTime();
}

void MainWindow::endGame(QString info, int code) {
    if (code == 1) QSound::play("://wav/lose.wav");
    else if (code == 2) QSound::play("://wav/win.wav");

    GameEnd::showGameEnd(info, code);
    this->close();
}
