#include "bullet.h"
#include <QPainter>

Bullet::Bullet()
{
    setData(GD_type, GO_Bullet);
}

QRectF Bullet::boundingRect() const
{
    qreal eps = 1;
    return QRectF(0-eps/2, 0-eps/2, 5+eps, 5+eps);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawRect(0, 0, 5, 5);
}

void Bullet::advance(int phace)
{
    if(!phace) return;

    QPointF cur = pos();
    setPos(cur.x(), cur.y() - 5);
}

