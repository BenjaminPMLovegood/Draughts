#include "serversettings.h"
#include "ui_serversettings.h"

#include "commonheader.h"
#include <QLineEdit>
#include <QPainter>
#include <QMessageBox>

ServerSettings::ServerSettings(QWidget *parent) :
    QDialog(parent), ui(new Ui::ServerSettings) {
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint /*| Qt::WindowCloseButtonHint*/);
    this->setFixedSize(this->size());

    port = new QNumberInput(this);
    port->setGeometry(ui->placeHolderPort->geometry());
    ui->placeHolderPort->hide();

    ui->localIp->setText(getCurrentInterfaceAddress().ip().toString());

    connect(ui->startListen, SIGNAL(clicked()), this, SLOT(onListen()));
    connect(ui->exitPrg, SIGNAL(clicked()), this, SLOT(onExit()));
}

ServerSettings::~ServerSettings() {
    delete ui;
}

void ServerSettings::paintEvent(QPaintEvent *ev) {
    QPainter(this).fillRect(rect(), QColor(255, 255, 255));
    this->QDialog::paintEvent(ev);
}

void ServerSettings::onListen() {
    bool ok = false;
    int port = this->port->text().toInt(&ok);

    if (ok && (port < 1024 || port > 65535)) ok = false;

    if (!ok) {
        QMessageBox::warning(this, "Draughts", "invalid port (1024 ~ 65535)");
        return;
    } else {
        this->portSelected = port;
        this->close();
    }
}

void ServerSettings::onExit() {
    this->portSelected = -1;
    this->close();
}
