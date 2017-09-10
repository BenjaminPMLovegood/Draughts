#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QVector>

#include "commonheader.h"
#include "connecttoserver.h"
#include "main.h"
#include "mainwindow.h"
#include "serversettings.h"
#include "startuppage.h"
#include "waiting.h"

#define var auto

ServerThread::ServerThread(int port, int timeLimit, QString status) {
    server = new GameServer(this);
    server->setupServer(port, timeLimit, status);
}

void ServerThread::run() {
    server->waitForTwoClients();
    emit onClientsConnected();
    server->launchServerSync();
}

GameClient client;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QString serverAddr = "";
    int serverPort = 0;
    ServerThread *server;

    StartupPage page;
    page.show();
    page.exec();

    if (page.exit) return 0;

    var isServer = page.isServer;
    qDebug() << (isServer ? "server" : "client");

    if (isServer) {
        QString initStatus = defaultInitStatus;

        ServerSettings settings;
        settings.show();
        settings.exec();

        serverPort = settings.portSelected;
        if (!~serverPort) return 0;

        server = new ServerThread(serverPort);
        server->start();
        server->moveToThread(server);

        client.connectToServer(getCurrentInterfaceAddress().ip(), serverPort);

        Waiting waitingPage;
        QObject::connect(server, SIGNAL(onClientsConnected()), &waitingPage, SLOT(close()));
        waitingPage.show();
        waitingPage.exec();

        serverAddr = getCurrentInterfaceAddress().ip().toString();
    } else {
        ConnectToServer conn;
        conn.show();
        conn.exec();

        serverAddr = conn.serverIp;
        serverPort = conn.serverPort;

        if (!~serverPort) return 0;

        client.connectToServer(QHostAddress(serverAddr), serverPort);

        Waiting waitingPage;
        QObject::connect(&client, SIGNAL(onConnected()), &waitingPage, SLOT(close()));
        waitingPage.show();
        waitingPage.exec();
    }

    MainWindow mw(&client);
    mw.show();
    int rv = app.exec();

    client.sock->disconnectFromHost();
    return rv;
}
