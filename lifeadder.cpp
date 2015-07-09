#include "lifeadder.h"
#include "gamecontroller.h"
#include <QPainter>


LifeAdder::LifeAdder(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_LifeAdder);
    pixMap.load(":/images/LifeAdder.png");
}

QRectF LifeAdder::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void LifeAdder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void LifeAdder::advance(int phace)
{
    if(!phace) return;

    QPointF cur = pos();
    setPos(cur.x(), cur.y() + 12);

    if(cur.y() > viewHeight) controller.removeItem(this);
}
