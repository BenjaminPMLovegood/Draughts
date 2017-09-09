#include "customboard.h"
#include "ui_customboard.h"

CustomBoard::CustomBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomBoard)
{
    ui->setupUi(this);
}

CustomBoard::~CustomBoard()
{
    delete ui;
}
