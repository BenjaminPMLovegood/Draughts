#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QMainWindow>
#include <QWebChannel>
#include <QWebEngineView>
#include <QTimer>
#include "draughtsboard.h"
#include "gameclient.h"
#include "board.h"
#include "possiblemovetreenode.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(GameClient *client, QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;

    DraughtsBoard *board;
    Board *status;

    GameClient *client;

    int side;
    bool myTurn;
    double timeLeft;
    QTimer *timer;

    bool valid[50], selected[50], clear[50];

    int selection;

    PossibleMoveTreeNode *root;
    PossibleMoveTreeNode *curr;

    void refreshValid();
    void actAllCapture();

private slots:
    void refreshTime();
    void myTurnBegins();
    void myTurnEnds(int code = 0); // 0 : a move performed, 1 : offer a draw, 2 : draw offer accepted, 3 : draw offer rejected
    void gg(QString reason = QString("Surrender!"));
    void tick();
    void offerDraw();

    void endGame(QString info, int code); // 0 : draw, 1 : lose, 2 : win

public slots:
    void onCellClick(int row, int column);
    void onMessage(QString msg);

};

#endif  // MAINWINDOW_H
