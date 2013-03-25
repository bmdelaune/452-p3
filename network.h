#ifndef NETWORK_H
#define NETWORK_H

#include <QNetworkInterface>
#include <QTcpSocket>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>

#define CW 1
#define CCW 2
#define ADDY 3
#define SUBY 4
#define ADDX 5
#define SUBX 6

void getMyIP();

class Connector : public QObject {
    Q_OBJECT
public:
    bool client;

    Connector(QWidget *parent = 0);
    ~Connector();
    void setup(QLabel *ql, QLineEdit *le, QPushButton *btn);
public slots:
    void cconnect();
    void changeMode();
    void sendCommand(int command);
    void cdisconnect();
private:
    bool connected;
    QTcpSocket s;
    QLabel *status;
    QLineEdit *ipBox;
    QPushButton *modeBtn;
};

#endif // NETWORK_H
