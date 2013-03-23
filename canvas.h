#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include "Link.h"
#include <vector>

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

    void addX();
    void subX();
    void addY();
    void subY();
private:
    QBrush blackBrush;
    QPen blackPen;
    Link* rootLink;
    std::vector<Link*> links;
    double x;
    double y;
};

#endif // CANVAS_H
