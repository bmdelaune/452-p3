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

    rect.setX(-(rect.width()-10)/2);
    rect.setWidth(ui->graphicsView->width()-5);
    rect.setHeight(ui->graphicsView->height()-5);
    scene->setSceneRect(rect);

    ui->graphicsView->setScene(scene);
    scene->initialize();

    ui->graphicsView->rotate(180);


    connect(ui->cwiseBtn, SIGNAL(clicked()), scene, SLOT(rotateCW()));
    connect(ui->ccwiseBtn, SIGNAL(clicked()), scene, SLOT(rotateCCW()));
    connect(ui->xPlus, SIGNAL(clicked()), scene, SLOT(addX()));
    connect(ui->xMinus, SIGNAL(clicked()), scene, SLOT(subX()));
    connect(ui->yPlus, SIGNAL(clicked()), scene, SLOT(addY()));
    connect(ui->yMinus, SIGNAL(clicked()), scene, SLOT(subY()));
    connect(ui->paintBtn, SIGNAL(clicked()), scene, SLOT(paintClicked()));
    connect(ui->brushColor, SIGNAL(clicked()), scene, SLOT(changeColor()));
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
