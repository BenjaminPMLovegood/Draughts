#ifndef QNUMBERIMPUT_H
#define QNUMBERIMPUT_H

#include <QLineEdit>

class QNumberInput : public QLineEdit {
public:
    QNumberInput(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *ev) override;
};

#endif  // QNUMBERIMPUT_H
