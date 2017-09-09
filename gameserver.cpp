#include "gameserver.h"

#include <QTextCodec>
#include <QDateTime>

GameServer::GameServer(QObject *parent) : QObject(parent) {
}

void GameServer::setupServer(int port, int timeLimit, QString initStatus) {
    this->server = new QTcpServer(this);
    this->port = port;
}

bool GameServer::waitForTwoClients() {
    server->setMaxPendingConnections(2);
    server->listen(QHostAddress::AnyIPv4, port);

    cnt = 0;
    while (cnt < 2) {
        server->waitForNewConnection(50);

        if (!server->hasPendingConnections()) continue;

        QTcpSocket **sock;
        sock = cnt ? &black : &white;

        *sock = server->nextPendingConnection();
        ++cnt;
    }

    return true;
}

bool isGG(const QByteArray &arr) {
    QString value = QTextCodec::codecForName("Utf-8")->toUnicode(arr);
    auto cmds = value.split('$');

    for (QString v : cmds) {
        if (v.length() >= 2 && v[0] == 'g' && v[1] == 'g') return true;
    }

    return false;
}

bool GameServer::launchServerSync() {
    bool gg = false;

    while (!gg) {
        QThread::sleep(50);

        if (black->bytesAvailable() > 0) {
            auto data = black->readAll();

            gg = isGG(data);
            white->write(data);
        }

        if (white->bytesAvailable() > 0) {
            auto data = white->readAll();

            gg = isGG(data);
            black->write(data);
        }
    }

    black->disconnectFromHost();
    white->disconnectFromHost();

    return true;
}

QHostAddress GameServer::getBlackAddr() {
    return black->peerAddress();
}

QHostAddress GameServer::getWhiteAddr() {
    return white->peerAddress();
}
