#include "myplane.h"
#include <QKeyEvent>
#include <QDebug>
#include <QtAlgorithms>
#include <QList>
#include <QDebug>


MyPlane::MyPlane(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_MyPlane);
    pixMap.load(":/images/MyPlane.png");
}

QRectF MyPlane::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void MyPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void MyPlane::advance(int phace)
{
    if(!phace) return;
    handleCollisions();
}

void MyPlane::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *item, collisions) {
        if(item->data(GD_type) == GO_Ball) {
            controller.gameOver();
            return;
        }
    }
}

void MyPlane::moveLeft()
{
    QPointF cur = pos();
    setPos(qMax(cur.x()-10, 0.0), cur.y());
}

void MyPlane::moveRight()
{
    QPointF cur = pos();
    setPos(qMin(cur.x()+10, 500.0), cur.y());
}

void MyPlane::moveUp()
{
    QPointF cur = pos();
    setPos(cur.x(), qMax(cur.y()-10, 100.0));
}

void MyPlane::moveDown()
{
    QPointF cur = pos();
    setPos(cur.x(), qMin(cur.y()+10, 600.0));
}

