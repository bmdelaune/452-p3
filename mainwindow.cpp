#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>

extern int axis_number;

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


    connect(ui->cwiseBtn, SIGNAL(clicked()), scene, SLOT(rotateCW()));
    connect(ui->ccwiseBtn, SIGNAL(clicked()), scene, SLOT(rotateCCW()));
}

void mainWindow::on_axisList_itemClicked(QListWidgetItem *item)
{
    QString qstr_axis_number =0;
    qstr_axis_number = item->text();
    axis_number = qstr_axis_number.toInt();
    qDebug()<<"axis number clicked: "<<axis_number<<endl;
}

mainWindow::~mainWindow()
{
    delete ui;
}
