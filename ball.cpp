#include "ball.h"
#include "gamecontroller.h"

#include <QPainter>

Ball::Ball(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_Ball);
    pixMap.load(":/images/Ball1.BMP");
    dirx = qrand() % 6 - 3;
}

QRectF Ball::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void Ball::advance(int phace)
{
    if(!phace) return;

    QPointF cur = pos();
    setPos(cur.x() + dirx, cur.y() + 7);

    if(cur.y() > viewHeight) controller.removeItem(this);
}

