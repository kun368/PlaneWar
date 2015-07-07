#include "enemy.h"
#include <QPainter>

Enemy::Enemy(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_Enemy);
}

QRectF Enemy::boundingRect() const
{
    qreal eps = 1;
    return QRectF(0-eps/2, 0-eps/2, 20+eps, 20+eps);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(0, 0, 20, 20);
}

void Enemy::advance(int phace)
{
    if(!phace) return;

    QPointF cur = pos();
    setPos(cur.x(), cur.y() + 1);
}
