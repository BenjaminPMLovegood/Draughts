#include "qnumberinput.h"

#include <QKeyEvent>

QNumberInput::QNumberInput(QWidget *parent) : QLineEdit(parent) {}

void QNumberInput::keyPressEvent(QKeyEvent *ev) {
    bool acc = false;
    if (ev->key() >= '0' && ev->key() <= '9') acc = true;
    else if (ev->key() == Qt::Key_Delete || ev->key() == Qt::Key_Backspace) acc = true;
    else if (ev->key() == '.') acc = true;

    if (acc) this->QLineEdit::keyPressEvent(ev);
    else ev->accept();
}
