#include "commonheader.h"

#define MAKE_DEFAULT_ADDRESS_ENTRY(name) \
    QNetworkAddressEntry name; \
    name.setBroadcast(QHostAddress("192.168.1.255")); \
    name.setNetmask(QHostAddress("255.255.255.0")); \
    name.setIp(QHostAddress("127.0.0.1"));

QNetworkAddressEntry getCurrentInterfaceAddress() {
    for (auto i : QNetworkInterface::allInterfaces()) {
        auto flg = i.flags();
        if (! CONTAIN(flg, QNetworkInterface::IsUp | QNetworkInterface::IsRunning | QNetworkInterface::CanBroadcast)) continue;
        if (CONTAIN(flg, QNetworkInterface::IsLoopBack) || CONTAIN(flg, QNetworkInterface::IsPointToPoint)) continue;

        if (i.humanReadableName().indexOf(QString("Virtual")) != -1) continue;

        for (auto a : i.addressEntries()) {
            if (a.ip().toString().length() >= 16) continue;
            if (a.prefixLength() < 0) continue;

            return a;
        }
    }

    MAKE_DEFAULT_ADDRESS_ENTRY(rv);
    return rv;
}
