#include "tip.h"
#include "gamecontroller.h"
#include <QPainter>

Tip::Tip(GameController &controller):
    controller(controller)
{
    setData(GD_type, GO_Tip);
    pixMap.load(":/images/Tip.png");
    setPos(-15, viewHeight-pixMap.height()+5);
    setZValue(2);
}

QRectF Tip::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(0, 0, w, h);
}

void Tip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(0, 0), pixMap);
        painter->restore();
    }
}

