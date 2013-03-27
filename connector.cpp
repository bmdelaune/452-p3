#include "network.h"

extern int axis_number;

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

void Connector::setup(QLabel *ql, QLineEdit *le, QPushButton *btn, Canvas *c) {
    status = ql;
    ipBox = le;
    modeBtn = btn;
    canvas = c;
}

void Connector::cconnect() {
    // client setup
    QString ip = ipBox->text();
    if (QString::compare(ip, "") == 0)
    {
        status->setText("NETWORK STATUS: No IP specified. Disconnected.");
        return;
    }
    QHostAddress host(ip);
    status->setText("NETWORK STATUS: Connecting to " + ip + "...");
    clientSock.connectToHost(host, PORT);
    if (clientSock.state() != 3)
    {
        qDebug() << "CONNECTION ERROR " << clientSock.error();
        status->setText("NETWORK STATUS: Error connecting to " + ip + ". Disconnected.");
        connected = false;
    }
    else
    {
        status->setText("NETWORK STATUS: Connected to " + ip);
        connected = true;
    }
}

void Connector::changeMode() {
    client = !client;
    // server mode - start server
    if (!client)
    {
        modeBtn->setText("Client Mode");
        if (connected)
            clientSock.close();
        status->setText("NETWORK STATUS: Awaiting connection...");
        server.listen(QHostAddress::Any, PORT);
        serverSock = server.nextPendingConnection();
        while (true)
        {
            readCommand();
        }
    }
    // client mode - stop server, wait for connect order
    else
    {
        modeBtn->setText("Server Mode");
        status->setText("NETWORK STATUS: Disconnected.");
        if (server.isListening() || serverSock->state() != 0)
            server.close();
    }
}

void Connector::sendCommand(int command) {}

void Connector::readCommand() {
    char buf[2] = {0};
    serverSock->read(buf, serverSock->bytesAvailable());
    switch(buf[0])
    {
    case CW:
        axis_number = buf[1];
        canvas->rotateCW();
    case CCW:
        axis_number = buf[1];
        canvas->rotateCCW();
    case ADDY:
        connect(this, SIGNAL(addY()), canvas, SLOT(addY()));
    case SUBY:
        connect(this, SIGNAL(subY()), canvas, SLOT(subY()));
    case ADDX:
        connect(this, SIGNAL(addX()), canvas, SLOT(addX()));
    case SUBX:
        connect(this, SIGNAL(subX()), canvas, SLOT(subX()));
    default:
        qDebug() << "RECEIVE ERROR:" << buf[0];
    }
}

void Connector::cdisconnect() {}
