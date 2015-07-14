#include "wingplane.h"
#include "gamecontroller.h"
#include <QPainter>

WingPlane::WingPlane(GameController &controller):
    controller(controller),
    cnt(0)
{
    setData(GD_type, GO_WingPlane);
    pixMap.load(":/images/MyPlane.png");
}

QRectF WingPlane::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void WingPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void WingPlane::advance(int phace)
{
    if(!phace) return;
    if(++cnt == 20) {
        controller.shootWingBullet(controller.getPlantPos() + pos() + QPointF(0, -20));
        cnt = 0;
    }
}
