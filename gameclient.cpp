#include "gameclient.h"

#include <QTextCodec>
#include <QThread>

GameClient::GameClient(QObject *parent) : QObject(parent) {  }

void GameClient::connectToServer(QHostAddress addr, int port) {
    QThread::msleep(50);

    sock = new QTcpSocket(this);
    sock->bind();

    sock->connectToHost(addr, port);

    connect(sock, SIGNAL(readyRead()), this, SLOT(onSocketData()));
    connect(sock, SIGNAL(connected()), this, SIGNAL(onConnected()));
}

void GameClient::sendData(QString str) {
    auto data = QTextCodec::codecForName("Utf-8")->fromUnicode(str + '$');
    sock->write(data);
    sock->flush();
}

void GameClient::onSocketData() {
    auto data = sock->readAll();
    QString cont = QTextCodec::codecForName("Utf-8")->toUnicode(data);
    auto cmds = cont.split('$');

    for (QString v : cmds) {
        if (v.length() > 0) emit onMessage(v);
    }
}
