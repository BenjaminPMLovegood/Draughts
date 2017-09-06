#ifndef COMMONHEADER_H
#define COMMONHEADER_H

#include <QtNetwork>

template <typename T>
T __T_CONTAIN(T v, T flg) { return (v & flg) == flg; }

#define CONTAIN(v, flg) __T_CONTAIN<int>(v, flg)

QNetworkAddressEntry getCurrentInterfaceAddress();

#endif // COMMONHEADER_H
