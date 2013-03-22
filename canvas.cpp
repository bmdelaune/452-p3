#include "canvas.h"
#include "Utils.h"
#include "Link.h"
#include <vector>
#include <QDebug>
#include <math.h>

Canvas::Canvas(QObject *parent) :
    QGraphicsScene(parent)
{
}

void Canvas::initialize(){
    links.clear();
    rootLink = new Link();
    //rootLink->setTheta(90);
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
    while(currLink->getNext() != NULL){
        int x, y;
        if(currLink->getPrevious() == NULL){
            x = 0;
            y = 0;
        }else{

        }
        //this->addEllipse(x,y,currLink->getLength()*sin(currLink->getTheta()),currLink->getLength()*cos(currLink->getTheta()),blackPen,blackBrush);
        this->addLine(currLink->getLine(),blackPen);
        currLink = currLink->getNext();
    }
}
