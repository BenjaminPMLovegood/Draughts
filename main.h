#ifndef MAIN_H
#define MAIN_H

#include <QThread>
#include "commonheader.h"
#include "gameserver.h"
#include "gameclient.h"

class ServerThread : public QThread {
    Q_OBJECT

public:
    ServerThread(int port, int timeLimit = defaultTimeLimit, QString status = defaultInitStatus);

protected:
    void run();

private:
    GameServer *server;

signals:
    void onClientsConnected();
};

extern GameClient client;

#endif  // MAIN_H
