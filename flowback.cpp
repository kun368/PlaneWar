#include "flowback.h"
#include <QPainter>

FlowBack::FlowBack(GameController &controller):
    controller(controller)
{
    cur = 0;
    setData(GD_type, GO_FlowBack);
    setPos(0, 0);
    pixMap.load(":/images/background.png");
}

QRectF FlowBack::boundingRect() const
{
    return QRectF(0, 0, pixMap.width(), viewHeight);
}

void FlowBack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int w = pixMap.width();
    painter->drawPixmap(QRectF(-10, -10, w, viewHeight+20), pixMap, QRectF(0, cur, w, viewHeight));
    update();
}

void FlowBack::advance(int phace)
{
    if(!phace) return;
    cur -= 3;
    if(cur <= 0) cur = cur + pixMap.height() - viewHeight;
}

QPainterPath FlowBack::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

