#ifndef MYPLANE_H
#define MYPLANE_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>

class MyPlane : public QGraphicsItem
{
public:
    MyPlane();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};

#endif // MYPLANE_H
