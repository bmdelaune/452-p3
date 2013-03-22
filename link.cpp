#include "Link.h"
#include <stdlib.h>

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

