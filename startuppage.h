#ifndef STARTUPPAGE_H
#define STARTUPPAGE_H

#include <QDialog>
#include <QWidget>

namespace Ui {
    class StartupPage;
}

class StartupPage : public QDialog {
    Q_OBJECT

public:
    explicit StartupPage(QWidget *parent = 0);
    ~StartupPage();

    bool isServer;

private:
    Ui::StartupPage *ui;

protected:
    void paintEvent(QPaintEvent *ev);

public slots:
    void serverChosen();
    void clientChosen();

};

#endif  // STARTUPPAGE_H
