#include "ball.h"
#include "gamecontroller.h"
#include <QPainter>
#include <cmath>

Ball::Ball(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_Ball);
    pixMap.load("://images/Ball1.BMP");
    dirx = qrand() % 6 - 3;
}

QRectF Ball::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
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
    moveBy(vector.x() * 10, vector.y() * 10);
    if(!isInView(pos())) controller.removeItem(this);
}

void Ball::setDir()
{
    vector = controller.getPlantPos() - pos();
    vector /= hypot(vector.x(), vector.y());
}

