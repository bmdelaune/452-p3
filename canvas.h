#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include "Link.h"
#include <vector>
//#include

class Canvas : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Canvas(QObject *parent = 0);
    void initialize();
    void updateLinks();
signals:
    
public slots:
    void rotateCW();
    void rotateCCW();
private:
    QBrush blackBrush;
    QPen blackPen;
    Link* rootLink;
    std::vector<Link*> links;
    //std::vector<
};

#endif // CANVAS_H
