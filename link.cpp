#include "Link.h"
#include <stdlib.h>
#include <math.h>

Link::Link()
{
    theta = 0;
    next = NULL;
    previous = NULL;
}

Link::~Link(){
    delete this;
}

double Link::getLength(){
    return length;
}

void Link::setLength(double l){
    length = l;
}

double Link::getTheta(){
    return theta;
}

void Link::setTheta(double t){
    theta = t;
}

double Link::getOrientation(){
    if(previous == NULL){
        return theta;
    } else {
        return theta+previous->getOrientation();
    }
}

Link* Link::getNext(){
    return next;
}

void Link::setNext(Link* n){
    next = n;
}

Link* Link::getPrevious(){
    return previous;
}

void Link::setPrevious(Link* p){
    previous = p;
}

QLine Link::getLine(){
    if(previous == NULL){
        return QLine(0,0,length*cos(theta),length*sin(theta));
    } else {
        QLine prevLine = previous->getLine();
        double orientation = getOrientation();
        return QLine(prevLine.x2(),prevLine.y2(),prevLine.x2()+length*cos(orientation),prevLine.y2()+length*sin(orientation));
    }
}
