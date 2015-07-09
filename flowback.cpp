#include "flowback.h"
#include <QPainter>

FlowBack::FlowBack(GameController &controller):
    controller(controller)
{
    cur = up = 0;
    setData(GD_type, GO_FlowBack);
    setPos(0, 0);
    pixMap.load(":/images/background.png");
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
    painter->save();
    int w = pixMap.width();
    painter->drawPixmap(QRectF(-10, -10, w, viewHeight+20), pixMap, QRectF(0, cur, w, viewHeight));
//    if(++up == 2){ //防止CPU占用率过高
//        up = 0;
//        update();
//    }
    update();
    painter->restore();
}

void FlowBack::advance(int phace)
{
    if(!phace) return;
    cur -= 2;
    if(cur <= 0) cur = cur + pixMap.height() - viewHeight;
}
