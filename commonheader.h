#ifndef COMMONHEADER_H
#define COMMONHEADER_H

#include <QtNetwork>

#define BOARD_WIDTH 10
const int defaultTimeLimit = 300;
const QString defaultInitStatus = QString("bbbbbbbbbbbbbbbbbbbb          wwwwwwwwwwwwwwwwwwww");

#define CONTAIN(v, flg) (((v) & (flg)) == (flg))

QNetworkAddressEntry getCurrentInterfaceAddress();


#endif // COMMONHEADER_H
