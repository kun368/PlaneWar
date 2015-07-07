#include "myplane.h"
#include <QKeyEvent>
#include <QDebug>
#include <QtAlgorithms>
#include <QList>


MyPlane::MyPlane(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_MyPlane);
}

QRectF MyPlane::boundingRect() const
{
    qreal eps = 1;
    return QRectF(0-eps/2, 0-eps/2, 20+eps, 20+eps);
}

void MyPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawRect(0, 0, 20, 20);
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
    setPos(cur.x(), qMax(cur.y()-10, 0.0));
}

void MyPlane::moveDown()
{
    QPointF cur = pos();
    setPos(cur.x(), qMin(cur.y()+10, 600.0));
}

