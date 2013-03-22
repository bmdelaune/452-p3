#include "canvas.h"
#include "Utils.h"
#include "Link.h"
#include <vector>

Canvas::Canvas(QObject *parent) :
    QGraphicsScene(parent)
{
}

Canvas::initialize(){
    links.clear();
    rootLink = new Link();
    rootLink->setTheta(90);
    links.pushback(rootLink);
    for(int i = 1; i < NUM_LINKS; i++){
        Link* tempLink = new Link();
        tempLink->setPrevious(links[i-1]);
        links[i-1].setNext(tempLink);
    }
    links[0].setLength(150);
    links[1].setLength(100);
    links[2].setLength(75);
    updateLinks();
}

void Canvas::updateLinks(){
    Link* currLink = rootLink;
    while(currLink->getNext() != NULL){
        this->addEllipse(20,20,20,20,blackPen, blackBrush);
        currLink = currLink->getNext();
    }
}
