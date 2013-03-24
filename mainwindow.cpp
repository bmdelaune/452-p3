#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QPointF>
#include "canvas.h"

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
    ui->graphicsView->setMouseTracking(true);
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

/*void mainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton
        && iconLabel->geometry().contains(event->pos())) {

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        mimeData->setText(commentEdit->toPlainText());
        drag->setMimeData(mimeData);
        drag->setPixmap(iconPixmap);

        Qt::DropAction dropAction = drag->exec();
    }
}

void DragWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setData(mimeType, data);
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}*/

void mainWindow::dragMoveEvent(QDragMoveEvent * e)
{
    QPointF pt = ui->graphicsView->mapToScene(e->pos());
    scene->setX(pt.x()+10);
    scene->setY(pt.y()+25);
    qDebug() <<"x: "<<pt.x();
    qDebug() <<"y: "<<pt.y();
    scene->worldMove();
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
