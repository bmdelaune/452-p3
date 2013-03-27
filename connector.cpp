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
    connect(this, SIGNAL(addY()), canvas, SLOT(addY()));
    connect(this, SIGNAL(subY()), canvas, SLOT(subY()));
    connect(this, SIGNAL(addX()), canvas, SLOT(addX()));
    connect(this, SIGNAL(subX()), canvas, SLOT(subX()));
    connect(&clientSock, SIGNAL(connected()), this, SLOT(ready()));
    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    connect(serverSock, SIGNAL(readyRead()), this, SLOT(readCommands()));
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
    ip = ipBox->text();
    if (QString::compare(ip, "") == 0)
    {
        status->setText("NETWORK STATUS: No IP specified. Disconnected.");
        return;
    }
    QHostAddress host(ip);
    status->setText("NETWORK STATUS: Connecting to " + ip + "...");
    clientSock.connectToHost(host, PORT);


}
void Connector::ready() {
    if (clientSock.state() != 3)
    {
        qDebug() << "CONNECTION STATUS " << clientSock.state();
        qDebug() << "CONNECTION ERROR " << clientSock.error();
        status->setText("NETWORK STATUS: Error connecting to " + ip + ". Disconnected.");
        connected = false;
    }
    else
    {
        status->setText("NETWORK STATUS: Connected to " + ip);
        connected = true;
        emit enableButtons();
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

void Connector::acceptConnection() {
    serverSock = server.nextPendingConnection();
    status->setText("NETWORK STATUS: Connected as server.");
}

void Connector::sendCommand(int command, int axis) {
    if (!connected)
    {
        qDebug() << "SEND ERROR: NOT CONNECTED";
        return;
    }
    char buf[2] = {command, axis};
    clientSock.write(buf);
}

void Connector::readCommands() {
    char buf[2] = {0};
    while (true)
    {
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
            canvas->addY();
        case SUBY:
            canvas->subY();
        case ADDX:
            canvas->addX();
        case SUBX:
            canvas->subX();
        default:
            qDebug() << "RECEIVE ERROR:" << buf[0];
        }
    }
}

void Connector::cdisconnect() {}
