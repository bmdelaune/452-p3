#include "Link.h"

Link::Link()
{
    theta = 0;
}

void Link::drawLink(double theta){

}

double getLength(){
    return length;
}

void setLength(double l){
    length = l;
}

double getTheta(){
    return theta;
}

void setTheta(double t){
    theta = t;
}

Link* getNext(){
    return next;
}

void setNext(Link* n){
    next = n;
}

Link* getPrevious(){
    return previous;
}

void setPrevious(Link* p){
    previous = p;
}
