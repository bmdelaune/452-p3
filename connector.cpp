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
    connect(&clientSock, SIGNAL(connected()), this, SLOT(ready()));
    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

Connector::~Connector() {}

void Connector::setup(QLabel *ql, QLineEdit *le, QPushButton *btn, Canvas *c) {
    status = ql;
    ipBox = le;
    modeBtn = btn;
    canvas = c;
    connect(this, SIGNAL(addY()), canvas, SLOT(addY()));
    connect(this, SIGNAL(subY()), canvas, SLOT(subY()));
    connect(this, SIGNAL(addX()), canvas, SLOT(addX()));
    connect(this, SIGNAL(subX()), canvas, SLOT(subX()));
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
    // client connection is ready
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
    connect(serverSock, SIGNAL(readyRead()), this, SLOT(readCommands()));
}

void Connector::sendCommand(int command, int axis) {
    if (!client)
    {
        qDebug() << "SEND - NOT CLIENT";
    }
    if (!connected)
    {
        qDebug() << "SEND ERROR: NOT CONNECTED";
        return;
    }
    char buf[2] = {command, axis};
    qDebug() << "SENDING: " << (int) buf[0] << ", " << (int) buf[1];
    clientSock.write(buf);
}

void Connector::readCommands() {
    if (client)
    {
        qDebug() << "READ - NOT SERVER";
        return;
    }
    char buf[2] = {0};

        serverSock->read(buf, serverSock->bytesAvailable());
        int command = int(buf[0]);
        int axis = int(buf[1]);
        switch(command)
        {
        case CW:
            axis_number = axis;
            canvas->rotateCW();
        case CCW:
            axis_number = axis;
            canvas->rotateCCW();
        case ADDY:
            emit addY();
        case SUBY:
            emit subY();
        case ADDX:
            emit addX();
        case SUBX:
            emit subX();
        default:
            qDebug() << "RECEIVE ERROR:" << command;
    }
}

void Connector::cdisconnect() {}
