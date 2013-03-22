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
    
private:
    const QBrush blackBrush;
    const QPen blackPen;
    Link* rootLink;
    std::vector<Link*> links;
};

#endif // CANVAS_H
