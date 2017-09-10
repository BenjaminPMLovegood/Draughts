#include "waiting.h"
#include "ui_waiting.h"

#include <QPainter>

Waiting::Waiting(QWidget *parent) :
    QDialog(parent), ui(new Ui::Waiting) {
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint /*| Qt::WindowCloseButtonHint*/);
    this->setFixedSize(this->size());
}

void Waiting::paintEvent(QPaintEvent *ev) {
    QPainter(this).fillRect(rect(), QColor(255, 255, 255));
    this->QDialog::paintEvent(ev);
}

Waiting::~Waiting() {
    delete ui;
}
