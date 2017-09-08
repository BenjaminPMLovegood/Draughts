#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setFixedSize(this->size());

    channel = new Channel();

    webChannel = new QWebChannel(this);
    webChannel->registerObject(QString("channel"), channel);

    QWebEngineView *view = new QWebEngineView(this);
    view->setGeometry(0, 0, this->width(), this->height());
    view->page()->setWebChannel(webChannel);

    view->load(QUrl("qrc:/ui/main.html"));
    view->show();
}

MainWindow::~MainWindow() { delete ui; }
