#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Canvas(this);

    QRectF rect = ui->graphicsView->rect();

    rect.setY((-rect.width()-10)/2);
    rect.setWidth(ui->graphicsView->height()-5);
    rect.setHeight(ui->graphicsView->width()-5);
    scene->setSceneRect(rect);

    ui->graphicsView->setScene(scene);
    scene->initialize();

    ui->graphicsView->rotate(270);
}

mainWindow::~mainWindow()
{
    delete ui;
}
