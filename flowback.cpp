#include "flowback.h"
#include <QPainter>

FlowBack::FlowBack(GameController &controller):
    controller(controller)
{
    cur = up = 0;
    setData(GD_type, GO_FlowBack);
    setPos(0, 0);
    pixMap.load(backgroundName);
}

FlowBack::~FlowBack()
{

}

QRectF FlowBack::boundingRect() const
{
    return QRectF(0, 0, pixMap.width(), viewHeight);
}

void FlowBack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    painter->save();
    int w = pixMap.width();
    painter->drawPixmap(QRectF(-10, -10, w, viewHeight+20), pixMap, QRectF(0, cur, w, viewHeight));
    if(backgroundLoop) update();
    painter->restore();
}

void FlowBack::advance(int phace)
{
    if(!phace) return;
    if(backgroundLoop) {
        cur -= 2;
        if(cur <= 0) cur = cur + pixMap.height() - viewHeight;
    }
}
