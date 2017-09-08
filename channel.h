#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QtNetwork>

class Channel : public QObject {
    Q_OBJECT
public:
    explicit Channel(QObject *parent = nullptr);

signals:
    void displayServerInfo(QString info);
    void refreshBoard(QString status);

    void waitForServerAddr();

public slots:
    void onClientConnected();

    void onCellClick(int i, int j);
    void onSurrender();

    void onRoleChosen(bool isServer);

private:
    QTcpServer *server;
    QTcpSocket *sock;
};

#endif  // CHANNEL_H
