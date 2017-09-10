#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QtNetwork>
#include <QThread>
#include "commonheader.h"

class GameServer : public QObject {
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = nullptr);

    void setupServer(int port, int timeLimit = defaultTimeLimit, QString initStatus = defaultInitStatus);
    bool waitForTwoClients(); // start listening and return true after 2 clients connected
    bool launchServerSync(); // start the game, return whether the game ends successfully after the end

    QHostAddress getBlackAddr();
    QHostAddress getWhiteAddr();

private:
    int port, timeLimit;
    QString init;

    int cnt;

    QTcpServer *server;
    QTcpSocket *black, *white;

private slots:

};

#endif  // GAMESERVER_H
