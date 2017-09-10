#include "gameserver.h"

#include <QTextCodec>
#include <QDateTime>

GameServer::GameServer(QObject *parent) : QObject(parent) {
}

void GameServer::setupServer(int port, int timeLimit, QString initStatus, bool whiteFirst) {
    this->server = new QTcpServer(this);
    this->port = port;
    this->timeLimit = timeLimit;
    this->init = initStatus;
    this->whiteFirst = whiteFirst;
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
    qDebug() << "[Server]game start";
    black->write(QTextCodec::codecForName("Utf-8")->fromUnicode(QString("broad ") + init + '$'));
    white->write(QTextCodec::codecForName("Utf-8")->fromUnicode(QString("broad ") + init + '$'));
    black->write(QTextCodec::codecForName("Utf-8")->fromUnicode(QString("you 0 ") + QString::number(timeLimit) + (whiteFirst ? " 2$"  : " 1$")));
    white->write(QTextCodec::codecForName("Utf-8")->fromUnicode(QString("you 1 ") + QString::number(timeLimit) + (whiteFirst ? " 2$"  : " 1$")));

    black->flush(); white->flush();
    qDebug() << "[Server]init data written";

    bool gg = false;

    while (!gg) {
        black->waitForReadyRead(50);
        white->waitForReadyRead(50);

        if (black->bytesAvailable() > 0) {
            auto data = black->readAll();
            qDebug() << "[Server]data from black:" << data.data();

            gg = isGG(data);
            white->write(data);
            white->flush();
        }

        if (white->bytesAvailable() > 0) {
            auto data = white->readAll();
            qDebug() << "[Server]data from white:" << data.data();

            gg = isGG(data);
            black->write(data);
            black->flush();
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
