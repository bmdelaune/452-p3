#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Canvas(this);

    QRectF rect = ui->graphicsView->rect();
    ui->graphicsView->translate(100,100);
    //ui->graphicsView->rotate(270);
    //ui->graphicsView->translate(-200,0);
    /*rect.setX((-rect.width()-10)/2);
    rect.setY((-rect.height()-10));
    rect.setWidth(ui->graphicsView->width()-1);
    rect.setHeight(ui->graphicsView->height()-1);*/
    scene->setSceneRect(rect);

    scene->initialize();
    ui->graphicsView->setScene(scene);

}

mainWindow::~mainWindow()
{
    delete ui;
}
