#include "channel.h"
#include "commonheader.h"
#include <QDebug>

Channel::Channel(QObject *parent) : QObject(parent) {
}

void Channel::onCellClick(int i, int j) {
    qDebug() << i << j;
}

void Channel::onSurrender() {
}

void Channel::onRoleChosen(bool isServer) {
    if (isServer) {
        server = new QTcpServer(this);
        server->setMaxPendingConnections(1);
        server->listen();

        sock = nullptr;
        connect(server, SIGNAL(newConnection()), this, SLOT(onClientConnected()));

        QString msg = QString("{ \"ip\": \"") + getCurrentInterfaceAddress().ip().toString() + "\", \"port\":" + QString::number(server->serverPort()) + "}"; qDebug() << msg;
        emit displayServerInfo(msg);
    } else {
        emit waitForServerAddr();
    }
}

void Channel::onClientConnected() {
    if (sock != nullptr) {
        auto conn = server->nextPendingConnection();
        conn->disconnectFromHost();
        conn->close();

        return;
    }

    sock = server->nextPendingConnection();
}
