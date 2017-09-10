#include "startuppage.h"
#include "ui_startuppage.h"

#include <QPainter>

StartupPage::StartupPage(QWidget *parent)
    : QDialog(parent), ui(new Ui::StartupPage) {
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    this->setFixedSize(this->size());

    connect(ui->runAsServer, SIGNAL(clicked()), this, SLOT(serverChosen()));
    connect(ui->runAsClient, SIGNAL(clicked()), this, SLOT(clientChosen()));

    exit = true;
}

StartupPage::~StartupPage() { delete ui; }

void StartupPage::paintEvent(QPaintEvent *ev) {
    QPainter(this).fillRect(rect(), QColor(255, 255, 255));
    this->QDialog::paintEvent(ev);
}

void StartupPage::serverChosen() { exit = false; this->isServer = true; this->close(); }
void StartupPage::clientChosen() { exit = false; this->isServer = false; this->close(); }
