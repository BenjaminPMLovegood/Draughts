#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <QDialog>
#include <QWidget>

#include "qnumberinput.h"

namespace Ui {
    class ServerSettings;
}

class ServerSettings : public QDialog {
    Q_OBJECT

public:
    explicit ServerSettings(QWidget *parent = 0);
    ~ServerSettings();

    int portSelected;

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ServerSettings *ui;

    QNumberInput *port;

private slots:
    void onListen();
    void onExit();
};

#endif  // SERVERSETTINGS_H
