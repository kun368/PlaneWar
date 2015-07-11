#include "circle.h"
#include "gamecontroller.h"
#include <QPainter>
#include <QDebug>



Circle::Circle(GameController &controller):
    controller(controller),
    cur(0)
{
    setData(GD_type, GO_Circle);
    pixMap.load(":/images/Circle.png");
    int w = pixMap.width() * 0.7, h = pixMap.height() * 0.7;
    path = new QPainterPath;
    path->addEllipse(QRectF(-w/2, -h/2, w, h));
}

QRectF Circle::boundingRect() const
{
    int w = pixMap.width() * 0.7, h = pixMap.height() * 0.7;
    return QRectF(-w/2, -h/2, w, h);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        painter->scale(0.7, 0.7);
        int w = pixMap.width(), h = pixMap.height();
        painter->rotate(cur);
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void Circle::advance(int phace)
{
    if(!phace) return;
    cur = (cur + 10) % 360;
}

QPainterPath Circle::shape()
{
    return *path;
}
