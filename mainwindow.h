#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "ui_mainwindow.h"

class CustomScene : public QGraphicsScene
{
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        qDebug() << event->scenePos();
    }
};

namespace Ui {
    class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();
    
private:
    Ui::mainWindow *ui;
    QGraphicsScene* scene;
};

#endif // MAINWINDOW_H
