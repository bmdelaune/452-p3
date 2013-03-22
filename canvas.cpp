#include "canvas.h"
#include "Utils.h"
#include "Link.h"
#include <vector>
#include <QDebug>

Canvas::Canvas(QObject *parent) :
    QGraphicsScene(parent)
{
}

void Canvas::initialize(){
    links.clear();
    rootLink = new Link();
    rootLink->setTheta(90);
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
    Link* currLink = rootLink;
    while(currLink->getNext() != NULL){
        //this->addEllipse(0,0,300,300,blackPen, blackBrush);
        this->addRect(0,0,100,100,blackPen,blackBrush);
        currLink = currLink->getNext();
    }
}
