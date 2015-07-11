#include "boss.h"
#include "gamecontroller.h"

#include <QPainter>

Boss::Boss(GameController &controller):
    controller(controller),
    posX(qrand() % viewWidth),
    dirl(true)
{
    setData(GD_type, GO_Boss);
    pixMap.load(":/images/Boss.png");
    setPos(posX, 100);
}

QRectF Boss::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void Boss::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void Boss::advance(int phace)
{
    if(!phace) return;

    if(dirl) posX -= 5;
    else posX += 5;
    if(posX >= viewWidth || posX <= 0)
        dirl = !dirl;
    setPos(posX, 100);
}
