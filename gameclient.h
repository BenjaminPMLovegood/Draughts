#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QtNetwork>

class GameClient : public QObject {
    Q_OBJECT
public:
    explicit GameClient(QObject *parent = nullptr);

    void connectToServer(QHostAddress addr, int port);
    void sendData(QString data);

signals:
    void onMessage(QString message);
    void onConnected();

private:public:
    QTcpSocket *sock;

private slots:
    void onSocketData();

};

#endif  // GAMECLIENT_H
