#include "connecttoserver.h"
#include "ui_connecttoserver.h"

#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
#include <QRegExp>

ConnectToServer::ConnectToServer(QWidget *parent)
    : QDialog(parent), ui(new Ui::ConnectToServer) {
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint /*| Qt::WindowCloseButtonHint*/);
    this->setFixedSize(this->size());

    port = new QNumberInput(this);
    port->setGeometry(ui->placeHolderPort->geometry());
    ui->placeHolderPort->hide();

    ip = new QNumberInput(this);
    ip->setGeometry(ui->placeHolderIp->geometry());
    ui->placeHolderIp->hide();

    connect(ui->connectSrv, SIGNAL(clicked()), this, SLOT(onConnect()));
    connect(ui->exitPrg, SIGNAL(clicked()), this, SLOT(onExit()));

}

ConnectToServer::~ConnectToServer() {
    delete ui;
}

void ConnectToServer::paintEvent(QPaintEvent *ev) {
    QPainter(this).fillRect(rect(), QColor(255, 255, 255));
    this->QDialog::paintEvent(ev);
}

void ConnectToServer::onConnect() {
    QRegExp rx("^([1]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])\\.([1]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])\\.([1]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])\\.([1]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])$");

    QString srvIp = ip->text(), srvPort = port->text();
    if (!rx.exactMatch(srvIp)) {
        QMessageBox::warning(this, "Draughts", "Invalid ip");
        return;
    }

    bool ok = false;
    int port = srvPort.toInt(&ok);

    if (ok && (port < 1024 || port > 65535)) ok = false;

    if (!ok) {
        QMessageBox::warning(this, "Draughts", "invalid port (1024 ~ 65535)");
        return;
    }

    this->serverIp = srvIp;
    this->serverPort = port;
    this->close();
}

void ConnectToServer::onExit() {
    this->serverPort = -1;
    this->close();
}
