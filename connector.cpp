#include "network.h"

void getMyIP() {
    QNetworkInterface *qni = new QNetworkInterface();
    QList<QHostAddress> ips;
    QList<QString> ipstr;
    QString str;
    ips = qni->allAddresses();
    for (int i = 0; i < ips.size(); i++)
    {
        str = ips.at(i).toString();
        qDebug() << i << " : " << str;
    }
}

Connector::Connector(QWidget *parent)
    :  QObject(parent) {
    connected = false;
    client = true;
}

Connector::~Connector() {}

void Connector::setup(QLabel *ql, QLineEdit *le, QPushButton *btn) {
    status = ql;
    ipBox = le;
    modeBtn = btn;
}

void Connector::cconnect() {
    QString ip = ipBox->text();
    if (QString::compare(ip, "") == 0)
    {
        status->setText("NETWORK STATUS: No IP specified.");
        return;
    }
    status->setText("NETWORK STATUS: Connecting to " + ip + "...");
}

void Connector::changeMode() {
    client = !client;
    if (client)
        qDebug() << "client true";
    else
        qDebug() << "client false";
    if (client)
        modeBtn->setText("Server Mode");
    else
        modeBtn->setText("Client Mode");
}

void Connector::sendCommand(int command) {}

void Connector::cdisconnect() {}
