#include "wingbullet.h"
#include "gamecontroller.h"
#include <QPainter>

WingBullet::WingBullet(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_WingBullet);
    pixMap.load(":/images/WingBullet.png");
}

QRectF WingBullet::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void WingBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        painter->scale(0.7, 0.7);
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void WingBullet::advance(int phace)
{
    if(!phace) return;
    moveBy(0, -8);
    if(!isInView(pos()))
        controller.removeItem(this);
}

