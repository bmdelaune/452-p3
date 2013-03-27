#ifndef NETWORK_H
#define NETWORK_H

#include <QNetworkInterface>
#include <QTcpSocket>
#include <QTcpServer>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include "canvas.h"

#define CW 1
#define CCW 2
#define ADDY 3
#define SUBY 4
#define ADDX 5
#define SUBX 6
#define PORT 9009

void getMyIP();

class Connector : public QObject {
    Q_OBJECT
public:
    bool client; // true if client, false if server
    bool connected;
    Connector(QWidget *parent = 0);
    ~Connector();
    void setup(QLabel *ql, QLineEdit *le, QPushButton *btn, Canvas *c);
signals:
    void enableButtons();
    void addY();
    void subY();
    void addX();
    void subX();
public slots:
    void cconnect();
    void ready();
    void acceptConnection();
    void changeMode();
    void sendCommand(int command, int axis);
    void readCommands();
    void cdisconnect();
private:
    QString ip;
    QTcpServer server;
    QTcpSocket *serverSock;
    QTcpSocket clientSock;
    QLabel *status;
    QLineEdit *ipBox;
    QPushButton *modeBtn;
    Canvas *canvas;
};

#endif // NETWORK_H
