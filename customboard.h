#ifndef CUSTOMBOARD_H
#define CUSTOMBOARD_H

#include <QDialog>

namespace Ui {
class CustomBoard;
}

class CustomBoard : public QDialog
{
    Q_OBJECT

public:
    explicit CustomBoard(QWidget *parent = 0);
    ~CustomBoard();

private:
    Ui::CustomBoard *ui;
};

#endif // CUSTOMBOARD_H
