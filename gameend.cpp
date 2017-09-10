#include "gameend.h"
#include "ui_gameend.h"

#include <QPainter>

GameEnd::GameEnd(QWidget *parent) :
    QDialog(parent), ui(new Ui::GameEnd) {
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    this->setFixedSize(this->size());
}

GameEnd::~GameEnd() { delete ui; }

void GameEnd::paintEvent(QPaintEvent *ev) {
    QPainter(this).fillRect(rect(), QColor(255, 255, 255));
    this->QDialog::paintEvent(ev);
}

void GameEnd::showGameEnd(QString desc, int code) {
    GameEnd diag;

    QString results[3] = {
        QString("Draw"),
        QString("Defeat"),
        QString("Victory")
    };

    diag.ui->result->setText(results[code]);
    diag.ui->desc->setText(desc);

    diag.setModal(true);
    diag.exec();
}
