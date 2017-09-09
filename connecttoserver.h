#ifndef CONNECTTOSERVER_H
#define CONNECTTOSERVER_H

#include <QDialog>
#include <QWidget>
#include <QtNetwork>

#include "qnumberinput.h"

namespace Ui {
    class ConnectToServer;
}

class ConnectToServer : public QDialog {
    Q_OBJECT

public:
    explicit ConnectToServer(QWidget *parent = 0);
    ~ConnectToServer();

    QString serverIp;
    int serverPort;

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ConnectToServer *ui;

    QNumberInput *port;
    QNumberInput *ip;

private slots:
    void onConnect();
    void onExit();
};

#endif  // CONNECTTOSERVER_H
