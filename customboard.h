#ifndef CUSTOMBOARD_H
#define CUSTOMBOARD_H

#include <QDialog>

#include "draughtsboard.h"
#include "board.h"

namespace Ui {
    class CustomBoard;
}

class CustomBoard : public QDialog {
    Q_OBJECT

public:
    explicit CustomBoard(QWidget *parent = 0);
    ~CustomBoard();

    QString res = defaultInitStatus;

private slots:
    void on_ok_clicked();

    void on_makeDefault_clicked();

    void on_loadA_clicked();

    void on_loadB_clicked();

private:
    Ui::CustomBoard *ui;

    DraughtsBoard *board;
    Board *status;
};

#endif  // CUSTOMBOARD_H
