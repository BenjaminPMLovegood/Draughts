#include "waiting.h"
#include "ui_waiting.h"

Waiting::Waiting(QWidget *parent) :
    QDialog(parent), ui(new Ui::Waiting) {
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    this->setFixedSize(this->size());
}

Waiting::~Waiting() {
    delete ui;
}
