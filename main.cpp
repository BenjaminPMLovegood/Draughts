#include <QApplication>
#include <QDir>
#include <QFile>
#include <QVector>
#include <QMessageBox>
#include "mainwindow.h"
#include "commonheader.h"

#define var auto

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    var returnValue = app.exec();
    return returnValue;
}
