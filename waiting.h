#ifndef WAITING_H
#define WAITING_H

#include <QDialog>

namespace Ui {
    class Waiting;
}

class Waiting : public QDialog {
    Q_OBJECT

public:
    explicit Waiting(QWidget *parent = 0);
    ~Waiting();

protected:
    void paintEvent(QPaintEvent *ev);

private:
    Ui::Waiting *ui;
};

#endif  // WAITING_H
