#include "canvas.h"
#include "Utils.h"
#include "Link.h"
#include <vector>
#include <QDebug>
#include <math.h>
#include <QGraphicsLineItem>

extern int axis_number;

Canvas::Canvas(QObject *parent) :
    QGraphicsScene(parent)
{
}

void Canvas::initialize(){
    links.clear();
    rootLink = new Link();
    links.push_back(rootLink);
    for(int i = 1; i < NUM_LINKS; i++){
        Link* tempLink = new Link();
        tempLink->setPrevious(links[i-1]);
        links[i-1]->setNext(tempLink);
        links.push_back(tempLink);
    }
    links[0]->setLength(150);
    links[1]->setLength(100);
    links[2]->setLength(75);
    updateLinks();
}

void Canvas::updateLinks(){
    blackBrush.setStyle(Qt::SolidPattern);
    blackPen.setStyle(Qt::SolidLine);
    blackPen.setWidth(5);
    Link* currLink = rootLink;
    while(true) {
        delete currLink->getDrawnLine();
        QGraphicsLineItem* newLine = this->addLine(currLink->getLine(),blackPen);
        currLink->setDrawnLine(newLine);
        if(currLink->getNext() == NULL)
            break;
        currLink = currLink->getNext();
    }
}

void Canvas::rotateCW()
{
    double newTheta = (links[axis_number-1]->getTheta()+BASE_ANGLE);
    qDebug() << "Clockwise. new theta: "<< newTheta <<endl;
    links[axis_number-1]->setTheta(newTheta);
    updateLinks();
}

void Canvas::rotateCCW()
{
    qDebug() << "counter-clockwise clicked" <<endl;
    links[axis_number-1]->setTheta((links[axis_number-1]->getTheta()-BASE_ANGLE));
    updateLinks();
}
