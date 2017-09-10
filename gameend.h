#ifndef GAMEEND_H
#define GAMEEND_H

#include <QDialog>

namespace Ui {
class GameEnd;
}

class GameEnd : public QDialog
{
    Q_OBJECT

public:
    explicit GameEnd(QWidget *parent = 0);
    ~GameEnd();

    static void showGameEnd(QString desc, int code);

protected:
    void paintEvent(QPaintEvent *ev);

private:
    Ui::GameEnd *ui;
};

#endif // GAMEEND_H
