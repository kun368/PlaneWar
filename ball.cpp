#include "ball.h"

#include <QPainter>

Ball::Ball()
{

}

QRectF Ball::boundingRect() const
{
    qreal eps = 1;
    return QRectF(0-eps/2, 0-eps/2, 10+eps, 10+eps);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(0, 0, 10, 10);
}

void Ball::advance(int phace)
{
    if(!phace) return;

    QPointF cur = pos();
    setPos(cur.x(), cur.y() + 2);
}

