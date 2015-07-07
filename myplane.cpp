#include "myplane.h"

MyPlane::MyPlane()
{

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

