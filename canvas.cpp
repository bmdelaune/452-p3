#include "canvas.h"
#include "Utils.h"
#include "Link.h"
#include <vector>
#include <QDebug>
#include <math.h>
#include <QGraphicsLineItem>
#include <QtWidgets/QColorDialog>

extern int axis_number;

Canvas::Canvas(QObject *parent) :
    QGraphicsScene(parent)
{
}

void Canvas::initialize(){
    links.clear();
    x, y = 0;

    brushSize = 5;
    paintToggle = false;
    paintPen.setColor(Qt::red);
    paintBrush.setColor(Qt::red);
    paintBrush.setStyle(Qt::SolidPattern);
    paintPen.setWidth(2);
    paintPen.setStyle(Qt::SolidLine);

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

    x = calcX();
    y = calcY();

    paint();
}

void Canvas::rotateCW()
{
    double newTheta = (links[axis_number-1]->getTheta()+BASE_ANGLE);
    links[axis_number-1]->setTheta(newTheta);
    updateLinks();
}

void Canvas::rotateCCW()
{
    double newTheta = (links[axis_number-1]->getTheta()-BASE_ANGLE);
    links[axis_number-1]->setTheta(newTheta);
    updateLinks();
}

void Canvas::addX()
{
    newX = x+XYMOVE;
    newY = y;
    worldMove();
}

void Canvas::subX()
{
    newX = x-XYMOVE;
    newY = y;
    worldMove();
}

void Canvas::addY()
{
    newX = x;
    newY = y+XYMOVE;
    worldMove();
}

void Canvas::subY()
{
    newX = x;
    newY = y-XYMOVE;
    worldMove();
}

double Canvas::calcX(){
    double x0 = 0;
    Link* currLink = rootLink;
    while(true){
        x0 += currLink->getLength()*cos(currLink->getOrientation()*DEG_TO_RAD);
        if(currLink->getNext() == NULL)
            break;
        currLink = currLink->getNext();
    }
    return x0;
}

double Canvas::calcY(){
    double y0 = 0;
    Link* currLink = rootLink;
    while(true){
        y0 += currLink->getLength()*sin(currLink->getOrientation()*DEG_TO_RAD);
        if(currLink->getNext() == NULL)
            break;
        currLink = currLink->getNext();
    }
    return y0;
}

double dabs(double k){
    if(k > 0) return k;
    else return -k;
}

void Canvas::worldMove(){
    double sld = dabs(sqrt(pow(newX,2)+pow(newY,2)));
    double alpha, beta, psi, theta1, theta2 = 0;
    double tempX, tempY = 0;
    if(sld > 215){
        alpha = atan2(newX,newY);
        tempX = newX-links[2]->getLength()*cos(alpha);
        tempY = newY-links[2]->getLength()*sin(alpha);
        theta2 =

    } else if(sld > 125){

    } else {

    }
}

void Canvas::paintClicked() {
    paintToggle = !paintToggle;
    paint();
}


void Canvas::paint(){
    Link* link = links[2];
    QPoint endEffector(link->getLine().x2(), link->getLine().y2());
    if (paintToggle)
        this->addEllipse((int)endEffector.x()- brushSize/2,(int)endEffector.y()- brushSize/2,brushSize,brushSize,paintPen,paintBrush);
}

void Canvas::changeColor(){
    QColor color = QColorDialog::getColor();

    const QColor newColor(color.red(), color.green(), color.blue());

    paintBrush.setColor(newColor);
    paintPen.setColor(newColor);

    paint();
}
