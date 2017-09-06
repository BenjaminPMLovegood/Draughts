#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>

class Channel : public QObject {
    Q_OBJECT
public:
    explicit Channel(QObject *parent = nullptr);

signals:
    void displayServerInfo(QString info);
    void refreshBoard(QString status);

public slots:

    void onCellClick(int i, int j);
    void onSurrender();

    void onRoleChosen(bool isServer);
};

#endif  // CHANNEL_H
