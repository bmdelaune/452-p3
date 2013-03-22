#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "canvas.h"
#include <QtGui>
#include <QDebug>

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    /*Canvas* canvas = new Canvas(this);
    canvas->setParent(this);
    canvas->initialize();
*/
}

mainWindow::~mainWindow()
{
    delete ui;
}
