#ifndef LINK_H
#define LINK_H

#include <QLine>

class Link
{
public:
    Link();

    double getLength();
    void setLength(double);

    double getTheta();
    void setTheta(double);
    double getOrientation();

    Link* getNext();
    void setNext(Link*);

    Link* getPrevious();
    void setPrevious(Link*);

    QLine getLine();

    ~Link();
private:
    double length;
    double theta;
    Link* previous;
    Link* next;
};

#endif // LINK_H
