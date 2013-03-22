#ifndef LINK_H
#define LINK_H

class Link
{
public:
    Link();

    double getLength();
    void setLength(double);

    double getTheta();
    void setTheta(double);

    Link* getNext();
    void setNext(Link*);

    Link* getPrevious();
    void setPrevious(Link*);

    ~Link();
private:
    double length;
    double theta;
    Link* previous;
    Link* next;
};

#endif // LINK_H
