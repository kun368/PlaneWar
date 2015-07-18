#include "bullet.h"
#include "gamecontroller.h"
#include <QPainter>

Bullet::Bullet(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_Bullet);
    pixMap.load("://images/Bullet.png");
    speed = 8;
}

QRectF Bullet::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void Bullet::advance(int phace)
{
    if(!phace) return;
    moveBy(0, -speed);
    if(!isInView(pos())) controller.removeItem(this);
}

void Bullet::setSpeed(int x)
{
    speed = x;
}

